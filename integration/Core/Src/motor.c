/*
 * motor.c
 *
 *  Created on: Dec 3, 2024
 *      Author: mvielmet
 */

#include "motor.h"
#include "main.h"

#include <stdbool.h>

extern TIM_HandleTypeDef MOTOR_TIMER_HANDLE;


/*
 * Make sure to define the motor ports in the ioc file
 */

#define MOTOR_DELAY 2

// Define step sequence for clockwise rotation
static int steps[8][4] =
	{ {1, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 1, 1},
	{0, 0, 0, 1},
	{1, 0, 0, 1} };

static bool motor_running = false;
static uint32_t cur_rotation_idx = 0;

void stepper_rotate_clockwise_ir() {
	 HAL_GPIO_WritePin(M0_0_GPIO_Port, M0_0_Pin, steps[cur_rotation_idx][0]);
	 HAL_GPIO_WritePin(M0_1_GPIO_Port, M0_1_Pin, steps[cur_rotation_idx][1]);
	 HAL_GPIO_WritePin(M0_2_GPIO_Port, M0_2_Pin, steps[cur_rotation_idx][2]);
	 HAL_GPIO_WritePin(M0_3_GPIO_Port, M0_3_Pin, steps[cur_rotation_idx][3]);

	 // ALSO M1 TODO

	 cur_rotation_idx++;
	 if (cur_rotation_idx == 8) {
		 cur_rotation_idx = 0;
	 }
}



//void stepper_rotate_clockwise_steps(uint32_t num_rotations) {
//	if (!motor_is_ready) {
//		return; //already running
//	}
//
//	motor_is_ready = false;
//
//	num_steps = num_rotations;
//	num_steps_completed = 0;
//	cur_rotation_idx = 0;
//
//	// enable motor timer interrupt
//	HAL_TIM_Base_Start_IT(&MOTOR_TIMER_HANDLE);
//}

void motor_start() {
	if (motor_running) {
		return;
	}

	motor_running = true;
	HAL_TIM_Base_Start_IT(&MOTOR_TIMER_HANDLE);
}

void motor_stop() {
	if (!motor_running) {
		return;
	}

	motor_running = false;
	HAL_TIM_Base_Stop_IT(&MOTOR_TIMER_HANDLE);
}



