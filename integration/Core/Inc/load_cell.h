/*
 * load_cell.h
 *
 *  Created on: Dec 3, 2024
 *      Author: mvielmet
 */

#ifndef INC_LOAD_CELL_H_
#define INC_LOAD_CELL_H_


// initialize the load cell
void ps_init();

void ps_isr();

int ps_get_reading();


#endif /* INC_LOAD_CELL_H_ */
