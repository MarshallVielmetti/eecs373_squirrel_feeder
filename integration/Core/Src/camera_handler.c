/*
 * camera_handler.c
 *
 *  Created on: Dec 4, 2024
 *      Author: nehakan
 */

#include "camera_handler.h"
#include "integration.h"
#include "vc0706_driver.h"
#include "FatFs.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
 * Number of image blocks the camera should process during each call to CAMERA_Process
 */
#define CAMERA_PROCESS_CHUNKS 10
#define CAMERA_READ_IMG_SIZE 32
#define CAMERA_READ_ACK_SIZE 10
#define CAMERA_RES 0x22 /* 0x11 = (320*240), 0x00 = (640*480), 0x22 = (160*120) */

extern TIM_HandleTypeDef CAM_TIMER_HANDLE;
extern UART_HandleTypeDef CAM_UART_HANDLE;


static bool camera_ready;
static uint32_t image_size;
static uint32_t cur_image_idx;

static uint16_t pic_index; // for storing file
static uint16_t rand_seed;

static uint8_t img_read_buf[CAMERA_READ_IMG_SIZE + CAMERA_READ_ACK_SIZE];

static FIL file_writer;


static bool READY_TO_REQUEST = false;


/*
 * PUBLIC CAMERA INTERFACE
 */

void camera_init(void) {
	printf("Initializing Camera... ");
	image_size = 0;
	cur_image_idx = 0;

	pic_index = 0;

	//  has to be mod 100 bcz file names have to be like 8 chars
	rand_seed = rand() % 100;
//	VC0706_SetResolution(CAMERA_RES);
//	HAL_Delay(1000);
//	VC0706_Reset();
//	HAL_Delay(2500);

	camera_ready = true;
	printf(" Successful!\n\r");
}

uint8_t camera_take_photo(void) {
	if (!camera_ready) {
		return 0; // camera not ready, return failure
	}

	// instruct the physical camera to take a photo
	uint8_t success = VC0706_StopCapture();

	// Verify success and update state
	if (!success) {
		return 0;
	}

	HAL_Delay(100);


	success = VC0706_TakePhoto();

	if (!success) {
		return 0;
	}

	HAL_Delay(100);

	/*
	 * Read in the length of the image
	 */
	image_size = VC0706_ReadImageDataLength();

	/*
	 * Now initialize the file handle
	 */
	char img_name[9];
	sprintf(img_name, "%d%d.jpg", pic_index, rand_seed);
//	FRESULT fres = f_open(&(file_writer), img_name, FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
	f_open(&(file_writer), img_name, FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);

	pic_index++;

	/*
	 * now must initialize the camera struct to be able to start receiving photos
	 */

	cur_image_idx = 0;
	camera_ready = 0; // no longer ready to take a new photo

	READY_TO_REQUEST = true;
//	__HAL_UART_ENABLE_IT(&CAM_UART_HANDLE, UART_IT_RXNE);

	return 1;
}

static void finish_image(void) {
	UINT bytes_wrote;

	for (uint32_t i = 1; i < 32; i++) {
		if (img_read_buf[i-1 + 5] == 0xFF && img_read_buf[i + 5] == 0xD9) {
			// found end sequence
			f_write(&file_writer, img_read_buf + 5, i + 1, &bytes_wrote);
			break;
		}
	}

	f_close(&file_writer);

	camera_ready = true; // ready to take a new image
	get_feeder()->needs_to_process_picture = false;

//	__HAL_UART_DISABLE_IT(&CAM_UART_HANDLE, UART_IT_RXNE);

	printf("Camera Processing Completed!\n\r");
}

static uint8_t process_chunk(void) {
	if (cur_image_idx >= image_size - CAMERA_READ_IMG_SIZE) {
		finish_image(); // needs to perform the final processing in this->finish_image
		return 1;
	}

	uint8_t status = VC0706_ReadImageBlock(img_read_buf, cur_image_idx);

	if (!status) {
		return 0;
	}

	UINT bytes_wrote;
	f_write(&file_writer, img_read_buf + 5, CAMERA_READ_IMG_SIZE, &bytes_wrote);

	cur_image_idx += 0x20;

	return 0; //normal case
}

uint32_t camera_get_percent_done() {
	return (100 * cur_image_idx) / image_size;
}


uint8_t camera_process(void) {
	printf("Camera Processing Image - %d%% Completed\n\r", camera_get_percent_done());
	uint8_t end_flag = 0;
	uint8_t num_chunks_processed = 0;

	while (!end_flag && num_chunks_processed++ < CAMERA_PROCESS_CHUNKS) {
		end_flag = process_chunk();
	}

	return end_flag; // 1 means the last chunk was read
}


uint8_t camera_get_ready() {
	return camera_ready;
}

bool camera_is_ready_to_request() {
	return READY_TO_REQUEST;
}

// called by main
void camera_request_chunk() {
	printf("Camera Requesting\n\r");
	READY_TO_REQUEST = false;

	VC0706_ReadImageBlock(img_read_buf, cur_image_idx);
}

#define VC0706_RESPONSE_TIMEOUT 1000
#define VC0706_IMAGE_BLOCK_SIZE 32
void camera_receive_chunk() {
	printf("Camera Processing Image - %d%% Completed\n\r", camera_get_percent_done());

    HAL_StatusTypeDef status = HAL_UART_Receive(&CAM_UART_HANDLE, img_read_buf, VC0706_IMAGE_BLOCK_SIZE + 10, VC0706_RESPONSE_TIMEOUT);

	if (cur_image_idx >= image_size - CAMERA_READ_IMG_SIZE) {
		finish_image(); // needs to perform the final processing in this->finish_image
	} else {
		process_chunk();
	}

	READY_TO_REQUEST = true;
}



