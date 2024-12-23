/*
 * vc0706_driver.c
 *
 *  Created on: Dec 4, 2024
 *      Author: nehakan
 */

#include "main.h"


/*
 * Camera command definitions
 */
#define VC0706_SERIAL_NUM 		0x00 /*(Serial Number)*/
#define VC0706_CMD_PREFIX 		0x56 /*(Command Prefix)*/

#define VC0706_CMD_RESET 		0x26 /*(Reset)*/
#define VC0706_CMD_SET_IMAGE_RES	0x31 /*(Resolution)*/

#define VC0706_CMD_TAKE_PHOTO 	0x36 /*(Take Photo)*/
#define VC0706_CMD_STOP_CAPTURE 0x36 /*(Stop Capture)*/
#define VC0706_CMD_READ_DATA 	0x32 /*(Read Data Packet)*/
#define VC0706_CMD_READ_DATA_LEN 0x34 /*(Get data length)*/

#define VC0706_RESPONSE_TIMEOUT 1000
#define VC0706_IMAGE_BLOCK_SIZE 32

extern UART_HandleTypeDef CAM_UART_HANDLE;

/*
 * HELPER FUNCTIONS
 */

/* VC0706_SendCommand
 * cmd - one of the command a data bytes
 * params - array of additional command bytes
 * params_len - length of parameters array
 */
void VC0706_SendCommand(uint8_t cmd, uint8_t *params, uint8_t params_len) {
    uint8_t buffer[16];

    /*
     * Universal Command Prefix
     */
    buffer[0] = VC0706_CMD_PREFIX;
    buffer[1] = VC0706_SERIAL_NUM;

    // Insert the command ID byte
    buffer[2] = cmd;

    /*
     * Copy params into command buffer
     */
    for (uint8_t i = 0; i < params_len; i++) {
        buffer[3 + i] = params[i];
    }

    HAL_UART_Transmit(&CAM_UART_HANDLE, buffer, 3 + params_len, HAL_MAX_DELAY);
}

/*
 * COMMANDS
 */

/* VC0706_TakePhoto
 *
 * Sends take photo command and verifies response ACK
 */
uint8_t VC0706_TakePhoto(void) {
    uint8_t takePhotoCommand[] = {0x01, 0x00}; // Parameters for taking a photo
    VC0706_SendCommand(VC0706_CMD_TAKE_PHOTO, takePhotoCommand, sizeof(takePhotoCommand));

    // response array
    uint8_t response[5]={0};
    HAL_StatusTypeDef status = HAL_UART_Receive(&CAM_UART_HANDLE, response, sizeof(response), VC0706_RESPONSE_TIMEOUT); // 1-second timeout

    if (status != HAL_OK) {
        // Timeout or error occurred, handle accordingly
        return 0; // Indicate failure to receive acknowledgment
    }

    // Check if the received response is as expected: 0x76 0x00 0x36 0x00 0x00
    return response[0] == 0x76 && response[1] == 0x00 && response[2] == 0x36 && response[3] == 0x00 && response[4] == 0x00;
}

/* VC0706_StopCapture
 * Sends the stop capture command, and verifies the ack
 *
 */
uint8_t VC0706_StopCapture(void) {
    uint8_t stopCaptureCommand[] = {0x01, 0x03};
    uint8_t response[5] = {0}; // Expected response: 0x76 0x00 0x36 0x00 0x00

    // Send the Stop Capture command
    VC0706_SendCommand(VC0706_CMD_STOP_CAPTURE, stopCaptureCommand, sizeof(stopCaptureCommand));

    // Receive the response
    HAL_StatusTypeDef status = HAL_UART_Receive(&CAM_UART_HANDLE, response, sizeof(response), VC0706_RESPONSE_TIMEOUT);

    // Check if the response is as expected
    return (status == HAL_OK) && (response[0] == 0x76 && response[1] == 0x00 && response[2] == 0x36 && response[3] == 0x00 && response[4] == 0x00);
}

/* VC0706_ReadImageDataLength
 *
 * Sends read image data length command returns correctly formated uint16_t containing
 * the length of the most recently taken image in bytes
 *
 */
uint16_t VC0706_ReadImageDataLength(void) {
	uint8_t read_image_len_cmd[] = {0x01, 0x00};
	VC0706_SendCommand(VC0706_CMD_READ_DATA_LEN, read_image_len_cmd, sizeof(read_image_len_cmd));

	uint8_t response[9]; // repsonse buffer
	HAL_StatusTypeDef status = HAL_UART_Receive(&CAM_UART_HANDLE, response, sizeof(response), VC0706_RESPONSE_TIMEOUT);


    if (status != HAL_OK) {
    	return 0;
    }

    uint16_t image_len = (response[7] << 8) | response[8];

    return image_len;
}

/* VC0706_ReadImageBlock
 * Sends the read image command, and then receives one block of image data into the provided buffer
 *
 * feeds the entire response into the image_buffer, which is at least 42 bytes
 */
uint8_t VC0706_ReadImageBlock(uint8_t *image_buffer, uint32_t start_address) {
    uint8_t readCommand[13];

    readCommand[0] = 0x0C;
    readCommand[1] = 0x00;
    readCommand[2] = 0x0A; // was 0D
    readCommand[3] = 0x00;
    readCommand[4] = 0x00;

    readCommand[5] = (start_address >> 8) & 0xFF;
    readCommand[6] = start_address & 0xFF;

    readCommand[7] = 0x00;
    readCommand[8] = 0x00;

    readCommand[9] = 0x00;
    readCommand[10] = 0x20;

    readCommand[11] = 0x00;
    readCommand[12] = 0xFF;

    __disable_irq();

    VC0706_SendCommand(VC0706_CMD_READ_DATA, readCommand, sizeof(readCommand));

    HAL_StatusTypeDef status = HAL_UART_Receive(&CAM_UART_HANDLE, image_buffer, VC0706_IMAGE_BLOCK_SIZE + 10, VC0706_RESPONSE_TIMEOUT);

    __enable_irq();

    return status == HAL_OK;
}

uint8_t VC0706_SetResolution(uint8_t resolution) {
    uint8_t resolutionCommand[] = {0x05, 0x04, 0x01, 0x00, 0x19, resolution}; // WRITE_DATA command parameters
    VC0706_SendCommand(VC0706_CMD_SET_IMAGE_RES, resolutionCommand, sizeof(resolutionCommand));

    uint8_t response[6];
    HAL_StatusTypeDef status = HAL_UART_Receive(&huart3, response, sizeof(response), 1000); // Timeout of 1 second

    if (status != HAL_OK) {
        return 0;
    }

    // Expected response: 0x76 0x00 0x31 0x00 0x00
    return response[0] == 0x76 && response[1] == 0x00 && response[2] == 0x31 && response[3] == 0x00;
}

uint8_t VC0706_Reset(void) {
    uint8_t resetCommand[] = {0x00};
    VC0706_SendCommand(VC0706_CMD_RESET, resetCommand, sizeof(resetCommand));

    uint8_t response[5];
    HAL_StatusTypeDef status = HAL_UART_Receive(&huart3, response, sizeof(response), 10000);

    if (status != HAL_OK) {
    	return 0;
    }

    return (response[0] == 0x76 && response[1] == 0x00 && response[2] == 0x26 && response[3] == 0x00); // Check if reset was successful
}

