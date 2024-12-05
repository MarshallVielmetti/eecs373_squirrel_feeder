/*
 * camera_handler.h
 *
 *  Created on: Dec 4, 2024
 *      Author: nehakan
 */

#include <stdint.h>

#ifndef INC_CAMERA_HANDLER_H_
#define INC_CAMERA_HANDLER_H_

/*
 * Performs global camera initialization and creates global camera object
 */
void camera_init(void);

/*
 * Forwards call to camera::take_photo
 */
uint8_t camera_take_photo(void);

/*
 * Performs the processing of a number of chunks of image data and writing them to the SD card
 *
 * Returns 1 if the chunk processed was the final chunk, otherwise 0.
 */
uint8_t camera_process();

uint8_t camera_get_ready();

uint32_t camera_get_percent_done();


#endif /* INC_CAMERA_HANDLER_H_ */
