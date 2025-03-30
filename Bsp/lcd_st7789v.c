/*
*********************************************************************************************************
*
*	ģ������ : ST7789V оƬ����ģ�飨����SPI��
*	�ļ����� : lcd_st7789v.c
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

#include "main.h"
#include "spi.h"
#include <stdio.h>
#include <stdlib.h>
#include "lcd_st7789v.h"

#define DUMMY_BYTE  0x00

static __IO uint8_t s_ucST7789VBusy = 0;

uint8_t DISPMODE = DISP_NORMAL;		// ��Ļ��ʾ����, ȡֵ��enum_DISPMODE


/*
*********************************************************************************************************
*	�� �� ��: Spi_Read_Byte
*	����˵��: SPI ��ȡ1�ֽ�����
*	��    ��: ��
*	�� �� ֵ: ��ȡ������
*********************************************************************************************************
*/
uint8_t Spi_Read_Byte(void)
{
#ifdef LCD_WA54HC046I

	return (Spi_Send_Byte(DUMMY_BYTE));
#else
	
#ifdef USE_SOFTSPI	// ʹ�����ģ��SPI
    uint8_t i, Temp=0;
	//TODO: ����MOSIΪ����
	
    for(i=0; i<8; i++)					// ѭ��8��
    {
        SPIx_SCK_LOW();					//����ʱ��
        SPIx_SCK_HIGH();				//����ʱ��
        Temp <<= 1;						//��������
        if(SPIx_READ_MOSI()) 
			Temp++;						//���Ӵӻ����յ��ߵ�ƽ�������Լ�һ
        SPIx_SCK_LOW();					//����ʱ��
    }
    return (Temp);						//��������

#else	

//	uint32_t retry = 0;
//	
//	SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Rx);// ���ô��䷽��BIDIOE=0
//	/* Wait to receive a byte */
//	while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET)
//	{
//	  retry++;
//	  if(retry>600)
//		  return 0;
//	}

//	/* Return the byte read from the SPI bus */
//	return SPI_I2S_ReceiveData(SPIx);
	return (Spi_Send_Byte(DUMMY_BYTE));

#endif
#endif
}

/*
*********************************************************************************************************
*	�� �� ��: Spi_Send_Byte
*	����˵��: SPI����/����һ�ֽ�
*	��    ��: uint8_t byte��Ҫ���͵�����
*	�� �� ֵ: ��ȡ������
*********************************************************************************************************
*/
uint8_t Spi_Send_Byte(uint8_t byte)
{
	HAL_SPI_Transmit_DMA(&hspi1, &byte, 1);

	return DUMMY_BYTE;
}

/*
*********************************************************************************************************
*	�� �� ��: ST7789V_Write_Reg
*	����˵��: дST7789V�Ĵ���. ST7789V�ļĴ�����ַΪ16bit��������8bit��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ST7789V_Write_Reg(uint16_t _ucRegAddr, uint16_t _ucRegValue)
{
	s_ucST7789VBusy = 1;
	ST7789V_CS(0);
	ST7789V_DC(0);	// cmd
	Spi_Send_Byte(_ucRegAddr);
	
	ST7789V_DC(1);	// data
	Spi_Send_Byte(_ucRegValue);

	ST7789V_CS(1);
	s_ucST7789VBusy = 0;
}
void ST7789V_Write_Reg_Com(uint16_t _ucRegAddr)
{
	ST7789V_CS(0);
	ST7789V_DC(0);	// cmd
	Spi_Send_Byte(_ucRegAddr);
	
	ST7789V_CS(1);
}

void ST7789V_Write_Data(uint8_t data)
{
	ST7789V_CS(0);
	ST7789V_DC(1);	// data
	Spi_Send_Byte(data);
	
	ST7789V_CS(1);
}
void ST7789V_Write_Data16(uint16_t data16)
{
	ST7789V_CS(0);
	ST7789V_DC(1);	// data
	Spi_Send_Byte(data16 >> 8);
	Spi_Send_Byte(data16 & 0xFF);
	
	ST7789V_CS(1);
}
/*
*********************************************************************************************************
*	�� �� ��: ST7789V_Read_Reg
*	����˵��: ��ST7789V�Ĵ�����1�ֽ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
uint16_t ST7789V_Read_Reg(uint16_t _ucRegAddr)
{
	uint16_t value;

	ST7789V_CS(0);
	ST7789V_DC(0);	// cmd
	//SpiSendByteWithoutRead(_ucRegAddr);//
	value = Spi_Send_Byte(_ucRegAddr);
	HAL_Delay_us(1);
	ST7789V_DC(1);	// data
	value = Spi_Read_Byte();
	
	ST7789V_CS(1);

	return value;
}

uint16_t ST7789V_Read_Reg16(uint16_t _ucRegAddr)
{
	uint16_t valueH, valueL;

	ST7789V_CS(0);
	ST7789V_DC(0);	// cmd
	Spi_Send_Byte(_ucRegAddr);
	HAL_Delay_us(1);
	ST7789V_DC(1);	// data
	valueH = Spi_Read_Byte();
	valueL = Spi_Read_Byte();
	
	ST7789V_CS(1);

	valueH <<= 8;
	return (valueH | valueL);
}

uint16_t ST7789V_Read_Data(void)
{
	return 0;			/* ��ȡ�Ĵ���ֵ */
}

/*
*********************************************************************************************************
*	�� �� ��: ST7789V_Read_ID
*	����˵��: ��ȡLCD����оƬID
*	��    ��: ����id
*	�� �� ֵ: id��ȷ����1�����󷵻�0
*********************************************************************************************************
*/
uint8_t ST7789V_Read_ID(uint32_t *_id)
{
	uint32_t  value;
	uint8_t temp8;
	
	value = ST7789V_Read_Reg(0xDA);
//	printf("RID1:%02X\r\n", value);
	value <<= 8;
	
	temp8 = ST7789V_Read_Reg(0xDb);
//	printf("RID2:%02X\r\n", temp8);
	value += temp8;
	value <<= 8;
	
	temp8 = ST7789V_Read_Reg(0xDc);
//	printf("RID3:%02X\r\n", temp8);
	value += temp8;
	
	
	*_id = value;
	if(value != ST7789V_ID)
		return 0;
	else
		return 1;
}

/*
*********************************************************************************************************
*	�� �� ��: ST7789V_Set_Display_Mode
*	����˵��: ������Ļ��ʾ����
*	��    ��: uint8_t _mode: ��Ļ��ʾ����, ȡֵ��enum_DISPMODE
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ST7789V_Set_Display_Mode(uint8_t _mode)
{
	// 7  6  5  4  3   2   1  0
	// MY MX MV ML RGB MH  -  -
	DISPMODE = _mode;
	switch(_mode)
	{
		case DISP_LEFT:		// ��Ļ������ת90��
			ST7789V_Write_Reg( 0x36, 0xA0 );	
			break;
		case DISP_RIGHT:	// ��Ļ������ת90��
			ST7789V_Write_Reg( 0x36, 0x60 );		
			break;
		case DISP_DOWN:		// ��Ļ��ת180��
			ST7789V_Write_Reg( 0x36, 0xC0 );		
			break;
		default:			// ��Ļ����������ʾ
			ST7789V_Write_Reg( 0x36, 0x00 );
			break;
	}
	
}

/*
*********************************************************************************************************
*	�� �� ��: ST7789V_Vertical_Refresh_Order
*	����˵��: �ı䴹ֱɨ�跽������ˢBMPͼƬ
*           ע�⣺���ͼƬ��ʽ�����ݷ���Ϊ����Ϊ�˰���������ʾͼƬ������Ҫ��ˢͼƬǰ���ô˺�����
*           ����ȡ1������ˢ��ͼƬ���ٵ���һ�Σ�����ȡ0���Իָ�֮ǰ��ɨ�跽��
*	��    ��: uint8_t _mode: ��Ļ��ʾ����, ȡֵ��enum_DISPMODE
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ST7789V_Vertical_Refresh_Order(uint8_t _bottom2top)
{
	uint8_t mode = DISPMODE;
	
	if(_bottom2top)
	{
		switch(mode)
		{
			case DISP_NORMAL:
				ST7789V_Write_Reg( 0x36, 0x80 );
				DISPMODE = DISP_DOWN;// Ϊ�����ô���
				break;
			case DISP_DOWN:
				ST7789V_Write_Reg( 0x36, 0x40 );
				DISPMODE = DISP_NORMAL;// Ϊ�����ô���
				break;
			case DISP_LEFT:
				ST7789V_Write_Reg( 0x36, 0xE0 );
				break;
			case DISP_RIGHT:
				ST7789V_Write_Reg( 0x36, 0x20 );
				break;
		}	
	}
	else
	{
		switch(mode)
		{
			case DISP_NORMAL:
				ST7789V_Set_Display_Mode(DISP_DOWN);//�ָ�֮ǰ��ɨ�跽��
				break;
			case DISP_DOWN:
				ST7789V_Set_Display_Mode(DISP_NORMAL);//�ָ�֮ǰ��ɨ�跽��
				break;
			case DISP_LEFT:
				ST7789V_Set_Display_Mode(DISP_LEFT);
				break;
			case DISP_RIGHT:
				ST7789V_Set_Display_Mode(DISP_RIGHT);
				break;
		}	
	}
}

/*
*********************************************************************************************************
*	�� �� ��: ST7789V_Reset
*	����˵��: ST7789V��λ
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ST7789V_Reset(void)
{
	ST7789V_RST(1);
	HAL_Delay(10);
	ST7789V_RST(0);
	HAL_Delay(50);	
	ST7789V_RST(1);
	HAL_Delay(200);
}


/*
*********************************************************************************************************
*	�� �� ��: ST7789V_Init
*	����˵��: ST7789V��ʼ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ST7789V_Init(void)
{
//	uint32_t id = 0;
	
	ST7789V_Reset();
//	LCD_BKL_ON();
	
	
//	ST7789V_Read_ID(&id);

	ST7789V_Write_Reg_Com(0x11);
	HAL_Delay(120);
	
#ifdef	LCD_WA54HC046I // ���ֿ� 240*RGB*240
	ST7789V_Write_Reg_Com(0x36);//MX, MY, RGB mode 
	ST7789V_Write_Data(0x00);

	ST7789V_Write_Reg_Com(0x3a);
	ST7789V_Write_Data(0x05);	// 0x05:RGB565

	//----------ST7789V Frame rate setting-------------------//
	ST7789V_Write_Reg_Com(0xb2);
	ST7789V_Write_Data(0x1F);
	ST7789V_Write_Data(0x1F);
	ST7789V_Write_Data(0x00);
	ST7789V_Write_Data(0x33);
	ST7789V_Write_Data(0x33);

	ST7789V_Write_Reg_Com(0xb7);
	ST7789V_Write_Data(0x00);
	
	//-----------ST7789V Power setting---------------------//
	ST7789V_Write_Reg_Com(0xbb);
	ST7789V_Write_Data(0x36);

//	ST7789V_Write_Reg_Com(0xc0);
//	ST7789V_Write_Data(0x2c);

	ST7789V_Write_Reg_Com(0xc2);
	ST7789V_Write_Data(0x01);

	ST7789V_Write_Reg_Com(0xc3);
	ST7789V_Write_Data(0x13);

	ST7789V_Write_Reg_Com(0xc4);
	ST7789V_Write_Data(0x20);  //VDV, 0x20:0v

	ST7789V_Write_Reg_Com(0xc6);
	ST7789V_Write_Data(0x13);  //0x0F:60Hz  

	ST7789V_Write_Reg_Com(0xD6);     
	ST7789V_Write_Data(0xA1);   	
	
	ST7789V_Write_Reg_Com(0xd0);
	ST7789V_Write_Data(0xa4);
	ST7789V_Write_Data(0xa1);
	
	ST7789V_Write_Reg_Com(0x2A); //Column Address Set
	ST7789V_Write_Data(0x00);
	ST7789V_Write_Data(0x00);//0
	ST7789V_Write_Data(0x00);
	ST7789V_Write_Data(0xEF);//239

	ST7789V_Write_Reg_Com(0x2B); //Row Address Set
	ST7789V_Write_Data(0x00);
	ST7789V_Write_Data(0x00);//0
	ST7789V_Write_Data(0x00);
	ST7789V_Write_Data(0xEF);//239
	
	//---------------ST7789V gamma setting-----------------------//
	ST7789V_Write_Reg_Com(0xe0);
	ST7789V_Write_Data(0xF0);
	ST7789V_Write_Data(0x08);
	ST7789V_Write_Data(0x0E);
	ST7789V_Write_Data(0x09);
	ST7789V_Write_Data(0x08);
	ST7789V_Write_Data(0x04);
	ST7789V_Write_Data(0x2F);
	ST7789V_Write_Data(0x33);
	ST7789V_Write_Data(0x45);
	ST7789V_Write_Data(0x36);
	ST7789V_Write_Data(0x13);
	ST7789V_Write_Data(0x12);
	ST7789V_Write_Data(0x2A);
	ST7789V_Write_Data(0x2D);

	ST7789V_Write_Reg_Com(0xe1);
	ST7789V_Write_Data(0xF0);
	ST7789V_Write_Data(0x0E);
	ST7789V_Write_Data(0x12);
	ST7789V_Write_Data(0x0C);
	ST7789V_Write_Data(0x0A);
	ST7789V_Write_Data(0x15);
	ST7789V_Write_Data(0x2E);
	ST7789V_Write_Data(0x32);
	ST7789V_Write_Data(0x44);
	ST7789V_Write_Data(0x39);
	ST7789V_Write_Data(0x17);
	ST7789V_Write_Data(0x18);
	ST7789V_Write_Data(0x2B);
	ST7789V_Write_Data(0x2F);

	ST7789V_Write_Reg_Com(0xE4);    
	ST7789V_Write_Data(0x1D);
	ST7789V_Write_Data(0x00); 
	ST7789V_Write_Data(0x00); 


	ST7789V_Write_Reg_Com(0x21);
	ST7789V_Write_Reg_Com(0x29);  
	
	ST7789V_Write_Reg_Com(0xc7);    
	ST7789V_Write_Data(0x04);

	ST7789V_Write_Reg_Com(0xcc);    
	ST7789V_Write_Data(0x18);
#else
// P169H002-CTP 240*RGB*280
	ST7789V_Write_Reg_Com(0x36);//MX, MY, RGB mode 
	ST7789V_Write_Data(0x00);

	ST7789V_Write_Reg_Com(0x3a);
	ST7789V_Write_Data(0x55);	// 16bits/pixel

	//----------ST7789V Frame rate setting-------------------//
	ST7789V_Write_Reg_Com(0xb2);
	ST7789V_Write_Data(0x0C);//(0x0B);
	ST7789V_Write_Data(0x0C);//(0x0B);
	ST7789V_Write_Data(0x00);
	ST7789V_Write_Data(0x33);
	ST7789V_Write_Data(0x33);

	ST7789V_Write_Reg_Com(0xb7);
	ST7789V_Write_Data(0x35);//(0x11);
	
	//-----------ST7789V Power setting---------------------//
	ST7789V_Write_Reg_Com(0xbb);
	ST7789V_Write_Data(0x19);//(0x2F);

	ST7789V_Write_Reg_Com(0xc0);
	ST7789V_Write_Data(0x2c);

	ST7789V_Write_Reg_Com(0xc2);
	ST7789V_Write_Data(0x01);

	ST7789V_Write_Reg_Com(0xc3);
	ST7789V_Write_Data(0x12);//(0x0D);

	ST7789V_Write_Reg_Com(0xc4);
	ST7789V_Write_Data(0x20);  //VDV, 0x20:0v

	ST7789V_Write_Reg_Com(0xc6);
	ST7789V_Write_Data(0x0F);//(0x13);  //0x0F:60Hz  
	
	ST7789V_Write_Reg_Com(0xD6);     
	ST7789V_Write_Data(0xA1);    //sleep in��gate���ΪGND	
	
	ST7789V_Write_Reg_Com(0xd0);
	ST7789V_Write_Data(0xa4);
	ST7789V_Write_Data(0xa1);
	
	
	//---------------ST7789V gamma setting-----------------------//
	ST7789V_Write_Reg_Com(0xe0);
	ST7789V_Write_Data(0xF0);
	ST7789V_Write_Data(0x04);
	ST7789V_Write_Data(0x07);
	ST7789V_Write_Data(0x09);
	ST7789V_Write_Data(0x07);
	ST7789V_Write_Data(0x13);
	ST7789V_Write_Data(0x25);
	ST7789V_Write_Data(0x33);
	ST7789V_Write_Data(0x3C);
	ST7789V_Write_Data(0x34);
	ST7789V_Write_Data(0x10);
	ST7789V_Write_Data(0x10);
	ST7789V_Write_Data(0x29);
	ST7789V_Write_Data(0x32);

	ST7789V_Write_Reg_Com(0xe1);
	ST7789V_Write_Data(0xF0);
	ST7789V_Write_Data(0x05);
	ST7789V_Write_Data(0x08);
	ST7789V_Write_Data(0x0A);
	ST7789V_Write_Data(0x09);
	ST7789V_Write_Data(0x05);
	ST7789V_Write_Data(0x25);
	ST7789V_Write_Data(0x32);
	ST7789V_Write_Data(0x3B);
	ST7789V_Write_Data(0x3B);
	ST7789V_Write_Data(0x17);
	ST7789V_Write_Data(0x18);
	ST7789V_Write_Data(0x2E);
	ST7789V_Write_Data(0x37);

	ST7789V_Write_Reg_Com(0xE4);    
	ST7789V_Write_Data(0x25);  //ʹ��240��gate  (N+1)*8
	ST7789V_Write_Data(0x00);  //�趨gate���λ��


	ST7789V_Write_Reg_Com(0x2A); //Column Address Set
	ST7789V_Write_Data(0x00);
	ST7789V_Write_Data(0x00);//0
	ST7789V_Write_Data(0x00);
	ST7789V_Write_Data(0xEF);//239

	ST7789V_Write_Reg_Com(0x2B); //Row Address Set
	ST7789V_Write_Data(0x00);
	ST7789V_Write_Data(0x14);//20
	ST7789V_Write_Data(0x01);
	ST7789V_Write_Data(0x2B);//299
	ST7789V_Write_Data(0x00);  //��gateû������ʱ��bit4(TMG)��Ϊ0


	ST7789V_Write_Reg_Com(0x21);
	
	ST7789V_Write_Reg_Com(0x29);  
	
	//ST7789V_Write_Reg_Com(0x2C);    
#endif
	ST7789V_Write_Reg_Com(0x11);
	HAL_Delay(30);
	
	ST7789V_Clear(BLACK);
}

/*
*********************************************************************************************************
*	�� �� ��: ST7789V_Clear
*	����˵��: �����������ɫֵ����
*	��    ��: uint16_t _Color: ��ɫֵ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ST7789V_Clear(uint16_t _Color)
{
//	uint16_t i,j;
//	
//	ST7789V_Set_Windows(0,0, LCD_WIDTH - 1, LCD_HEIGHT - 1);
//	for(i=0; i<LCD_HEIGHT; i++)
//	{
//		for(j=0; j<LCD_WIDTH; j++)
//			ST7789V_Write_Data16(_Color);
//	}
	uint16_t width = 240;
	uint16_t height = 10;
	uint32_t buf_size = (width * height);
	uint8_t *buf = (uint8_t *)malloc(buf_size * 2);
//	printf("-%d-%d-%d-%d-w=%d,,h=%d\n", x1, y1, x2, y2,width,height);
	HAL_Delay(1);
	if (buf == NULL)
	{
		printf("�ڴ����ʧ�ܣ�����\r\n");  
		// �����ڴ����ʧ�ܵ����
		return;
	}

	for (uint32_t i = 0; i < buf_size; i++)
	{
		buf[i * 2] = (_Color >> 8) & 0xFF;
		buf[i * 2 + 1] = _Color & 0xFF;
	}
	
	for(uint8_t i = 0; i < 24; i++)
	{
		LCD_Address_Set(0, height * i, 240, height * i + height);
		ST7789V_CS(0);
		ST7789V_DC(1);
		HAL_SPI_Transmit_DMA(&hspi1, buf, buf_size * 2);
		HAL_Delay(1);
	}
	ST7789V_CS(1);
	free(buf);
}


/*
*********************************************************************************************************
*	�� �� ��: ST7789V_Set_Windows
*	����˵��: ���û��ƴ��ڴ�С ע�⣺ֻ֧����������
*	��    ��: uint16_t _x0: x����ʼλ��
*			  uint16_t _y0: y����ʼλ��
*			  uint16_t _x1: x�����λ��
*			  uint16_t _y1: y�����λ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ST7789V_Set_Windows(uint16_t _x0, uint16_t _y0, uint16_t _x1, uint16_t _y1)
{// ����Ϊ�����ʱ��Ӳ����ֱ������Ҫ��ƽ��xx���ء�
	if(DISPMODE == DISP_RIGHT)
	{
		ST7789V_Write_Reg_Com(0x2A);
		ST7789V_Write_Data(_x0>>8);          //ˮƽGRAM��ʼλ��
		ST7789V_Write_Data(_x0&0xFF);        //ˮƽGRAM��ʼλ��
		ST7789V_Write_Data(_x1>>8);          //ˮƽGRAM�յ�λ��
		ST7789V_Write_Data(_x1&0xFF);        //ˮƽGRAM�յ�λ��
		
		ST7789V_Write_Reg_Com(0x2B);
		ST7789V_Write_Data(_y0>>8);          //��ֱGRAM��ʼλ��
		ST7789V_Write_Data(_y0&0xFF);        //��ֱGRAM��ʼλ��
		ST7789V_Write_Data(_y1>>8);          //��ֱGRAM�յ�λ��
		ST7789V_Write_Data(_y1&0xFF);        //��ֱGRAM�յ�λ��
	}
	else if(DISPMODE == DISP_LEFT)
	{
		ST7789V_Write_Reg_Com(0x2A);
		ST7789V_Write_Data((_x0+80)>>8);     //ˮƽGRAM��ʼλ��
		ST7789V_Write_Data((_x0+80)&0xFF);   //ˮƽGRAM��ʼλ��
		ST7789V_Write_Data((_x1+80)>>8);     //ˮƽGRAM�յ�λ��
		ST7789V_Write_Data((_x1+80)&0xFF);   //ˮƽGRAM�յ�λ��
		
		ST7789V_Write_Reg_Com(0x2B);
		ST7789V_Write_Data(_y0>>8);          //��ֱGRAM��ʼλ��
		ST7789V_Write_Data(_y0&0xFF);        //��ֱGRAM��ʼλ��
		ST7789V_Write_Data(_y1>>8);          //��ֱGRAM�յ�λ��
		ST7789V_Write_Data(_y1&0xFF);        //��ֱGRAM�յ�λ��
	}
	else if(DISPMODE == DISP_DOWN)
	{
		ST7789V_Write_Reg_Com(0x2A);
		ST7789V_Write_Data(_x0>>8);          //ˮƽGRAM��ʼλ��
		ST7789V_Write_Data(_x0&0xFF);        //ˮƽGRAM��ʼλ��
		ST7789V_Write_Data(_x1>>8);          //ˮƽGRAM�յ�λ��
		ST7789V_Write_Data(_x1&0xFF);        //ˮƽGRAM�յ�λ��
		
		ST7789V_Write_Reg_Com(0x2B);
		ST7789V_Write_Data((_y0+80)>>8);     //��ֱGRAM��ʼλ��
		ST7789V_Write_Data((_y0+80)&0xFF);   //��ֱGRAM��ʼλ��
		ST7789V_Write_Data((_y1+80)>>8);     //��ֱGRAM�յ�λ��
		ST7789V_Write_Data((_y1+80)&0xFF);   //��ֱGRAM�յ�λ��
	}
	else
	{
		ST7789V_Write_Reg_Com(0x2A);
		ST7789V_Write_Data(_x0>>8);          //ˮƽGRAM��ʼλ��
		ST7789V_Write_Data(_x0&0xFF);        //ˮƽGRAM��ʼλ��
		ST7789V_Write_Data(_x1>>8);          //ˮƽGRAM�յ�λ��
		ST7789V_Write_Data(_x1&0xFF);        //ˮƽGRAM�յ�λ��

#ifdef	LCD_WA54HC046I // ���ֿ� 240*RGB*240
		
		ST7789V_Write_Reg_Com(0x2B);
		ST7789V_Write_Data(_y0>>8);          //��ֱGRAM��ʼλ��
		ST7789V_Write_Data(_y0&0xFF);        //��ֱGRAM��ʼλ��
		ST7789V_Write_Data(_y1>>8);          //��ֱGRAM�յ�λ��
		ST7789V_Write_Data(_y1&0xFF);        //��ֱGRAM�յ�λ��
#else
		_y0 += 0x14;
		_y1 += 0x14;
		ST7789V_Write_Reg_Com(0x2B);
		ST7789V_Write_Data(_y0>>8);          //��ֱGRAM��ʼλ��
		ST7789V_Write_Data(_y0&0xFF);        //��ֱGRAM��ʼλ��
		ST7789V_Write_Data(_y1>>8);          //��ֱGRAM�յ�λ��
		ST7789V_Write_Data(_y1&0xFF);        //��ֱGRAM�յ�λ��

#endif		
	}
	ST7789V_Write_Reg_Com(0x2C);
}

/*
*********************************************************************************************************
*	�� �� ��: ST7789V_Display_On
*	����˵��: ����ʾ
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ST7789V_Display_On(void)
{
	ST7789V_Write_Reg_Com(0x29);
	HAL_Delay(1);
}

/*
*********************************************************************************************************
*	�� �� ��: ST7789V_Display_Off
*	����˵��: �ر���ʾ
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ST7789V_Display_Off(void)
{
	ST7789V_Write_Reg_Com(0x28);
	HAL_Delay(1);
}


/*
*********************************************************************************************************
*	�� �� ��: ST7789V_Set_Cursor
*	����˵��: ���õ�ǰ��ͼλ��
*	��    ��: uint16_t _x, uint16_t _y: ��ͼ����λ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ST7789V_Set_Cursor(uint16_t _x, uint16_t _y)
{
	ST7789V_Set_Windows(_x, _y, LCD_WIDTH-1, LCD_HEIGHT-1);
}


/*
*********************************************************************************************************
*	�� �� ��: ST7789V_Draw_Pixel
*	����˵��: ��1������
*	��    ��: uint16_t _x, uint16_t _y: ��������
*			  uint16_t _Color : ������ɫ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void ST7789V_Draw_Pixel(uint16_t _x, uint16_t _y, uint16_t _Color)
{
	ST7789V_Set_Cursor(_x, _y);	/* ���ù��λ�� */

	s_ucST7789VBusy = 1;
	ST7789V_Write_Data16(_Color);
	s_ucST7789VBusy = 0;
}


void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	/* ָ��X����������� */
	ST7789V_Write_Reg_Com(0x2a);
	ST7789V_Write_Data(x1 >> 8);
	ST7789V_Write_Data(x1 & 0xFF);
	ST7789V_Write_Data(x2 >> 8);
	ST7789V_Write_Data(x2 & 0xFF);

	/* ָ��Y����������� */
	ST7789V_Write_Reg_Com(0x2b);
	ST7789V_Write_Data(y1 >> 8);
	ST7789V_Write_Data(y1 & 0xFF);
	ST7789V_Write_Data(y2 >> 8);
	ST7789V_Write_Data(y2 & 0xFF);

	/* ���͸����LCD��ʼ�ȴ������Դ����� */
	ST7789V_Write_Reg_Com(0x2C);
}


void LCD_color_fill_lvgl(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lv_color_t *color)
{
	uint16_t width = (x2 - x1) + 1;
	uint16_t height = (y2 - y1) + 1;
	uint32_t buf_size = (width * height);
	uint8_t *buf = (uint8_t *)malloc(buf_size * 2);
//	printf("-%d-%d-%d-%d-w=%d,,h=%d\n", x1, y1, x2, y2,width,height);
	HAL_Delay(1);
	if (buf == NULL)
	{
		printf("�ڴ����ʧ�ܣ�����\r\n");  
		// �����ڴ����ʧ�ܵ����
		return;
	}

	LCD_Address_Set(x1, y1, x2, y2);

	ST7789V_CS(0);
	ST7789V_DC(1);
//	printf("-1--%d-%d-%d---\n",width,height,buf_size);
	for (uint32_t i = 0; i < buf_size; i++)
	{
		buf[i * 2] = (color->full >> 8) & 0xFF;
		buf[i * 2 + 1] = color->full & 0xFF;
		color++;
	}

//	HAL_SPI_Transmit(&hspi1, buf, buf_size*2, 1000);
	HAL_SPI_Transmit_DMA(&hspi1, buf, buf_size * 2);
//	ST7789V_CS(1);
	free(buf);
}


