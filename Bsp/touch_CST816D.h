#ifndef __TOUCH_CST816D
#define __TOUCH_CST816D

#include "main.h"
#include "i2c.h"

#define CST816D_I2C									hi2c1

#define CST816D_CMD_WR							0x2A		// д��ַ
#define CST816D_CMD_RD							0x2B		// ����ַ

#define CST816D_DEVIDE_MODE					0x00		// CST816ģʽ���ƼĴ���
#define CST816D_REG_NUM_FINGER			0x02		// ����״̬�Ĵ���

#define CST816D_TP1_REG							0X03		// ��һ�����������ݵ�ַ
#define CST816D_TP2_REG							0X09		// �ڶ������������ݵ�ַ
#define CST816D_TP3_REG							0X0F		// ���������������ݵ�ַ
#define CST816D_TP4_REG							0X15		// ���ĸ����������ݵ�ַ
#define CST816D_TP5_REG							0X1B		// ��������������ݵ�ַ

#define CST816D_ID_G_LIB_VERSION		0xA1		// �汾
#define CST816D_ID_G_MODE						0xA4		// CST816�ж�ģʽ���ƼĴ���
#define CST816D_ID_G_THGROUP				0x80		// ������Чֵ���üĴ���
#define CST816D_ID_G_PERIODACTIVE 	0x88		// ����״̬�������üĴ���

#define Chip_Vendor_ID							0xA7		// оƬID(0x36)
#define ID_G_CST816ID								0xA8		// 0x11

#define TP_PRES_DOWN								0x81		// ����������
#define TP_COORD_UD									0x40 		// ����������±��

// ������λ
#define CST816_RST(x)			x?		HAL_GPIO_WritePin(TP_RST_GPIO_Port, TP_RST_Pin, GPIO_PIN_SET):\
																HAL_GPIO_WritePin(TP_RST_GPIO_Port, TP_RST_Pin, GPIO_PIN_RESET)

//������������ݽṹ�嶨��
typedef struct
{
	uint8_t TouchSta;		//���������b7:����1/�ɿ�0; b6:0û�а�������/1�а�������;bit5:������bit4-bit0�����㰴����Ч��־����ЧΪ1���ֱ��Ӧ������5-1��
	uint16_t x[5];			//֧��5�㴥������Ҫʹ��5������洢����������
	uint16_t y[5];
}TouchPointRefTypeDef;

extern uint16_t touch_x, touch_y;

void CST816D_Write_Reg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen);
void CST816D_Read_Reg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen);
void CST816D_Init(void);
void CST816D_Scan(void);

#endif