/*
 * ir_sensor.h
 *
 *  Created on: Dec 3, 2024
 *      Author: mvielmet
 */

#ifndef INC_IR_SENSOR_H_
#define INC_IR_SENSOR_H_

void ir_sensor_init();

void ir_sensor_interrupt_routine();

// returns an average measurement as set by NUM_MEASUREMENTS_TO_AVG
float get_cur_distance_average();

void zero_averages();

#endif /* INC_IR_SENSOR_H_ */
