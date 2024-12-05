/*
 * integration.c
 *
 *  Created on: Dec 3, 2024
 *      Author: mvielmet
 */

#include "main.h"

#include "motor.h"
#include "load_cell.h"
#include "ir_sensor.h"
#include "camera_handler.h"
#include "lcd.h"

#include <stdint.h>

extern TIM_HandleTypeDef IR_SENSOR_TIMER_HANDLE;
extern TIM_HandleTypeDef MAIN_TIMER_HANDLE;

extern int weight;
extern int squirrel_count;

enum FeederStateType {
	WAITING_FOR_SQUIRREL,
	DETECTED_SQUIRREL,
	DISPENSING,
	COOLDOWN,
	OUT_OF_FOOD
} FeederState;

float IR_DISTANCE_THRESHOLD = 1.5; 	// Threshold to determine IR sensor trigger - Need to confirm voltage vs. distance for IR sensor reading
int PS_FOOD_THRESHOLD = 5000;		// Max weight (mg) of food on tray
int cool_down_time = 5000;			// Time that system waits after dispensing food
uint8_t error_state = 0;	 		// Error catching for camera capture
extern bool out_of_food = false;	// Condition flag for when dispenser is jammed/out of food


void init_peripherals() {
	HAL_Delay(2500);

	camera_init();

	// shared between the IR sensor and pressure sensor
	HAL_TIM_Base_Start_IT(&IR_SENSOR_TIMER_HANDLE);

	ir_sensor_init();
	ps_init();
	lcd_init();

	FeederState = WAITING_FOR_SQUIRREL;

	// start main timer
	HAL_TIM_Base_Start_IT(&MAIN_TIMER_HANDLE);

}

// main program logic interrupt routine
void main_isr() {
	switch (FeederState) {
	case WAITING_FOR_SQUIRREL:
		waiting_for_squirrel_isr();
		break;
	case DETECTED_SQUIRREL:
		detected_squirrel_isr();
		break;
	case DISPENSING:
		dispensing_isr();
		break;
	case COOLDOWN:
		cooldown();
		break;
	case OUT_OF_FOOD:
		out_of_food_isr();
		break;
	}
}

waiting_for_squirrel_isr() {
	if(get_cur_distance_average() > IR_DISTANCE_THRESHOLD) {
		FeederState = DETECTED_SQUIRREL;
	}
}

detected_squirrel_isr() {
	error_state = camera_take_photo();
	if(!error_state) {
		while(1){} // Should probably remove error-handling for demo
	}
	FeederState = DISPENSING;
}

dispensing_isr() {
	int dispense_count = 0;
	while(ps_get_reading() < PS_FOOD_THRESHOLD) {
		stepper_rotate_clockwise_steps(1); // Could adjust function to use steps/partial rotations
		if(dispense_count > 5) {
			FeederState = OUT_OF_FOOD;
		}
	}
	FeederState = COOLDOWN;
}

cooldown() {
	HAL_DELAY(cool_down_time);
	FeederState = WAITING_FOR_SQUIRREL;
}

out_of_food() {	// We don't have a great way to determine when food is added back
	out_of_food = true;
	while(out_of_food) {
		stepper_rotate_clockwise_steps(5);
		HAL_DELAY(30000);
		if(ps_get_reading() > PS_FOOD_THRESHOLD){
			FeederState = WAITING_FOR_SQUIRREL;
		}
	}
}



//FeederStateType cooldown_isr(){}
void perform_startup_routine() {
	/*
	 * Spin motor a lil bit
	 */
	stepper_rotate_clockwise_steps(200);

	/*
	 * Test force sensor
	 */
	uint32_t ttl_weight = 0;
	for (uint8_t i = 0; i < 1; i++) {
		ttl_weight += weigh();
	}

	float avg_weight = ttl_weight / 4.0;

	/*
	 * Test the IR sensor
	 */
//	float ttl_distance = 0;
//	for (uint8_t i = 0; i < 15; i++) {
//		float dist = read_distance();
//		ttl_distance += read_distance();
//	}

//	float avg_distance = ttl_distance / 4.0;
}


void simple_IR_trigger() {
	while(1) {
		float ttl_distance = 0;
		for (uint8_t i = 0; i < 8; i++) {
			ttl_distance += read_distance();
		}
		float avg_distance = ttl_distance / 8.0;

		if (avg_distance < 3) {
			stepper_rotate_clockwise_steps(200);
			break;
		}
	}
}

void camera_test() {


	camera_take_photo();

//	while (camera_process() != 1);
}

// Should update variables to display right stuff





