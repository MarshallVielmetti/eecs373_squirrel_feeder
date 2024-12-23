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
#include <stdbool.h>
#include <stdio.h>

extern TIM_HandleTypeDef IR_SENSOR_TIMER_HANDLE;
extern TIM_HandleTypeDef MAIN_TIMER_HANDLE;
extern TIM_HandleTypeDef LCD_TIMER_HANDLE;


// DECLARATION OF FEEDER OBJECT
static Feeder feeder;

#define IR_DISTANCE_THRESHOLD 1200 	// Threshold to determine IR sensor trigger - Need to confirm voltage vs. distance for IR sensor reading
#define PS_FOOD_THRESHOLD 15000		// Max weight (mg) of food on tray
#define PS_RESET_THRESHOLD 100000	// Put your hand on the feeder to reset it from the out_of_food state after refill
#define COOLDOWN_ISR_ITERATIONS 20

#define MIN_DISPENSE_ITERATIONS 3
#define MAX_DISPENSE_ITERATIONS 7


void init_peripherals() {
	HAL_Delay(2500);

	camera_init();

	ir_sensor_init();
	ps_init();

	// shared between the IR sensor and pressure sensor
	HAL_TIM_Base_Start_IT(&IR_SENSOR_TIMER_HANDLE);

	lcd_init(&feeder);

	feeder.state = WAITING_FOR_SQUIRREL;
	feeder.squirrel_count = 0;
	feeder.out_of_food = false;

	// start main timer
	HAL_TIM_Base_Start_IT(&MAIN_TIMER_HANDLE);

	// start LCD timer
	HAL_TIM_Base_Start_IT(&LCD_TIMER_HANDLE);

}

static void waiting_for_squirrel_isr();
static void detected_squirrel_isr();
static void dispensing_isr();
static void cooldown_isr();
static void out_of_food_isr();

// main program logic interrupt routine
void main_isr() {
	printf("\n\r\n\r#### Main Service Routine ###\n\r");

	// send the feeder state to the lcd and update it
	switch (feeder.state) {
	case WAITING_FOR_SQUIRREL:
		printf("state -- waiting for squirrel\n\r");
		waiting_for_squirrel_isr();
		break;
	case DETECTED_SQUIRREL:
		printf("state -- detected squirrel\n\r");
		detected_squirrel_isr();
		break;
	case DISPENSING:
		printf("state -- dispensing\n\r");
		dispensing_isr();
		break;
	case COOLDOWN:
		printf("state -- cooldown\n\r");
		cooldown_isr();
		break;
	case OUT_OF_FOOD:
		printf("state -- out of food\n\r");
		out_of_food_isr();
		break;
	}
}

static void waiting_for_squirrel_isr() {
	printf("Current Distance Reading: %f\n\r", get_cur_distance_average());

	if(get_cur_distance_average() > IR_DISTANCE_THRESHOLD) {
		printf("DETECTED SQUIRREL!\n\r");
		feeder.state = DETECTED_SQUIRREL;
	}
}

static void detected_squirrel_isr() {
	feeder.squirrel_count++;

	feeder.needs_to_take_picture = true;

	motor_start();

	feeder.state = DISPENSING;

	// clear IR camera buffer
	zero_averages();
}

static uint32_t times_dispensed = 0;
static void dispensing_isr() {
	printf("Times Dispensed: %d\n\r", times_dispensed);
	printf("PS reading: %d,  Threshold: %d (mg)\n\r", ps_get_reading(), PS_FOOD_THRESHOLD);

	if (ps_get_reading() >= PS_FOOD_THRESHOLD && times_dispensed >= MIN_DISPENSE_ITERATIONS) {
		printf("Transitioning to COOLDOWN\n\r");
		// Must have dispensed enough food
		motor_stop();
		feeder.needs_to_process_picture = true;

		feeder.state = COOLDOWN;
		times_dispensed = 0;

		return;
	}

	if (times_dispensed >= MAX_DISPENSE_ITERATIONS) {
		printf("Transitioning to out_of_food state\n\r");
		// has dispensed 5 times on this iteration already -- out of food
		motor_stop();
		feeder.needs_to_process_picture = true;

		feeder.state = OUT_OF_FOOD;
		times_dispensed = 0;

		return;
	}

	// Down here is "average" use case -- needs to continue dispensing
	++times_dispensed;

	// Stay in the same state
	feeder.state = DISPENSING;
}

/*
 * Prevents the system from dispensing food over and over again
 */
static uint32_t cooldown_cur_iteration = 0;
static void cooldown_isr(void) {

	cooldown_cur_iteration += 1;

	printf("Current cooldown iteration: %d\n\r", cooldown_cur_iteration);

	if (cooldown_cur_iteration == COOLDOWN_ISR_ITERATIONS) {
		cooldown_cur_iteration = 0;
		feeder.state = WAITING_FOR_SQUIRREL;
	}
}

// In order to reset the feeder, just put your hand on the pressure sensor
static void out_of_food_isr() {	// We don't have a great way to determine when food is added back
	feeder.out_of_food = true;

	printf("Current PS Reading: %d\n\r", ps_get_reading());

	if (ps_get_reading() > PS_RESET_THRESHOLD) {
		feeder.out_of_food = false;
		feeder.state = WAITING_FOR_SQUIRREL;
	}
}

Feeder *get_feeder() {
	return &feeder;
}







