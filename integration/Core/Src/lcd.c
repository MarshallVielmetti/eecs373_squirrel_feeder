#include "main.h"

#include "integration.h"
#include "camera_handler.h"

#include "ili9341.h"
#include "fonts.h"
#include "test_squirrel_1.h"
#include "test_squirrel_2.h"
#include "test_umich_1.h"
#include "white_screen.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
//
extern SPI_HandleTypeDef hspi3;
extern TIM_HandleTypeDef LCD_TIMER_HANDLE;

static const Feeder* lcd_feeder_ref;

static bool IS_STATS = false;

enum LcdStateType {
	SQUIRREL_CLIP,
	SQUIRREL_HD,
	M_LOGO,
} LcdState;

void lcd_init(const Feeder* feeder) {
	ILI9341_Unselect();
	ILI9341_Init();

	lcd_feeder_ref = feeder;
	LcdState = SQUIRREL_CLIP;
}

static void lcd_between(){
//	HAL_Delay(1000);
//	ILI9341_FillScreen(ILI9341_WHITE);
	ILI9341_DrawImage(0,0,320,240,(const uint16_t*)white_screen_map);
}




void squirrel_clip() {
	ILI9341_DrawImage((ILI9341_WIDTH - 320)/2,(ILI9341_HEIGHT-240)/2,320,240,(const uint16_t*)squirrelclip);
	LcdState = SQUIRREL_HD;
}

void squirrel_res() {
	ILI9341_DrawImage((ILI9341_WIDTH - 320)/2,(ILI9341_HEIGHT-213)/2,320,213,(const uint16_t*)squirrelres);
	LcdState = M_LOGO;
}

void m_logo() {
	ILI9341_DrawImage((ILI9341_WIDTH - 320)/2,(ILI9341_HEIGHT-203)/2,320,203,(const uint16_t*)MLogo);
	LcdState = SQUIRREL_CLIP;
}

void display_stats() {
	const char* team1 = "FEED";
	const char* team2 = "THE";
	const char* team3 = "SQUIRRELS";
	const char* class = "FROM EECS 373";
	const char* linebrk = "-*-*-*-*-*-";

	// Needs help
	char str_squirrels_fed[20];
	sprintf(str_squirrels_fed, "Squirrels Fed: %lu", lcd_feeder_ref->squirrel_count);
//	char strWeight[4];
//	sprintf(strWeight, "%d", weight);

//	const char* squcount = strcat("Squirrels Fed: ", strSquirrels);
//	const char* flevels = strcat("Food Dispensed: ", strWeight);

	// FEED THE SQUIRRELS FROM EECS 383 -*-*-*-*-*
	ILI9341_WriteString(10, 10, team1, Font_16x26, ILI9341_YELLOW, ILI9341_BLUE);
	ILI9341_WriteString(10, 40, team2, Font_16x26, ILI9341_YELLOW, ILI9341_BLUE);
	ILI9341_WriteString(10, 70, team3, Font_16x26, ILI9341_YELLOW, ILI9341_BLUE);
	ILI9341_WriteString(10, 100, class, Font_11x18, ILI9341_YELLOW, ILI9341_BLUE);
	ILI9341_WriteString(10, 130, linebrk, Font_11x18, ILI9341_YELLOW, ILI9341_BLUE);

	// Squirrels Fed: squcount
	// Food Dispensed: strWeight
	ILI9341_WriteString(10, 160, str_squirrels_fed, Font_11x18, ILI9341_YELLOW, ILI9341_BLUE);
//	ILI9341_WriteString(10, 190, flevels, Font_11x18, ILI9341_YELLOW, ILI9341_BLUE);

	// DISPLAY CAMERA STATUS
	char camera_ready[40];
	if (camera_get_ready()) {
		sprintf(camera_ready, "Camera: Ready");
	} else {
		sprintf(camera_ready, "Camera: %lu%% Done", camera_get_percent_done());
	}

	ILI9341_WriteString(10, 190, camera_ready, Font_11x18, ILI9341_YELLOW, ILI9341_BLUE);
}

// DISPLAY OUT OF FOOD WARNING
void display_out_of_food() {
	const char* out_of_food_str = "!! OUT OF FOOD !!";
	ILI9341_WriteString(10, 70, out_of_food_str, Font_16x26, ILI9341_YELLOW, ILI9341_BLUE);
}

static bool LCD_UPDATE = false;

// MAIN LCD SERVICE ROUTINE
void lcd_update() {
	IS_STATS = !IS_STATS;

	lcd_between();

	if (IS_STATS) {
		printf("lcd - transition to statistics\n\r");
		display_stats();
	} else if (lcd_feeder_ref->state == OUT_OF_FOOD) {
		printf("lcd - transition to no food warning\n\r");
		display_out_of_food();
	} else {
		switch(LcdState) {
		case SQUIRREL_CLIP:
			printf("lcd - transition to squirrel clip\n\r");
			squirrel_clip();
			break;
		case SQUIRREL_HD:
			printf("lcd - transition to squirrel res\n\r");
			squirrel_res();
			break;
		case M_LOGO:
			printf("lcd - transition to M logo\n\r");
			m_logo();
			break;
		}
	}

	LCD_UPDATE = false;
}

void lcd_trigger_update() {
	LCD_UPDATE = true;
}

bool lcd_needs_update() {
	return LCD_UPDATE;
}



