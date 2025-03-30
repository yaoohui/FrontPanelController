#ifndef __TOUCH_CST816D
#define __TOUCH_CST816D

#include "main.h"
#include "i2c.h"

#define CST816D_I2C									hi2c1

#define CST816D_CMD_WR							0x2A		// 写地址
#define CST816D_CMD_RD							0x2B		// 读地址

#define CST816D_DEVIDE_MODE					0x00		// CST816模式控制寄存器
#define CST816D_REG_NUM_FINGER			0x02		// 触摸状态寄存器

#define CST816D_TP1_REG							0X03		// 第一个触摸点数据地址
#define CST816D_TP2_REG							0X09		// 第二个触摸点数据地址
#define CST816D_TP3_REG							0X0F		// 第三个触摸点数据地址
#define CST816D_TP4_REG							0X15		// 第四个触摸点数据地址
#define CST816D_TP5_REG							0X1B		// 第五个触摸点数据地址

#define CST816D_ID_G_LIB_VERSION		0xA1		// 版本
#define CST816D_ID_G_MODE						0xA4		// CST816中断模式控制寄存器
#define CST816D_ID_G_THGROUP				0x80		// 触摸有效值设置寄存器
#define CST816D_ID_G_PERIODACTIVE 	0x88		// 激活状态周期设置寄存器

#define Chip_Vendor_ID							0xA7		// 芯片ID(0x36)
#define ID_G_CST816ID								0xA8		// 0x11

#define TP_PRES_DOWN								0x81		// 触屏被按下
#define TP_COORD_UD									0x40 		// 触摸坐标更新标记

// 触摸复位
#define CST816_RST(x)			x?		HAL_GPIO_WritePin(TP_RST_GPIO_Port, TP_RST_Pin, GPIO_PIN_SET):\
																HAL_GPIO_WritePin(TP_RST_GPIO_Port, TP_RST_Pin, GPIO_PIN_RESET)

//触摸点相关数据结构体定义
typedef struct
{
	uint8_t TouchSta;		//触摸情况，b7:按下1/松开0; b6:0没有按键按下/1有按键按下;bit5:保留；bit4-bit0触摸点按下有效标志，有效为1，分别对应触摸点5-1；
	uint16_t x[5];			//支持5点触摸，需要使用5组坐标存储触摸点数据
	uint16_t y[5];
}TouchPointRefTypeDef;

extern uint16_t touch_x, touch_y;

void CST816D_Write_Reg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen);
void CST816D_Read_Reg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen);
void CST816D_Init(void);
void CST816D_Scan(void);

#endif