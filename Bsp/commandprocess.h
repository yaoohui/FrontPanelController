/*
*********************************************************************************************************
*
*	模块名称 : 串口接收数据处理
*	文件名称 : commandprocess.h
*	版    本 : V1.0
*	说    明 :
*			   
*	修改记录 :
*		版本号  日期		作者	说明
*		V1.0    2018-01-01	JOY	
*
*********************************************************************************************************
*/
#ifndef __COMMANDPROCESS_H
#define __COMMANDPROCESS_H

//#include "includes.h"
#include "main.h"

// 通信协议头格式结构体
typedef struct 
{
	uint16_t prefix;			// 前缀 0xAA, 0x99
	uint8_t modeid;				// 模块编号
	uint8_t cmd;					// 命令码
	uint8_t subcmd;				// 子命令码
	uint8_t flag;					// 发送方标志，发送方为0xFF，应答方为0x00，或其他值。见 CmdFlag_TypeDef。
	uint16_t len;					// 数据长度
}Cmdhead_TypeDef;

// 通信协议中发送方标志取值
typedef enum
{
	CMDFLAG_SEND = 0xFF,
	CMDFLAG_RES_OK = 0x00,
	CMDFLAG_RES_ERR = 0x01,
}CmdFlag_TypeDef;

// 命令码
enum CMD
{
	CMD_VERSION = 0xA0,								// 查询版本号
	CMD_ACK = 0xA1,										// 通信测试
	CMD_RESET = 0xA2,									// 系统复位
	CMD_FACTORY_SET = 0xA3,						// 恢复出厂设置
	CMD_BAUD = 0xB0,									// 串口波特率，保存至非易失性存储器
	CMD_RELAY = 0xA4,									// 继电器控制
	CMD_LCDTEST = 0xA5,								// 屏幕测试
	CMD_UID = 0xA6,										// 读取序列号
	CMD_FW_NAME = 0xA7,								// 读取固件名称
	
	// 正式指令
	CMD_SWITCH_WINDOW = 0x01,					// 切换界面
	CMD_COMM_TRANSFER = 0x02,					// 通信转发
	CMD_FINGERPRINT = 0x03,						// 指纹操作
	CMD_DATA_TIME = 0x04,							// 日期时间
	CMD_PASSWORD = 0x05,							// 密码
	CMD_CHK_PERIPH = 0x06,						// 读取外设状态
};

// 通信类型
typedef enum
{
	COMM_TYPE_USART_DEBUG = 1,				// 调试串口3
	COMM_TYPE_USART_FINGERPRINT = 2,	// 指纹串口2
	COMM_TYPE_USBEP1 = 3,							// USB
	COMM_TYPE_USBEP2 = 4,							// USB
}CommType_TypdDef;



uint8_t Crc8(uint8_t* data, uint16_t length);
uint8_t Command_Process(void);
uint8_t Process_Data(CommType_TypdDef commtype, uint8_t* data, uint16_t length);
void Send_Command(uint8_t cmd, uint8_t subcmd, uint8_t flag, uint16_t datalen, uint8_t* data);
void Send_Data(CommType_TypdDef _commtype, uint8_t *data, uint16_t len);



#endif
