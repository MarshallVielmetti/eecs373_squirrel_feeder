/*
 * logger.h
 *
 *  Created on: Nov 21, 2024
 *      Author: mvielmet
 */

#ifndef INC_LOGGER_H_
#define INC_LOGGER_H_

#include "main.h"

struct LOGGER {
	enum EVENT {
		SYSTEM_INIT,
	};

	static FIL fil; 		//File handle
	static FRESULT fres; //Result after operations

	static void LOG_EVENT(LOGGER_EVENT event);
	static void LOG(char* DATA);
};



#endif /* INC_LOGGER_H_ */
