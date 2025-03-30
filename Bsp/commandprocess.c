/*
*********************************************************************************************************
*
*	模块名称 : 串口接收数据处理
*	文件名称 : commandprocess.c
*	版    本 : V1.3
*	说    明 : 处理多接口的数据
*			   
*	修改记录 :
*		版本号  日期		作者	说明
*		V1.0    2018-01-01	JOY	
*		V1.1	2018-12-04  JOY
*		V1.2	2019-06-20	JOY		保存和加载参数函数单独为源文件
*		V1.3	2020-04-21	JOY		增加验证MODEID
*									增加保存到EEPROM功能
*									增加识别bootloader复位指令
*
*********************************************************************************************************
*/
#include "main.h"
#include "commandprocess.h"
//#include "flashsave.h"
#include "fingerprint.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
#include "global.h"


#define CMDPAYLOAD_POS  (sizeof(Cmdhead_TypeDef))	// 有效数据的位置，从0开始
#define CMDMIN_LENGTH (sizeof(Cmdhead_TypeDef) + 1)	// 通信协议格式最小长度

#define MODEID	0xA1		// 模块ID，串口通讯部分

uint8_t CommTempbuff[128];


//static uint8_t Process_Data(CommType_TypdDef commtype, uint8_t* data, uint16_t length);
static bool Check_Cmd_Protocol(uint8_t* data, uint16_t length);
void Send_Response(CommType_TypdDef _commtype, uint8_t _flag, uint8_t* _data, uint16_t _datalen);
void Data_Switching(CommType_TypdDef dataType, unsigned char* data, int length );

/*
*********************************************************************************************************
*	函 数 名: Command_Process
*	功能说明: 查询串口接收中断返回的数据，并进行处理
*			  起始码(2字节)0xAA,0x99，模块编号(1)，命令码(1)，子命令码(1)，发送方标志(1)，数据长度(2)，
*			  数据，异或校验(1)，总共至少9字节。
*				其中：数据长度仅为数据的字节数，不包括头和校验，低字节在前；异或校验为除自身外的所有字节。
*				发送方标志字节，发送方为0xFF，应答方为0x00，或其他值。
*	形    参: 无
*	返 回 值: 有处理数据返回命令码
*********************************************************************************************************
*/
uint8_t Command_Process(void)
{	
	uint8_t res = 0;

	if(Usart3RxFlag)
	{
//		Data_Switching(COMM_TYPE_USART_DEBUG, (uint8_t*)Usart3RxBuffer, Usart3RxLength);
		res = Process_Data(COMM_TYPE_USART_DEBUG, (uint8_t*)Usart3RxBuffer, Usart3RxLength);
		
		Usart3RxFlag = 0;
		Usart3RxLength = 0;
		HAL_UARTEx_ReceiveToIdle_DMA(&huart3, Usart3RxBuffer, MAX_USART_SIZE);   // 接收完毕后重启
		__HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);                        // 手动关闭DMA_IT_HT中断
	}
	
//	if(Usart2RxFlag)
//	{
////		Data_Switching(COMM_TYPE_USART_FINGERPRINT, (uint8_t*)Usart2RxBuffer, Usart2RxLength);
//		res = Process_Data(COMM_TYPE_USART_FINGERPRINT, (uint8_t*)Usart2RxBuffer, Usart2RxLength);

//		Usart2RxFlag = 0;
//		Usart2RxLength = 0;
//		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, Usart2RxBuffer, MAX_USART_SIZE);   // 接收完毕后重启
//		__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);                        // 手动关闭DMA_IT_HT中断
//	}
	return res;
}

/*
*********************************************************************************************************
*	函 数 名: Process_Data
*	功能说明: 数据处理（支持bootloader协议格式）
*	形    参: CommType_TypdDef commtype, uint8_t* data, uint16_t length
*	返 回 值: 有应答返回命令码，否则返回0
*********************************************************************************************************
*/
uint8_t Process_Data(CommType_TypdDef commtype, uint8_t* data, uint16_t length)
{
	uint8_t index = 0, cmd, subcmd, bNeedResponse = 0, flag = CMDFLAG_RES_OK;
	int16_t len;
	uint16_t prefix = 0; 
	int8_t temp8 = 0;
	
	prefix = ((Cmdhead_TypeDef*)data)->prefix;
	if( length < CMDMIN_LENGTH )	// 长度不足，返回
	{
		if(prefix != 0x90AA)// bootloader协议头为AA 90
			return 0;
	}
	
	if(!Check_Cmd_Protocol(data, length))
		return 0;
	
	FlagData.CommandTypePre = commtype;

	
//	IWDG_ReloadCounter();
	if(prefix == 0x90AA)	// bootloader
	{
		cmd = data[4];
		flag = data[5];
		if((flag == CMDFLAG_SEND) && (cmd == CMD_RESET))// 复位
		{
			// 发送应答
			uint8_t rstcmd[7] = {0xAA, 0x90, 0x02, 0x00, 0xA2, 0x00, 0x9A};
			Send_Data(commtype, rstcmd, 7);
			HAL_Delay(100);
			NVIC_SystemReset();
			return CMD_RESET;
		}
		else
			return 0;
	}		
	
//	IWDG_ReloadCounter();

	index = sizeof(Cmdhead_TypeDef);// 数据的位置
	cmd = ((Cmdhead_TypeDef*)data)->cmd;
	subcmd = ((Cmdhead_TypeDef*)data)->subcmd;
	len = ((Cmdhead_TypeDef*)data)->len;
	
	if (((Cmdhead_TypeDef*)data)->flag == CMDFLAG_SEND)// 为接收消息，需要应答
		bNeedResponse = 1;
	else// 为应答消息，不需要再次应答
		bNeedResponse = 0;

	switch(cmd)
	{
		case CMD_VERSION:	//0xA0,		// 查询版本号
		{
			len = 4;
			data[index] = FlagData.HardMainVersion;
			data[index+1] = FlagData.HardSubVersion;
			data[index+2] = FlagData.FirmwareMainVersion;
			data[index+3] = FlagData.FirmwareSubVersion;
			break;
		}
		case CMD_ACK:	// 0xA1 通信测试
		{
			break;
		}		
		case CMD_RESET:// 0xA2 系统复位
		{
			if(bNeedResponse)
				Send_Command(cmd, subcmd, CMDFLAG_RES_OK, 0, 0);
			HAL_Delay(100);
			NVIC_SystemReset();
			break;
		}
		case CMD_FACTORY_SET:// 0xA3,        // 恢复出厂设置
		{
			
			// 恢复参数默认值
			// 波特率
			ConfigParameter.baud = DEFAULT_BAUD;
			BLConfigParameter.baud = DEFAULT_BAUD;
			memset(ConfigParameter.password, DEFAULT_PASSWORD, MAX_PASSWORD_COUNT);
			
//			if(!SaveConfigData())	// 保存失败
//				flag = CMDFLAG_RES_ERR;
			break;
		}
		case CMD_BAUD:// = 0xB0,               // 串口波特率，保存至非易失性存储器
		{
			if(subcmd == 0)	// 读取
			{
				data[index] = GetBaudCode(ConfigParameter.baud);
			}
			else	// 设置
			{
				if(data[index] < 7)	// 波特率码有效
				{
					if(ConfigParameter.baud != VALID_BAUD[data[index]])	// 波特率不同时，保存
					{
						ConfigParameter.baud = VALID_BAUD[data[index]];
						BLConfigParameter.baud = ConfigParameter.baud;
						
//						if(!SaveConfigData())	// 保存失败
//							flag = CMDFLAG_RES_ERR;
					#ifdef USE_BOOTLOADER
						if(!SaveConfigDataBL())	// 保存失败
							flag = CMDFLAG_RES_ERR;
					#endif
					}
				}
			}
			break;
		}
		case CMD_RELAY:// 0xA4,              // 继电器控制
		{
//			if(subcmd == 0)	// 读取
//			{
//				data[index] = RelayRead();
//			}
//			else 	// 设置
//			{
//				if(data[index] == 0)
//					RelayOff();
//				else
//					RelayOn();
//			}
			break;
		}
//		case CMD_LCDTEST:// 0xA5,            // 屏幕测试
//		{
//			if(subcmd == 0)	// 屏幕测试
//			{
//				if(data[index] == 0)	// 开始测试
//					FlagData.CurrentMenu = MS_MAIN_DEBUG;
//				else
//					FlagData.CurrentMenu = MS_MAIN_WINDOW_PASSWORD;
//			}
//			else if(subcmd == 1 && len == 3) // 设置背景色
//			{
//				// 转换颜色
//				LCD_ClrScr(Color24to16(data[index], data[index+1], data[index+2]));
//				HAL_Delay(2000);
//			}
//			break;
//		}
		case CMD_UID:// = 0xA6,                // 读取序列号
		{
			len = 12;
			memcpy(&data[index], ConfigParameter.uid, 12);
			break;
		}
		case CMD_FW_NAME:// = 0xA7,            // 读取固件名称
		{
			len = strlen(FlagData.FirmwareName) + 1;
			memcpy(&data[index], FlagData.FirmwareName, len-1);
			data[index+len] = 0;// 增加末尾的\0
			break;
		}
		
		//----正式指令-----------------------------------------------------------
		case CMD_SWITCH_WINDOW:      // 0x01, 切换界面
		{
			FlagData.CurrentMenu = data[index] % (MS_MAIN_DEBUG + 1);
			break;
		}
		case CMD_COMM_TRANSFER:	// 0x02,      // 通信转发
		{
//			if(subcmd == 0)	// 读取
//			{
//				data[index] = FlagData.CommunicationTransfer;
//			}
//			else	// 设置
//			{
//				FlagData.CommunicationTransfer = data[index] % 4;	// 取值范围0~3
//			}
			
			if(subcmd == 0)// 读取
			{
				data[index] = FlagData.CommunicationTransfer;
			}
			else if(subcmd == 1)// 设置
			{
				temp8 = (data[index] >> 4) & 0x0F;
				if((data[index] & 0x0F) <= 4 && (temp8 <= 4))
					FlagData.CommunicationTransfer = data[index];
				else
					bNeedResponse = false;
			}
			else
				FlagData.CommunicationTransfer = 0;	// 清除转发

			
			break;
		}
		case CMD_FINGERPRINT:// 0x03,        // 指纹操作
		{
			if(subcmd == 0)	// 搜索指纹
			{
				uint16_t page = 0, score = 0;
				flag = Fingerprint_CheckFingerLoop(&temp8, &page, &score);
				*(uint16_t*)&data[index] = score;
				*(uint16_t*)&data[index+2] = page;
			}
			else if(subcmd == 1)	// 录入指纹
			{
				flag = Fingerprint_Register(&temp8);
				if(flag == RET_OK)	// 成功
				{
					*(uint16_t*)&data[index] = FingerprintPara.ValidPageId;
				}
				else
				{
					data[index] = 0;
					data[index+1] = 0;
				}
			}
			else if(subcmd == 2)	// 删除指纹
			{
				if(len == 2)
					flag = Fingerprint_DeleteOne(*(uint16_t*)&data[index]);// 删除指定指纹
				else if(len == 0)
					flag = Fingerprint_DeleteAll();// 删除所有指纹
				else
					bNeedResponse = false;
			}
			else if(subcmd == 3)	// 硬件信息
			{
				int8_t res = -1;
				
				// 读取参数表
				res = Fingerprint_ReadInfoPage();
				printf("读取参数表结果：%d\r\n", res);
				
				// 读取模板个数，确认录入指纹的个数
				res = Fingerprint_ReadTemplateNum(&FingerprintPara.TemplateNum);
				printf("读取模板个数结果：%d\r\n", res);

				// 读取索引表
				res = Fingerprint_ReadConList(FingerprintPara.ConList);
				printf("读取索引表结果：%d\r\n", res);
				if(res == RET_OK)
				{
					// 确认下次注册的位置
					FingerprintPara.ValidPageId = Fingerprint_GetValidTemplate();
				}
				
				len = 35;
				memcpy(&data[index], &FingerprintPara.FingerprintSize, 2);	// 指纹库大小
				data[index+2] = FingerprintPara.RegisterTimes;	// 注册次数
				memcpy(&data[index+3], &FingerprintPara.ConList, 32);		// 指纹使用列表
			}
			else if(subcmd == 4)	// 透传
			{
				flag = SendCmdAndWaitResponse(&data[index], len);
			}
			else if(subcmd == 5)	// 搜索指纹库（底层）
			{
				uint16_t page = 0, score = 0;
				flag = Fingerprint_Search(&page, &score);	// 搜索指纹库
				memcpy(&data[index], &page, 2);
				memcpy(&data[index+2], &score, 2);
			}
			else
				bNeedResponse = false;
			break;
		}
//		case CMD_DATA_TIME:// = 0x04,          // 日期时间
//		{
//			struct tm nowTime;
//			if(subcmd == 0)	// 读取
//			{
//				nowTime = Time_GetCalendarTime();
//				data[index] = nowTime.tm_year & 0xFF;
//				data[index+1] = (nowTime.tm_year >> 8) & 0xFF;
//				data[index+2] = nowTime.tm_mon;
//				data[index+3] = nowTime.tm_mday;
//				data[index+4] = nowTime.tm_wday;
//				data[index+5] = nowTime.tm_hour;
//				data[index+6] = nowTime.tm_min;
//				data[index+7] = nowTime.tm_sec;
////				printf("get time:%d-%02d-%02d %d %02d:%02d:%02d\r\n",
////					nowTime.tm_year,nowTime.tm_mon,nowTime.tm_mday, nowTime.tm_wday, nowTime.tm_hour,nowTime.tm_min,nowTime.tm_sec);
//			}
//			else // 设置
//			{
//				nowTime.tm_year = data[index+1];
//				nowTime.tm_year <<= 8;
//				nowTime.tm_year += data[index];
//				nowTime.tm_mon = data[index+2];
//				nowTime.tm_mday = data[index+3];
//				nowTime.tm_wday = data[index+4];
//				nowTime.tm_hour = data[index+5];
//				nowTime.tm_min = data[index+6];
//				nowTime.tm_sec = data[index+7];
//				Time_SetCalendarTime(nowTime);
//				FlagData.bNeedRefresh = 1;
//			}
//
//			break;
//		}
//		case CMD_PASSWORD:// = 0x05,           // 密码
//		{
//			if(subcmd == 0)	// 读取
//			{
//				len = MAX_PASSWORD_COUNT;
//				memcpy(&data[index], ConfigParameter.password, MAX_PASSWORD_COUNT);
//			}
//			else	// 设置
//			{
//				if(len == MAX_PASSWORD_COUNT)
//				{
//					memcpy(&ConfigParameter.password, &data[index], MAX_PASSWORD_COUNT);
//					if(!SaveConfigData())	// 保存失败
//						flag = CMDFLAG_RES_ERR;
//				}
//				else
//					flag = CMDFLAG_RES_ERR;
//			}
//			break;
//		}
		case CMD_CHK_PERIPH:// = 0x06,         // 读取外设状态
		{
			len = 1;
			data[index] = FlagData.chkUsb;
			data[index] <<= 1;
			data[index] |= FlagData.chkFingerprintDevice;
			data[index] <<= 1;
			data[index] |= FlagData.chkCTP;
			data[index] <<= 1;
			data[index] |= FlagData.chkClock;
			break;
		}
		default:
		{
			bNeedResponse = 0;// 无效指令不应答
			return 0;
		}
	}
	
//	IWDG_ReloadCounter();
	if(bNeedResponse)
		Send_Response(commtype, flag, data, len);//Send_Command(cmd, subcmd, flag, len, &data[index]);

	return cmd;
}

/*
*********************************************************************************************************
*	函 数 名: Check_Cmd_Protocol
*	功能说明: 校验串口接收数据的crc是否正确（支持bootloader协议格式）
*	形    参: uint8_t* data, uint16_t length
*	返 回 值: 校验正确返回true
*********************************************************************************************************
*/
static bool Check_Cmd_Protocol(uint8_t* data, uint16_t length)
{
	uint16_t prefix = 0, i = 0, len = 0;
	uint8_t crc = 0;
	
	prefix = ((Cmdhead_TypeDef*)data)->prefix;
	if((prefix != 0x99AA) && (prefix != 0x90AA))
		return false;
	
	if(prefix == 0x99AA)	// 用户指令协议
	{
		len = CMDMIN_LENGTH + ((Cmdhead_TypeDef*)data)->len;// 根据格式中的长度计算整个命令的长度
		if( len > length)
			return false;	
	}
	else if(prefix == 0x90AA)// bootloader协议
	{
		len = *(uint16_t*)&data[2] + 5;// 根据格式中的长度计算整个命令的长度
		if(len > length)// 未接收完整
			return false;
	}
	else
		return false;
	
	for(i=0; i<len-1; i++)
	{
		crc ^= data[i];
	}
	if(crc == data[i])
		return true;
	else
		return false;
}

/*
*********************************************************************************************************
*	函 数 名: Crc8
*	功能说明: 异或校验
*	形    参: uint8_t *_data: 数据
*			  uint16_t _datalen: 数据长度
*	返 回 值: 无
*********************************************************************************************************
*/
uint8_t Crc8(uint8_t* data, uint16_t length)
{
	uint16_t i;
	uint8_t crc = 0;
	
	for(i=0; i<length; i++)
		crc ^= data[i];
	
	return crc;
}

/*
*********************************************************************************************************
*	函 数 名: Send_Command
*	功能说明: 发送指令
*	形    参: uint8_t _cmd: 命令码，1字节
*			  uint8_t *_data: 数据
*			  uint16_t _datalen: 数据长度
*			  uint8_t _isresponse: 是否为应答，0-不是应答，1-为正确应答，2-为错误应答
*	返 回 值: 无
*********************************************************************************************************
*/
void Send_Command(uint8_t cmd, uint8_t subcmd, uint8_t flag, uint16_t datalen, uint8_t* data)
{
	uint16_t i,j;
	uint8_t crc;
	
	i = 0;
	TxBuffer[i++] = 0xAA;		// 起始码
	TxBuffer[i++] = 0x99;
	TxBuffer[i++] = MODEID;		// 模块编码
	TxBuffer[i++] = cmd;		// 命令码
	TxBuffer[i++] = subcmd;		// 子命令码
	TxBuffer[i++] = flag;		// 发送方标志
	*((uint16_t*)(&TxBuffer[i])) = datalen;		// 数据长度，低字节在前
	i += 2;
	if(datalen > 0)
		memcpy(&TxBuffer[i], data, datalen);
	i += datalen;
	crc = 0;
	for(j=0; j<i; j++)
		crc = crc ^ TxBuffer[j];
	TxBuffer[i++] = crc;
	
	HAL_UART_Transmit_IT(&huart3, TxBuffer, i);
}

void Send_Response(CommType_TypdDef _commtype, uint8_t _flag, uint8_t* _data, uint16_t _datalen)
{
	uint16_t i = 0;
	uint8_t crc;
	
	((Cmdhead_TypeDef*)_data)->flag = _flag;
	((Cmdhead_TypeDef*)_data)->len = _datalen;
	
	crc = 0;
	for(i = 0; i< _datalen + 8; i++)
		crc = crc ^ _data[i];
	_data[i++] = crc;
	
	Send_Data(_commtype, _data, i);
}

void Send_Data(CommType_TypdDef _commtype, uint8_t *data, uint16_t len)
{
	uint8_t res = 0;
	switch((uint32_t)_commtype)
	{
		case COMM_TYPE_USART_FINGERPRINT://=2,	// 指纹串口1
			HAL_UART_Transmit_IT(&huart2, data, len);
			break;
		
		case COMM_TYPE_USART_DEBUG:// = 1,		// 串口3
			HAL_UART_Transmit_IT(&huart3, data, len);
			break;
	
//		case COMM_TYPE_USBEP1:	// USB
//			res = UsbSendData(ENDP1, data, len);
//			break;
//		case COMM_TYPE_USBEP2:	// USB
//			res = UsbSendData(ENDP2, data, len);
//			break;
	}
	if(res)
		printf("Send Error! res=%d\r\n", res);
}

// 通信接口间数据转发
void Data_Switching(CommType_TypdDef dataType, unsigned char* data, int length )
{
	if( (FlagData.CommunicationTransfer & 0xF0) == 0  || (FlagData.CommunicationTransfer & 0x0F) == 0  )
		return;
	
	if( (FlagData.CommunicationTransfer >> 4) == dataType )
	{
		Send_Data( (CommType_TypdDef)(FlagData.CommunicationTransfer & 0x0F) , data ,length );
	}
	else if( (FlagData.CommunicationTransfer & 0x0F) == dataType )
	{
		Send_Data( (CommType_TypdDef)(FlagData.CommunicationTransfer  >> 4) , data ,length );
	}
}

//===================================================================================================================

