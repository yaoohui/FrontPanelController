/*
*********************************************************************************************************
*
*	模块名称 : ST7789V 芯片驱动模块（串行SPI）
*	文件名称 : lcd_st7789v.h
*	版    本 : V1.0
*	作    者 : 耀辉工作室   https://shop108339233.taobao.com/  
*	说    明 : ST7789V 底层驱动，4线SPI
*	接口说明 ：
*-------------显示接口------------------------------------
*				PB4 		LCD背光，推挽输出，高有效
*				PB0			DC
*				PB1			LCD复位，低电平复位
*				PA4			CS，低有效
*				PA5			SCK
*				PA6			MISO
*				PA7			MOSI
*-------------触摸屏接口------------------------------------
*				PB6			SCL 触摸I2C时钟
*				PB7			SDA	触摸I2C数据
*				PB8			INT 触摸中断
*				PB9			RST 触摸复位
*				
*	修改记录 :
*		版本号  日期        	作者    说明
*		V1.0	2025年1月14日	yaoohui		
*
*********************************************************************************************************
*/

#ifndef __LCD_ST7789V2_H
#define __LCD_ST7789V2_H

#include "main.h"
#include "lv_port_disp.h"

//画笔颜色
#define WHITE         	 (uint16_t)0xFFFF
#define BLACK         	 (uint16_t)0x0000	  
#define BLUE           	 (uint16_t)0x001F  
#define BRED             (uint16_t)0XF81F
#define GRED 			       (uint16_t)0XFFE0
#define GBLUE			       (uint16_t)0X07FF
#define RED           	 (uint16_t)0xF800
#define MAGENTA       	 (uint16_t)0xF81F
#define GREEN         	 (uint16_t)0x07E0
#define CYAN          	 (uint16_t)0x7FFF
#define YELLOW        	 (uint16_t)0xFFE0
#define BROWN 			     (uint16_t)0XBC40 //棕色
#define BRRED 			     (uint16_t)0XFC07 //棕红色
#define GRAY  			     (uint16_t)0X8430 //灰色
#define DARKBLUE      	 (uint16_t)0X01CF	//深蓝色
#define LIGHTBLUE      	 (uint16_t)0X7D7C	//浅蓝色  
#define GRAYBLUE       	 (uint16_t)0X5458 //灰蓝色
#define LIGHTGREEN     	 (uint16_t)0X841F //浅绿色
#define LGRAY 			     (uint16_t)0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        (uint16_t)0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           (uint16_t)0X2B12 //浅棕蓝色(选择条目的反色)


// LCD 显示屏尺寸
#ifdef LCD_WA54HC046I // 沃乐康 240*RGB*240

#define LCD_WIDTH       	240			/* 屏幕宽度，单位：像素 */
#define LCD_HEIGHT      	240			/* 屏幕高度，单位：像素 */

#define MY_DISP_HOR_RES		LCD_WIDTH
#define MY_DISP_VER_RES		LCD_HEIGHT

#else

#define LCD_WIDTH       	240			/* 屏幕宽度，单位：像素 */
#define LCD_HEIGHT      	280			/* 屏幕高度，单位：像素 */

#endif


// ST7789V ID号
#define ST7789V_ID  ((uint32_t)0x00778901)//((uint32_t)(0x00858552))

// 屏幕显示方向
enum enum_DISPMODE
{
	DISP_NORMAL = 0,		// 正常显示
	DISP_LEFT,				// 屏幕向左旋转90度，上在左
	DISP_RIGHT,				// 屏幕向右旋转90度，上在右
	DISP_DOWN,				// 屏幕旋转180度，上在下
};

// LCD 接口定义
#define ST7789V_RST(x)		x?		HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_SET):\
																HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_RESET)

#define ST7789V_DC(x)			x?		HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET):\
																HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET)

#define ST7789V_CS(x)			x?		HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET):\
																HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET)

uint8_t Spi_Read_Byte(void);
uint8_t Spi_Send_Byte(uint8_t byte);
void ST7789V_Write_Reg(uint16_t _ucRegAddr, uint16_t _ucRegValue);
uint16_t ST7789V_Read_Reg(uint16_t _ucRegAddr);
uint8_t ST7789V_Read_ID(uint32_t *_id);
void ST7789V_Set_Display_Mode(uint8_t _mode);
void ST7789V_Vertical_Refresh_Order(uint8_t _bottom2top);
void ST7789V_Reset(void);
void ST7789V_Init(void);
void ST7789V_Clear(uint16_t _Color);
void ST7789V_Set_Windows(uint16_t _x0, uint16_t _y0, uint16_t _x1, uint16_t _y1);
void ST7789V_Display_On(void);
void ST7789V_Display_Off(void);
void ST7789V_Draw_Pixel(uint16_t _x, uint16_t _y, uint16_t _Color);
void LCD_color_fill_lvgl(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lv_color_t *color);
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

#endif
