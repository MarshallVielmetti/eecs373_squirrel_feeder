/*
 * logger.c
 *
 *  Created on: Nov 21, 2024
 *      Author: mvielmet
 */

#include "fatfs.h"

#include <string.h>
#include <stdio.h>

#include "logger.h"



struct LOGGER {
	static FIL fil; 		//File handle
	static FRESULT fres; //Result after operations

	static void LOG_EVENT(EVENT event);
	static void LOG(char* DATA);
};

FIL LOGGER::fil;
FRESULT LOGGER::fres;

void LOGGER::LOG(char* DATA) {
	LOGGER::fres = f_open(&LOGGER::fil, "log.txt", FA_WRITE | FA_OPEN_ALWAYS);
	LOGGER::fres = f_lseek(&LOGGER::fil, f_size(&LOGGER::fil));

	UINT bytesWrote;
	f_write(&LOGGER::fil, DATA, strlen(DATA), &bytesWrote);
	f_close(&LOGGER::fil);
}

void LOGGER::LOG_EVENT(EVENT event) {
	// open log file and seek till end
	char event_string[32];

	switch(event) {
	case EVENT::SYSTEM_INIT:
		sprintf(event_string, "--- SYSTEM INIT --- %d\n", HAL_GetTick());
		break;
	}

	LOGGER::LOG(event_string);
}


/*
 * Wrapper functions for C code
 */

void LOG_EVENT(EVENT event) {
//	FIL fil;
//	f_open(&fil, "log.txt", FA_WRITE | FA_OPEN_ALWAYS);
//	f_lseek(&fil, f_size(&fil));
	LOGGER::LOG_EVENT(event);
}

void LOG(char* DATA) {
	LOGGER::LOG(DATA);
}
