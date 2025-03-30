#ifndef INC_IO_H_
#define INC_IO_H_

#include "main.h"


// 启动和复位继电器宏定义
#define HWRST(x)			x?		HAL_GPIO_WritePin(HWRST_GPIO_Port, HWRST_Pin, GPIO_PIN_SET):\
														HAL_GPIO_WritePin(HWRST_GPIO_Port, HWRST_Pin, GPIO_PIN_RESET)
#define HWPWR(x)			x?		HAL_GPIO_WritePin(PWR_GPIO_Port, PWR_Pin, GPIO_PIN_SET):\
														HAL_GPIO_WritePin(PWR_GPIO_Port, PWR_Pin, GPIO_PIN_RESET)

// LCD背光
#define LCD_BL(x)			x?		HAL_GPIO_WritePin(BLC_GPIO_Port, BLC_Pin, GPIO_PIN_SET):\
														HAL_GPIO_WritePin(BLC_GPIO_Port, BLC_Pin, GPIO_PIN_RESET)
// LCD复位
#define LCD_RESET(x)	x?		HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_SET):\
														HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_RESET)

#define PWR_STD							HAL_GPIO_ReadPin(PWR_STD_GPIO_Port, PWR_STD_Pin)
#define HDD_STD							HAL_GPIO_ReadPin(HDD_STD_GPIO_Port, HDD_STD_Pin)
#define LED_BL_STD          HAL_GPIO_ReadPin(BLC_GPIO_Port, BLC_Pin)

void Check_PWR_Std(void);


#endif /* INC_IO_H_ */
