/*
 * load_cell.h
 *
 *  Created on: Dec 3, 2024
 *      Author: mvielmet
 */

#include <stdbool.h>

#ifndef INC_LOAD_CELL_H_
#define INC_LOAD_CELL_H_


// initialize the load cell
void ps_init();

void ps_take_reading();

// sets whether or not the pressure sensor needs to take a reading
void ps_set_needs_reading(bool val);

// returns whether or not the pressure sensor needs to take a reading
bool ps_needs_reading();

int ps_get_reading();


#endif /* INC_LOAD_CELL_H_ */
