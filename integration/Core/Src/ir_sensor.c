/*
 * ir_sensor.c
 *
 *  Created on: Dec 3, 2024
 *      Author: mvielmet
 */

#include "ir_sensor.h"
#include "main.h"

/*
 * Make sure to define:
 *  IR_ADC_HANDLE
 *  IR0_ADC_CHANNEL
 *  IR1_ADC_CHANNEL
 *
 *  in main.h
 */

extern ADC_HandleTypeDef IR_ADC_HANDLE;
extern TIM_HandleTypeDef IR_SENSOR_TIMER_HANDLE;

#define NUM_MEASUREMENTS_TO_AVG 8



static float distance_measurements[NUM_MEASUREMENTS_TO_AVG];
static uint8_t distance_idx = 0;


void ir_sensor_init() {
	printf("Initializing IR Sensor...");
	// make sure doesn't auto trigger without readings
	for (uint8_t i = 0; i < NUM_MEASUREMENTS_TO_AVG; i++) {
		distance_measurements[i] = 0;
	}
	printf(" Successful!\n\r");
}

static float read_distance() {
	 uint32_t ADC_VAL = 0;

	 HAL_ADC_Start(&IR_ADC_HANDLE);//start conversion
	 HAL_ADC_PollForConversion(&IR_ADC_HANDLE, 0xFFFFFFFF);//wait for conversion to finish
	 ADC_VAL = HAL_ADC_GetValue(&IR_ADC_HANDLE);//retrieve value

	 return ADC_VAL;
}

void ir_sensor_interrupt_routine() {
	float curr = read_distance();

	distance_measurements[distance_idx++] = curr;
	distance_idx %= NUM_MEASUREMENTS_TO_AVG;
}

float get_cur_distance_average() {
	float ttl = 0;
	for (uint8_t i = 0; i < NUM_MEASUREMENTS_TO_AVG; i++) {
		ttl += distance_measurements[i];
	}

	return ttl / NUM_MEASUREMENTS_TO_AVG;
}

void zero_averages() {
	for (uint8_t i = 0; i < NUM_MEASUREMENTS_TO_AVG; i++) {
		distance_measurements[i] = 0;
	}
}



/*
 * PLANNING FOR MULTIPLe
 *
 * Each one needs to do a HAL_ADC_ConfigChannel beforehand
 */
