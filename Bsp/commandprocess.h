/*
*********************************************************************************************************
*
*	ģ������ : ���ڽ������ݴ���
*	�ļ����� : commandprocess.h
*	��    �� : V1.0
*	˵    �� :
*			   
*	�޸ļ�¼ :
*		�汾��  ����		����	˵��
*		V1.0    2018-01-01	JOY	
*
*********************************************************************************************************
*/
#ifndef __COMMANDPROCESS_H
#define __COMMANDPROCESS_H

//#include "includes.h"
#include "main.h"

// ͨ��Э��ͷ��ʽ�ṹ��
typedef struct 
{
	uint16_t prefix;			// ǰ׺ 0xAA, 0x99
	uint8_t modeid;				// ģ����
	uint8_t cmd;					// ������
	uint8_t subcmd;				// ��������
	uint8_t flag;					// ���ͷ���־�����ͷ�Ϊ0xFF��Ӧ��Ϊ0x00��������ֵ���� CmdFlag_TypeDef��
	uint16_t len;					// ���ݳ���
}Cmdhead_TypeDef;

// ͨ��Э���з��ͷ���־ȡֵ
typedef enum
{
	CMDFLAG_SEND = 0xFF,
	CMDFLAG_RES_OK = 0x00,
	CMDFLAG_RES_ERR = 0x01,
}CmdFlag_TypeDef;

// ������
enum CMD
{
	CMD_VERSION = 0xA0,								// ��ѯ�汾��
	CMD_ACK = 0xA1,										// ͨ�Ų���
	CMD_RESET = 0xA2,									// ϵͳ��λ
	CMD_FACTORY_SET = 0xA3,						// �ָ���������
	CMD_BAUD = 0xB0,									// ���ڲ����ʣ�����������ʧ�Դ洢��
	CMD_RELAY = 0xA4,									// �̵�������
	CMD_LCDTEST = 0xA5,								// ��Ļ����
	CMD_UID = 0xA6,										// ��ȡ���к�
	CMD_FW_NAME = 0xA7,								// ��ȡ�̼�����
	
	// ��ʽָ��
	CMD_SWITCH_WINDOW = 0x01,					// �л�����
	CMD_COMM_TRANSFER = 0x02,					// ͨ��ת��
	CMD_FINGERPRINT = 0x03,						// ָ�Ʋ���
	CMD_DATA_TIME = 0x04,							// ����ʱ��
	CMD_PASSWORD = 0x05,							// ����
	CMD_CHK_PERIPH = 0x06,						// ��ȡ����״̬
};

// ͨ������
typedef enum
{
	COMM_TYPE_USART_DEBUG = 1,				// ���Դ���3
	COMM_TYPE_USART_FINGERPRINT = 2,	// ָ�ƴ���2
	COMM_TYPE_USBEP1 = 3,							// USB
	COMM_TYPE_USBEP2 = 4,							// USB
}CommType_TypdDef;



uint8_t Crc8(uint8_t* data, uint16_t length);
uint8_t Command_Process(void);
uint8_t Process_Data(CommType_TypdDef commtype, uint8_t* data, uint16_t length);
void Send_Command(uint8_t cmd, uint8_t subcmd, uint8_t flag, uint16_t datalen, uint8_t* data);
void Send_Data(CommType_TypdDef _commtype, uint8_t *data, uint16_t len);



#endif
