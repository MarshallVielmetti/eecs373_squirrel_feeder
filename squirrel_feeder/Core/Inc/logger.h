/*
 * logger.h
 *
 *  Created on: Nov 21, 2024
 *      Author: mvielmet
 */

#pragma once

#include "main.h"

enum EVENT {
	SYSTEM_INIT,
};

#ifdef __cplusplus
extern "C" {
#endif

void LOG_EVENT(enum EVENT event);

void LOG(char* DATA);

#ifdef __cplusplus
}
#endif

