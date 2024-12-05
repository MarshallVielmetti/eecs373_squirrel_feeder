#include "main.h"
#include <string.h>
#include <stdarg.h>
#include "ili9341.h"
#include "fonts.h"
#include "test_squirrel_1.h"
#include "test_squirrel_2.h"
#include "test_umich_1.h"
#include <stdio.h>
//
extern SPI_HandleTypeDef hspi3;
extern TIM_HandleTypeDef LCD_TIMER_HANDLE;

void squirrel_clip() {
	ILI9341_DrawImage((ILI9341_WIDTH - 320)/2,(ILI9341_HEIGHT-240)/2,320,240,(const uint16_t*)squirrelclip);
}

void squirrel_res() {
	ILI9341_DrawImage((ILI9341_WIDTH - 320)/2,(ILI9341_HEIGHT-213)/2,320,213,(const uint16_t*)squirrelres);
}

void m_logo() {
	ILI9341_DrawImage((ILI9341_WIDTH - 320)/2,(ILI9341_HEIGHT-203)/2,320,203,(const uint16_t*)MLogo);
}

void display_stats(int weight, int squirrel_count) {
	const char* team1 = "FEED";
	const char* team2 = "THE";
	const char* team3 = "SQUIRRELS";
	const char* class = "FROM EECS 373";
	const char* linebrk = "-*-*-*-*-*-";
	// Needs help
	char strSquirrels[4];
	sprintf(strSquirrels, "%d", squirrel_count);
	char strWeight[4];
	sprintf(strWeight, "%d", weight);

	const char* squcount = strcat("Squirrels Fed: ", strSquirrels);
	const char* flevels = strcat("Food Dispensed: ", strWeight);
	ILI9341_WriteString(10, 10, team1, Font_16x26, ILI9341_YELLOW, ILI9341_BLUE);
	ILI9341_WriteString(10, 40, team2, Font_16x26, ILI9341_YELLOW, ILI9341_BLUE);
	ILI9341_WriteString(10, 70, team3, Font_16x26, ILI9341_YELLOW, ILI9341_BLUE);
	ILI9341_WriteString(10, 100, class, Font_11x18, ILI9341_YELLOW, ILI9341_BLUE);
	ILI9341_WriteString(10, 130, linebrk, Font_11x18, ILI9341_YELLOW, ILI9341_BLUE);
	ILI9341_WriteString(10, 160, squcount, Font_11x18, ILI9341_YELLOW, ILI9341_BLUE);
	ILI9341_WriteString(10, 190, flevels, Font_11x18, ILI9341_YELLOW, ILI9341_BLUE);
}

void lcd_init() {
	ILI9341_Unselect();
	ILI9341_Init();
}
void lcd_between(){
	HAL_Delay(1000);
	ILI9341_FillScreen(ILI9341_WHITE);
}
