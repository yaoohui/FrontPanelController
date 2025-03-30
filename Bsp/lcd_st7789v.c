/*
*********************************************************************************************************
*
*	模块名称 : ST7789V 芯片驱动模块（串行SPI）
*	文件名称 : lcd_st7789v.c
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

#include "main.h"
#include "spi.h"
#include <stdio.h>
#include <stdlib.h>
#include "lcd_st7789v.h"

#define DUMMY_BYTE  0x00

static __IO uint8_t s_ucST7789VBusy = 0;

uint8_t DISPMODE = DISP_NORMAL;		// 屏幕显示方向, 取值见enum_DISPMODE


/*
*********************************************************************************************************
*	函 数 名: Spi_Read_Byte
*	功能说明: SPI 读取1字节数据
*	形    参: 无
*	返 回 值: 读取的数据
*********************************************************************************************************
*/
uint8_t Spi_Read_Byte(void)
{
#ifdef LCD_WA54HC046I

	return (Spi_Send_Byte(DUMMY_BYTE));
#else
	
#ifdef USE_SOFTSPI	// 使用软件模拟SPI
    uint8_t i, Temp=0;
	//TODO: 配置MOSI为输入
	
    for(i=0; i<8; i++)					// 循环8次
    {
        SPIx_SCK_LOW();					//拉低时钟
        SPIx_SCK_HIGH();				//拉高时钟
        Temp <<= 1;						//数据左移
        if(SPIx_READ_MOSI()) 
			Temp++;						//若从从机接收到高电平，数据自加一
        SPIx_SCK_LOW();					//拉低时钟
    }
    return (Temp);						//返回数据

#else	

//	uint32_t retry = 0;
//	
//	SPI_BiDirectionalLineConfig(SPIx, SPI_Direction_Rx);// 设置传输方向。BIDIOE=0
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
*	函 数 名: Spi_Send_Byte
*	功能说明: SPI发送/接收一字节
*	形    参: uint8_t byte：要发送的数据
*	返 回 值: 读取的数据
*********************************************************************************************************
*/
uint8_t Spi_Send_Byte(uint8_t byte)
{
	HAL_SPI_Transmit_DMA(&hspi1, &byte, 1);

	return DUMMY_BYTE;
}

/*
*********************************************************************************************************
*	函 数 名: ST7789V_Write_Reg
*	功能说明: 写ST7789V寄存器. ST7789V的寄存器地址为16bit，数据是8bit的
*	形    参: 无
*	返 回 值: 无
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
*	函 数 名: ST7789V_Read_Reg
*	功能说明: 读ST7789V寄存器，1字节
*	形    参: 无
*	返 回 值: 无
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
	return 0;			/* 读取寄存器值 */
}

/*
*********************************************************************************************************
*	函 数 名: ST7789V_Read_ID
*	功能说明: 读取LCD驱动芯片ID
*	形    参: 返回id
*	返 回 值: id正确返回1，错误返回0
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
*	函 数 名: ST7789V_Set_Display_Mode
*	功能说明: 设置屏幕显示方向
*	形    参: uint8_t _mode: 屏幕显示方向, 取值见enum_DISPMODE
*	返 回 值: 无
*********************************************************************************************************
*/
void ST7789V_Set_Display_Mode(uint8_t _mode)
{
	// 7  6  5  4  3   2   1  0
	// MY MX MV ML RGB MH  -  -
	DISPMODE = _mode;
	switch(_mode)
	{
		case DISP_LEFT:		// 屏幕向左旋转90度
			ST7789V_Write_Reg( 0x36, 0xA0 );	
			break;
		case DISP_RIGHT:	// 屏幕向右旋转90度
			ST7789V_Write_Reg( 0x36, 0x60 );		
			break;
		case DISP_DOWN:		// 屏幕旋转180度
			ST7789V_Write_Reg( 0x36, 0xC0 );		
			break;
		default:			// 屏幕正常方向显示
			ST7789V_Write_Reg( 0x36, 0x00 );
			break;
	}
	
}

/*
*********************************************************************************************************
*	函 数 名: ST7789V_Vertical_Refresh_Order
*	功能说明: 改变垂直扫描方向，用于刷BMP图片
*           注意：如果图片格式中数据方向为反向，为了按正方向显示图片，则需要在刷图片前调用此函数，
*           参数取1，并在刷完图片后再调用一次，参数取0，以恢复之前的扫描方向。
*	形    参: uint8_t _mode: 屏幕显示方向, 取值见enum_DISPMODE
*	返 回 值: 无
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
				DISPMODE = DISP_DOWN;// 为了设置窗口
				break;
			case DISP_DOWN:
				ST7789V_Write_Reg( 0x36, 0x40 );
				DISPMODE = DISP_NORMAL;// 为了设置窗口
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
				ST7789V_Set_Display_Mode(DISP_DOWN);//恢复之前的扫描方向
				break;
			case DISP_DOWN:
				ST7789V_Set_Display_Mode(DISP_NORMAL);//恢复之前的扫描方向
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
*	函 数 名: ST7789V_Reset
*	功能说明: ST7789V复位
*	形    参: 无
*	返 回 值: 无
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
*	函 数 名: ST7789V_Init
*	功能说明: ST7789V初始化
*	形    参: 无
*	返 回 值: 无
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
	
#ifdef	LCD_WA54HC046I // 沃乐康 240*RGB*240
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
	ST7789V_Write_Data(0xA1);    //sleep in后，gate输出为GND	
	
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
	ST7789V_Write_Data(0x25);  //使用240根gate  (N+1)*8
	ST7789V_Write_Data(0x00);  //设定gate起点位置


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
	ST7789V_Write_Data(0x00);  //当gate没有用完时，bit4(TMG)设为0


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
*	函 数 名: ST7789V_Clear
*	功能说明: 根据输入的颜色值清屏
*	形    参: uint16_t _Color: 颜色值
*	返 回 值: 无
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
		printf("内存分配失败！！！\r\n");  
		// 处理内存分配失败的情况
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
*	函 数 名: ST7789V_Set_Windows
*	功能说明: 设置绘制窗口大小 注意：只支持正常方向
*	形    参: uint16_t _x0: x轴起始位置
*			  uint16_t _y0: y轴起始位置
*			  uint16_t _x1: x轴结束位置
*			  uint16_t _y1: y轴结束位置
*	返 回 值: 无
*********************************************************************************************************
*/
void ST7789V_Set_Windows(uint16_t _x0, uint16_t _y0, uint16_t _x1, uint16_t _y1)
{// 方向为左和下时，硬件垂直方向需要多平移xx像素。
	if(DISPMODE == DISP_RIGHT)
	{
		ST7789V_Write_Reg_Com(0x2A);
		ST7789V_Write_Data(_x0>>8);          //水平GRAM起始位置
		ST7789V_Write_Data(_x0&0xFF);        //水平GRAM起始位置
		ST7789V_Write_Data(_x1>>8);          //水平GRAM终点位置
		ST7789V_Write_Data(_x1&0xFF);        //水平GRAM终点位置
		
		ST7789V_Write_Reg_Com(0x2B);
		ST7789V_Write_Data(_y0>>8);          //垂直GRAM起始位置
		ST7789V_Write_Data(_y0&0xFF);        //垂直GRAM起始位置
		ST7789V_Write_Data(_y1>>8);          //垂直GRAM终点位置
		ST7789V_Write_Data(_y1&0xFF);        //垂直GRAM终点位置
	}
	else if(DISPMODE == DISP_LEFT)
	{
		ST7789V_Write_Reg_Com(0x2A);
		ST7789V_Write_Data((_x0+80)>>8);     //水平GRAM起始位置
		ST7789V_Write_Data((_x0+80)&0xFF);   //水平GRAM起始位置
		ST7789V_Write_Data((_x1+80)>>8);     //水平GRAM终点位置
		ST7789V_Write_Data((_x1+80)&0xFF);   //水平GRAM终点位置
		
		ST7789V_Write_Reg_Com(0x2B);
		ST7789V_Write_Data(_y0>>8);          //垂直GRAM起始位置
		ST7789V_Write_Data(_y0&0xFF);        //垂直GRAM起始位置
		ST7789V_Write_Data(_y1>>8);          //垂直GRAM终点位置
		ST7789V_Write_Data(_y1&0xFF);        //垂直GRAM终点位置
	}
	else if(DISPMODE == DISP_DOWN)
	{
		ST7789V_Write_Reg_Com(0x2A);
		ST7789V_Write_Data(_x0>>8);          //水平GRAM起始位置
		ST7789V_Write_Data(_x0&0xFF);        //水平GRAM起始位置
		ST7789V_Write_Data(_x1>>8);          //水平GRAM终点位置
		ST7789V_Write_Data(_x1&0xFF);        //水平GRAM终点位置
		
		ST7789V_Write_Reg_Com(0x2B);
		ST7789V_Write_Data((_y0+80)>>8);     //垂直GRAM起始位置
		ST7789V_Write_Data((_y0+80)&0xFF);   //垂直GRAM起始位置
		ST7789V_Write_Data((_y1+80)>>8);     //垂直GRAM终点位置
		ST7789V_Write_Data((_y1+80)&0xFF);   //垂直GRAM终点位置
	}
	else
	{
		ST7789V_Write_Reg_Com(0x2A);
		ST7789V_Write_Data(_x0>>8);          //水平GRAM起始位置
		ST7789V_Write_Data(_x0&0xFF);        //水平GRAM起始位置
		ST7789V_Write_Data(_x1>>8);          //水平GRAM终点位置
		ST7789V_Write_Data(_x1&0xFF);        //水平GRAM终点位置

#ifdef	LCD_WA54HC046I // 沃乐康 240*RGB*240
		
		ST7789V_Write_Reg_Com(0x2B);
		ST7789V_Write_Data(_y0>>8);          //垂直GRAM起始位置
		ST7789V_Write_Data(_y0&0xFF);        //垂直GRAM起始位置
		ST7789V_Write_Data(_y1>>8);          //垂直GRAM终点位置
		ST7789V_Write_Data(_y1&0xFF);        //垂直GRAM终点位置
#else
		_y0 += 0x14;
		_y1 += 0x14;
		ST7789V_Write_Reg_Com(0x2B);
		ST7789V_Write_Data(_y0>>8);          //垂直GRAM起始位置
		ST7789V_Write_Data(_y0&0xFF);        //垂直GRAM起始位置
		ST7789V_Write_Data(_y1>>8);          //垂直GRAM终点位置
		ST7789V_Write_Data(_y1&0xFF);        //垂直GRAM终点位置

#endif		
	}
	ST7789V_Write_Reg_Com(0x2C);
}

/*
*********************************************************************************************************
*	函 数 名: ST7789V_Display_On
*	功能说明: 打开显示
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void ST7789V_Display_On(void)
{
	ST7789V_Write_Reg_Com(0x29);
	HAL_Delay(1);
}

/*
*********************************************************************************************************
*	函 数 名: ST7789V_Display_Off
*	功能说明: 关闭显示
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void ST7789V_Display_Off(void)
{
	ST7789V_Write_Reg_Com(0x28);
	HAL_Delay(1);
}


/*
*********************************************************************************************************
*	函 数 名: ST7789V_Set_Cursor
*	功能说明: 设置当前绘图位置
*	形    参: uint16_t _x, uint16_t _y: 绘图坐标位置
*	返 回 值: 无
*********************************************************************************************************
*/
void ST7789V_Set_Cursor(uint16_t _x, uint16_t _y)
{
	ST7789V_Set_Windows(_x, _y, LCD_WIDTH-1, LCD_HEIGHT-1);
}


/*
*********************************************************************************************************
*	函 数 名: ST7789V_Draw_Pixel
*	功能说明: 画1个像素
*	形    参: uint16_t _x, uint16_t _y: 像素坐标
*			  uint16_t _Color : 像素颜色
*	返 回 值: 无
*********************************************************************************************************
*/
void ST7789V_Draw_Pixel(uint16_t _x, uint16_t _y, uint16_t _Color)
{
	ST7789V_Set_Cursor(_x, _y);	/* 设置光标位置 */

	s_ucST7789VBusy = 1;
	ST7789V_Write_Data16(_Color);
	s_ucST7789VBusy = 0;
}


void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	/* 指定X方向操作区域 */
	ST7789V_Write_Reg_Com(0x2a);
	ST7789V_Write_Data(x1 >> 8);
	ST7789V_Write_Data(x1 & 0xFF);
	ST7789V_Write_Data(x2 >> 8);
	ST7789V_Write_Data(x2 & 0xFF);

	/* 指定Y方向操作区域 */
	ST7789V_Write_Reg_Com(0x2b);
	ST7789V_Write_Data(y1 >> 8);
	ST7789V_Write_Data(y1 & 0xFF);
	ST7789V_Write_Data(y2 >> 8);
	ST7789V_Write_Data(y2 & 0xFF);

	/* 发送该命令，LCD开始等待接收显存数据 */
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
		printf("内存分配失败！！！\r\n");  
		// 处理内存分配失败的情况
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


