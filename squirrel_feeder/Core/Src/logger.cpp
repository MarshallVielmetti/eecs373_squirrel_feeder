/*
 * logger.c
 *
 *  Created on: Nov 21, 2024
 *      Author: mvielmet
 */

#include "fatfs.h"
#include <string.h>

// global logger object
void LOGGER::LOG_EVENT(LOGGER::EVENT event) {
	// open log file and seek till end
	char event_string[32];

	switch(event) {
	case LOGGER::EVENT::SYSTEM_INIT:
		sprintf(event_string, "--- SYSTEM INIT --- %d\n", HAL_GetTick());
		break;
	}

	LOGGER::LOG(event_string);
}

void LOGGER::LOG(char* DATA) {
	fres = f_open(&LOGGER::fil, "log.txt", FA_WRITE | FA_OPEN_ALWAYS);
	fres = f_lseek(&LOGGER::fil, f_size(fil));

	UINT bytesWrote;
	f_write(&LOGGER::fil, DATA, strlen(DATA), &bytesWrote);
	f_close(&fil);
}