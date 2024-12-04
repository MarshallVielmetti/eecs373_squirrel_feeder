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
//#include "lcd.h"

#include <stdint.h>

extern TIM_HandleTypeDef IR_SENSOR_TIMER_HANDLE;
extern TIM_HandleTypeDef MAIN_TIMER_HANDLE;


enum FeederStateType {
	WAITING_FOR_SQUIRREL,
	DETECTED_SQUIRREL,
	DISPENSING,
	JUST_DISPENSED,
	COOLDOWN
} FeederState;


void init_peripherals() {
	HAL_Delay(2500);

	camera_init();

	// shared between the IR sensor and pressure sensor
	HAL_TIM_Base_Start_IT(&IR_SENSOR_TIMER_HANDLE);

	ir_sensor_init();
	ps_init();

	FeederState = WAITING_FOR_SQUIRREL;

	// start main timer
	HAL_TIM_Base_Start_IT(&MAIN_TIMER_HANDLE);

}

// main program logic interrupt routine
void main_isr() {
	switch (FeederState) {
	case WAITING_FOR_SQUIRREL:
		FeederState = waiting_for_squirrel_isr();
		break;
	case DETECTED_SQUIRREL:
		FeederState = detected_squirrel_isr();
		break;
	case DISPENSING:
		FeederState = dispensing__isr();
		break;
	case JUST_DISPENSED:
		FeederState = just_dispensed_isr();
		break;
	case COOLDOWN:
		FeederState = cooldown_isr();
		break;
	}
}

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

	float avg_distance = ttl_distance / 4.0;
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
int weight = 0;
int squirrel_count = 0;

//void lcd_routine() {
//	// Initialization Calls
//  ILI9341_Unselect();
//  ILI9341_Init();
//
//	while(1) {
//		squirrel_clip();
//		HAL_Delay(1000);
//		ILI9341_FillScreen(ILI9341_WHITE);
//		display_stats(weight, squirrel_count);
//		HAL_Delay(1000);
//		ILI9341_FillScreen(ILI9341_WHITE);
//		squirrel_res();
//		HAL_Delay(1000);
//		ILI9341_FillScreen(ILI9341_WHITE);
//		display_stats(weight, squirrel_count);
//		HAL_Delay(1000);
//		ILI9341_FillScreen(ILI9341_WHITE);
//		m_logo();
//		HAL_Delay(1000);
//		ILI9341_FillScreen(ILI9341_WHITE);
//	}
//
//}


