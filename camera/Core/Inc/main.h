/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdint.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PS1_CLK_Pin GPIO_PIN_0
#define PS1_CLK_GPIO_Port GPIOF
#define PS1_DATA_Pin GPIO_PIN_1
#define PS1_DATA_GPIO_Port GPIOF
#define M1_2_Pin GPIO_PIN_3
#define M1_2_GPIO_Port GPIOF
#define M1_3_Pin GPIO_PIN_5
#define M1_3_GPIO_Port GPIOF
#define PS0_CLK_Pin GPIO_PIN_1
#define PS0_CLK_GPIO_Port GPIOC
#define PS0_DATA_Pin GPIO_PIN_3
#define PS0_DATA_GPIO_Port GPIOC
#define SD_SCK_Pin GPIO_PIN_5
#define SD_SCK_GPIO_Port GPIOA
#define SD_MISO_Pin GPIO_PIN_6
#define SD_MISO_GPIO_Port GPIOA
#define SD_MOSI_Pin GPIO_PIN_7
#define SD_MOSI_GPIO_Port GPIOA
#define IR0_ADC_Pin GPIO_PIN_4
#define IR0_ADC_GPIO_Port GPIOC
#define IR1_ADC_Pin GPIO_PIN_5
#define IR1_ADC_GPIO_Port GPIOC
#define LCD_CS_Pin GPIO_PIN_14
#define LCD_CS_GPIO_Port GPIOF
#define LCD_DC_Pin GPIO_PIN_15
#define LCD_DC_GPIO_Port GPIOF
#define LCD_RESET_Pin GPIO_PIN_13
#define LCD_RESET_GPIO_Port GPIOE
#define CAM_TX_Pin GPIO_PIN_8
#define CAM_TX_GPIO_Port GPIOD
#define CAM_RX_Pin GPIO_PIN_9
#define CAM_RX_GPIO_Port GPIOD
#define SD_CS_Pin GPIO_PIN_14
#define SD_CS_GPIO_Port GPIOD
#define M0_0_Pin GPIO_PIN_8
#define M0_0_GPIO_Port GPIOC
#define M0_1_Pin GPIO_PIN_9
#define M0_1_GPIO_Port GPIOC
#define M0_2_Pin GPIO_PIN_10
#define M0_2_GPIO_Port GPIOC
#define M0_3_Pin GPIO_PIN_11
#define M0_3_GPIO_Port GPIOC
#define M1_0_Pin GPIO_PIN_12
#define M1_0_GPIO_Port GPIOC
#define M1_1_Pin GPIO_PIN_2
#define M1_1_GPIO_Port GPIOD
#define LCD_SCK_Pin GPIO_PIN_3
#define LCD_SCK_GPIO_Port GPIOB
#define LCD_MOSI_Pin GPIO_PIN_5
#define LCD_MOSI_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define SD_SPI_HANDLE hspi1
#define IR_ADC_HANDLE hadc1
#define PS_TIMER_HANDLE htim2
#define CAM_UART_HANDLE huart3

#define IR0_ADC_CHANNEL ADC_CHANNEL_13
#define IR1_ADC_CHANNEL ADC_CHANNEL_14

#define CAM_TIMER_HANDLE htim3
#define MOTOR_TIMER_HANDLE htim4
#define IR_SENSOR_TIMER_HANDLE htim5
#define MAIN_TIMER_HANDLE htim16

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
