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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

#include "stdbool.h"
#include "gui_guider.h"

/*############################################################################*/

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */


#define VER 1.0


/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

extern volatile unsigned int LocalTime;	// 
extern volatile uint8_t touch_IRQ;		// 触摸中断次数
extern uint8_t tp_pressed;
extern bool begin_fb_flag;
extern char password[8];
extern lv_ui guider_ui;

/*############################################################################*/

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

// 微秒延时
void HAL_Delay_us(uint32_t us);

/*############################################################################*/

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TH_OUT_Pin GPIO_PIN_3
#define TH_OUT_GPIO_Port GPIOC
#define HWRST_Pin GPIO_PIN_0
#define HWRST_GPIO_Port GPIOA
#define PWR_Pin GPIO_PIN_1
#define PWR_GPIO_Port GPIOA
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define DC_Pin GPIO_PIN_0
#define DC_GPIO_Port GPIOB
#define RES_Pin GPIO_PIN_1
#define RES_GPIO_Port GPIOB
#define EEPROM_SCL_Pin GPIO_PIN_10
#define EEPROM_SCL_GPIO_Port GPIOB
#define EEPROM_SDA_Pin GPIO_PIN_11
#define EEPROM_SDA_GPIO_Port GPIOB
#define BLC_Pin GPIO_PIN_8
#define BLC_GPIO_Port GPIOA
#define PWR_STD_Pin GPIO_PIN_9
#define PWR_STD_GPIO_Port GPIOA
#define HDD_STD_Pin GPIO_PIN_10
#define HDD_STD_GPIO_Port GPIOA
#define TP_SCL_Pin GPIO_PIN_6
#define TP_SCL_GPIO_Port GPIOB
#define TP_SDA_Pin GPIO_PIN_7
#define TP_SDA_GPIO_Port GPIOB
#define TP_INT_Pin GPIO_PIN_8
#define TP_INT_GPIO_Port GPIOB
#define TP_INT_EXTI_IRQn EXTI9_5_IRQn
#define TP_RST_Pin GPIO_PIN_9
#define TP_RST_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

#define TP_I2C_GPIO_Port				GPIOB
#define EEPROM_I2C_GPIO_Port		GPIOB

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
