/*
 * camera_handler.cpp
 *
 *  Created on: Nov 22, 2024
 *      Author: mvielmet
 */


#include "camera_handler.h"
#include "FatFs.h"
#include "vc0706_driver.h"

#include <stdlib.h>
#include <stdio.h>

/*
 * Number of image blocks the camera should process during each call to CAMERA_Process
 */
#define CAMERA_PROCESS_CHUNKS 50
#define CAMERA_READ_IMG_SIZE 32
#define CAMERA_READ_ACK_SIZE 10

struct Camera {
	/* Whether or not the camera is ready to take another photo (has finished processing the current photo)*/
	bool ready;

	uint32_t cur_image_size;
	uint32_t cur_image_idx;

	uint16_t pic_index;
	uint16_t rand_seed;

	/*
	 * Declare this here to avoid needing to reallocate it all the time
	 */
	uint8_t img_read_buf[42];

	/* Writer to current image file */
	FIL file_writer;

	void init();

	/*
	 * Instructs the physical camera to take a photo. If there is already a photo "ready"
	 *
	 * returns '1' if successful, otherwise 0
	 */
	uint8_t take_photo(void);

	uint8_t process(void);

	// returns 1 if read the end chunk
	uint8_t process_chunk(void);

	/*
	 * Reads in the LAST block of image data, then does cleanup / makes the camera "ready"
	 */
	void finish_image(void);
} CAMERA;


void CAMERA_Init(void) {
	CAMERA.init();
}

uint8_t CAMERA_Take_Photo(void) {
	return CAMERA.take_photo();
}

uint8_t CAMERA_Process(void) {
	return CAMERA.process();
}


void Camera::init(void) {
	this->ready = false;

	this->cur_image_size = 0;
	this->cur_image_idx = 0;

	this->pic_index = 0;
	this->rand_seed = rand() % 1000;
}


uint8_t Camera::take_photo(void) {
	if (!this->ready) {
		return 0; // camera not ready, return failure
	}

	// instruct the physical camera to take a photo
	uint8_t success = VC0706_TakePhoto();

	// Verify success and update state
	if (!success) {
		return 0;
	}

	success = VC0706_StopCapture();

	if (!success) {
		return 0;
	}

	/*
	 * Read in the length of the image
	 */
	this->cur_image_size = VC0706_ReadImageDataLength();

	/*
	 * Now initialize the file handle
	 */
	char img_name[20];
	sprintf(img_name, "%d-%d.jpg", this->pic_index, this->rand_seed);
	f_open(&this->file_writer, img_name, FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);

	this->pic_index++;

	/*
	 * now must initialize the camera struct to be able to start receiving photos
	 */

	this->cur_image_idx = 0;
	this->ready = 0; // no longer ready to take a new photo

	return 1;
};


uint8_t Camera::process(void) {
	uint8_t end_flag = 0;
	uint8_t num_chunks_processed = 0;

	while (!end_flag && num_chunks_processed++ < CAMERA_PROCESS_CHUNKS) {
		end_flag = process_chunk();
	}

	return end_flag; // 1 means the last chunk was read
}

uint8_t Camera::process_chunk(void) {
	uint8_t status = VC0706_ReadImageBlock(this->img_read_buf, this->cur_image_idx);

	if (!status) {
		return 0;
	}

	UINT bytes_wrote;
	f_write(&this->file_writer, img_read_buf + 5, CAMERA_READ_IMG_SIZE, &bytes_wrote);

	this->cur_image_idx += 0x20;

	if (this->cur_image_idx >= this->cur_image_size) {
		this->finish_image(); // needs to perform the final processing in this->finish_image
		return 1;
	}

	return 0; //normal case
}

void Camera::finish_image() {
	VC0706_ReadImageBlock(this->img_read_buf, this->cur_image_idx);

	UINT bytes_wrote;

	for (uint32_t i = 1; i < 32; i++) {
		if (this->img_read_buf[i-1 + 5] == 0xFF && this->img_read_buf[i + 5] == 0xD9) {
			// found end sequence
			f_write(&this->file_writer, this->img_read_buf + 5, i + 1, &bytes_wrote);
			break;
		}
	}

	f_close(&this->file_writer);

	this->ready = true; // ready to take a new image
}


