/*
 * integration.h
 *
 *  Created on: Dec 3, 2024
 *      Author: mvielmet
 */

#ifndef INC_INTEGRATION_H_
#define INC_INTEGRATION_H_

#include <stdbool.h>

typedef enum FeederStateType {
	WAITING_FOR_SQUIRREL, 	// Default system state -- polling IR sensor for a squirrel
	DETECTED_SQUIRREL,		// Squirrel candidate detected!
	DISPENSING,				// Dispense some food
	COOLDOWN,				// Cooldown state to prevent food from being dispensed too rapidly
	OUT_OF_FOOD
} FeederState;

typedef struct FeederType {
	// Current state of the feeder
	FeederState state;

	// The number of squirrels fed
	uint32_t squirrel_count;

	// Whether or not the feeder is out of food
	bool out_of_food;

	// whether or not the camera needs to take a picture
	bool needs_to_take_picture;
	bool needs_to_process_picture;
} Feeder;

// This must be called first -- initializes main system objects
void init_main();

// This must be called second -- initializes all peripherals to start polling correctly and performs first time setup
void init_peripherals();

// Main ISR routine called by the main timer interrupt handler
void main_isr();

void perform_startup_routine();

void simple_IR_trigger();

Feeder *get_feeder();


// External functions


#endif /* INC_INTEGRATION_H_ */
