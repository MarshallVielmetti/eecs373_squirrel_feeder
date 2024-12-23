#include "integration.h"

#include <stdbool.h>

#ifndef INC_LCD_H_
#define INC_LCD_H_

// give sthe LCD a const pointer to the feeder object
void lcd_init(const Feeder* feeder);

void lcd_update();


/*
 * Tells the LCD to display a picture of a squirrel
 */
void squirrel_clip();

/*
 * Tells the LCD to display a different squirrel res image
 */
void squirrel_res();

/*
 * Changes the LCd to display a Michigan logo
 */
void m_logo();

void display_stats(int weight, int squirrel_count);
void lcd_between();

void lcd_trigger_update();

bool lcd_needs_update();

#endif
