/*
 * camera_handler.h
 *
 *  Created on: Nov 22, 2024
 *      Author: mvielmet
 */


#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "FatFs.h"

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Performs global camera initialization and creates global camera object
 */
void CAMERA_Init(void);

/*
 * Forwards call to camera::take_photo
 */
uint8_t CAMERA_Take_Photo(void);


/*
 * Performs the processing of a number of chunks of image data and writing them to the SD card
 *
 * Returns 1 if the chunk processed was the final chunk, otherwise 0.
 */
uint8_t CAMERA_Process();

#ifdef __cplusplus
}
#endif

