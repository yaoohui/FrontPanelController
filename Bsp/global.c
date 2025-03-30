#include "global.h"



// volatile unsigned int LocalTime = 0;
FlagData_TypeDef  FlagData;
ConfigParameter_TypeDef  ConfigParameter;
BLConfigParameter_TypeDef BLConfigParameter;
USB_EndpointFlag_TypeDef UsbEPFlagStruct = {0,0,0,0};


const uint32_t VALID_BAUD[7] = {9600, 4800, 14400, 19200, 38400, 57600, 115200};	// 有效波特率，与BaudCode_TypeDef 对应

/*
*********************************************************************************************************
*	函 数 名: GetMachineID
*	功能说明: 读取MCU ID
*	形    参: unsigned char* idBuffer：12字节缓冲区
*	返 回 值: 无
*********************************************************************************************************
*/
//void GetMachineID(unsigned char* idBuffer)
//{
//	*(unsigned int*)idBuffer = *(uint32_t*)(UID_BASE);// 96bit
//	*(unsigned int*)(idBuffer + 4) = *(uint32_t*)(UID_BASE+4);//+4
//	*(unsigned int*)(idBuffer + 8) = *(uint32_t*)(UID_BASE+8);//+8
//}

/*
*********************************************************************************************************
*	函 数 名: GetBaudCode
*	功能说明: 波特率转为波特率码
*	形    参: uint32_t _baud：波特率，单位：bps
*	返 回 值: 波特率码@BaudCode_TypeDef
*********************************************************************************************************
*/
uint8_t GetBaudCode(uint32_t _baud)
{
	uint8_t i = 0;
	for(i = 0; i < 7; i++)
	{
		if(_baud == VALID_BAUD[i])
		{
			return i;
		}
	}
	return  BAUDCODE_9600;
}
