/*
 * motor.h
 *
 *  Created on: Dec 3, 2024
 *      Author: mvielmet
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include <stdint.h>

//void stepper_rotate_clockwise_steps(uint32_t num_rotations);

// start motor
void motor_start();

// stop motor
void motor_stop();

// called by interrupt routine
void stepper_rotate_clockwise_ir();


#endif /* INC_MOTOR_H_ */
