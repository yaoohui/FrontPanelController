/*
*********************************************************************************************************
*
*	ģ������ : ST7789V оƬ����ģ�飨����SPI��
*	�ļ����� : lcd_st7789v.h
*	��    �� : V1.0
*	��    �� : ҫ�Թ�����   https://shop108339233.taobao.com/  
*	˵    �� : ST7789V �ײ�������4��SPI
*	�ӿ�˵�� ��
*-------------��ʾ�ӿ�------------------------------------
*				PB4 		LCD���⣬�������������Ч
*				PB0			DC
*				PB1			LCD��λ���͵�ƽ��λ
*				PA4			CS������Ч
*				PA5			SCK
*				PA6			MISO
*				PA7			MOSI
*-------------�������ӿ�------------------------------------
*				PB6			SCL ����I2Cʱ��
*				PB7			SDA	����I2C����
*				PB8			INT �����ж�
*				PB9			RST ������λ
*				
*	�޸ļ�¼ :
*		�汾��  ����        	����    ˵��
*		V1.0	2025��1��14��	yaoohui		
*
*********************************************************************************************************
*/

#ifndef __LCD_ST7789V2_H
#define __LCD_ST7789V2_H

#include "main.h"
#include "lv_port_disp.h"

//������ɫ
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
#define BROWN 			     (uint16_t)0XBC40 //��ɫ
#define BRRED 			     (uint16_t)0XFC07 //�غ�ɫ
#define GRAY  			     (uint16_t)0X8430 //��ɫ
#define DARKBLUE      	 (uint16_t)0X01CF	//����ɫ
#define LIGHTBLUE      	 (uint16_t)0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 (uint16_t)0X5458 //����ɫ
#define LIGHTGREEN     	 (uint16_t)0X841F //ǳ��ɫ
#define LGRAY 			     (uint16_t)0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        (uint16_t)0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           (uint16_t)0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


// LCD ��ʾ���ߴ�
#ifdef LCD_WA54HC046I // ���ֿ� 240*RGB*240

#define LCD_WIDTH       	240			/* ��Ļ��ȣ���λ������ */
#define LCD_HEIGHT      	240			/* ��Ļ�߶ȣ���λ������ */

#define MY_DISP_HOR_RES		LCD_WIDTH
#define MY_DISP_VER_RES		LCD_HEIGHT

#else

#define LCD_WIDTH       	240			/* ��Ļ��ȣ���λ������ */
#define LCD_HEIGHT      	280			/* ��Ļ�߶ȣ���λ������ */

#endif


// ST7789V ID��
#define ST7789V_ID  ((uint32_t)0x00778901)//((uint32_t)(0x00858552))

// ��Ļ��ʾ����
enum enum_DISPMODE
{
	DISP_NORMAL = 0,		// ������ʾ
	DISP_LEFT,				// ��Ļ������ת90�ȣ�������
	DISP_RIGHT,				// ��Ļ������ת90�ȣ�������
	DISP_DOWN,				// ��Ļ��ת180�ȣ�������
};

// LCD �ӿڶ���
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
