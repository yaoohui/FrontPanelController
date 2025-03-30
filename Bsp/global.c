#include "global.h"



// volatile unsigned int LocalTime = 0;
FlagData_TypeDef  FlagData;
ConfigParameter_TypeDef  ConfigParameter;
BLConfigParameter_TypeDef BLConfigParameter;
USB_EndpointFlag_TypeDef UsbEPFlagStruct = {0,0,0,0};


const uint32_t VALID_BAUD[7] = {9600, 4800, 14400, 19200, 38400, 57600, 115200};	// ��Ч�����ʣ���BaudCode_TypeDef ��Ӧ

/*
*********************************************************************************************************
*	�� �� ��: GetMachineID
*	����˵��: ��ȡMCU ID
*	��    ��: unsigned char* idBuffer��12�ֽڻ�����
*	�� �� ֵ: ��
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
*	�� �� ��: GetBaudCode
*	����˵��: ������תΪ��������
*	��    ��: uint32_t _baud�������ʣ���λ��bps
*	�� �� ֵ: ��������@BaudCode_TypeDef
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
