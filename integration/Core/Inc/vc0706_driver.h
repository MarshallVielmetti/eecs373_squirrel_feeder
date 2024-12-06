/*
 * vc0706_driver.h
 *
 *  Created on: Dec 4, 2024
 *      Author: nehakan
 */

#include <stdint.h>


#ifndef INC_VC0706_DRIVER_H_
#define INC_VC0706_DRIVER_H_

void VC0706_SendCommand(uint8_t cmd, uint8_t *params, uint8_t params_len);

uint8_t VC0706_TakePhoto(void);
uint8_t VC0706_StopCapture(void);

uint16_t VC0706_ReadImageDataLength(void);
uint8_t VC0706_ReadImageBlock(uint8_t *image_buffer, uint32_t start_address);

uint8_t VC0706_SetResolution(uint8_t resolution);

uint8_t VC0706_Reset(void);


#endif /* INC_VC0706_DRIVER_H_ */
