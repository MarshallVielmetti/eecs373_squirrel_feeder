/*
 * load_cell.c
 *
 *  Created on: Dec 3, 2024
 *      Author: mvielmet
 */

#include "load_cell.h"
#include "main.h"

/*
 * Make sure to correctly rename pins in ioc
 * PS0_DATA, PS0_CLK
 *
 * PS1_DATA, PS1_CLK
 */

// scaling
#define PS0_TARE 8532000
//static uint32_t tare = 8482978; // set to zero value
static float knownOriginal = 171000;  // in milli gram
static float knownHX711 = -65335;

#define NUM_PS_SAMPLES 5

extern TIM_HandleTypeDef PS_TIMER_HANDLE;

static int CURRENT_READING = 0;


/*
 * Really short delay function
 */
static void microDelay(uint16_t delay)
{
	return;
  __HAL_TIM_SET_COUNTER(&PS_TIMER_HANDLE, 0);
  while (__HAL_TIM_GET_COUNTER(&PS_TIMER_HANDLE) < delay);
}

/*
 * reads in data value from HX711
 */
static int32_t getHX711(void)
{
	__disable_irq(); // ENTER CRITICAL SECTION
  uint32_t data = 0;
  uint32_t startTime = HAL_GetTick();
  while(HAL_GPIO_ReadPin(PS0_DATA_GPIO_Port, PS0_DATA_Pin) == GPIO_PIN_SET)
  {
	// weird
    if(HAL_GetTick() - startTime > 200) {
      __enable_irq();
      return 0;
    }
  }

  for(int8_t len=0; len<24 ; len++)
  {
    HAL_GPIO_WritePin(PS0_CLK_GPIO_Port, PS0_CLK_Pin, GPIO_PIN_SET);
    microDelay(1);
    data = data << 1;
    HAL_GPIO_WritePin(PS0_CLK_GPIO_Port, PS0_CLK_Pin, GPIO_PIN_RESET);
    microDelay(1);
    if(HAL_GPIO_ReadPin(PS0_DATA_GPIO_Port, PS0_DATA_Pin) == GPIO_PIN_SET)
      data ++;
  }

  data = data ^ 0x800000;

  /*
   * END BIT
   */
  HAL_GPIO_WritePin(PS0_CLK_GPIO_Port, PS0_CLK_Pin, GPIO_PIN_SET);
  microDelay(1);
  HAL_GPIO_WritePin(PS0_CLK_GPIO_Port, PS0_CLK_Pin, GPIO_PIN_RESET);
  microDelay(1);

  __enable_irq();

  return data;
}


static int weigh()
{
  int32_t  total = 0;
  int milligram;
  float coefficient;

  // average out NUM_PS_SAMPLES
  for(uint16_t i=0 ; i<NUM_PS_SAMPLES ; i++)
  {
      total += getHX711();
  }

  int32_t average = (int32_t)(total / NUM_PS_SAMPLES);
  coefficient = knownOriginal / knownHX711;
  milligram = (int)(average-PS0_TARE)*coefficient;
  return milligram;
}


void ps_init() {};

static bool NEEDS_READING = false;

void ps_take_reading() {
	NEEDS_READING = false;
	CURRENT_READING = weigh();
}

int ps_get_reading() {
	return CURRENT_READING;
}


// sets whether or not the pressure sensor needs to take a reading
void ps_set_needs_reading(bool val) {
	NEEDS_READING = val;
}

// returns whether or not the pressure sensor needs to take a reading
bool ps_needs_reading() {
	return NEEDS_READING;
}
