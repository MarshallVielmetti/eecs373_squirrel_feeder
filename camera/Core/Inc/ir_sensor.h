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

// returns the average 8 most recent distance readings
float get_cur_distance_average();

#endif /* INC_IR_SENSOR_H_ */
