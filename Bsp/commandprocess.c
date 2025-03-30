/*
*********************************************************************************************************
*
*	ģ������ : ���ڽ������ݴ���
*	�ļ����� : commandprocess.c
*	��    �� : V1.3
*	˵    �� : �����ӿڵ�����
*			   
*	�޸ļ�¼ :
*		�汾��  ����		����	˵��
*		V1.0    2018-01-01	JOY	
*		V1.1	2018-12-04  JOY
*		V1.2	2019-06-20	JOY		����ͼ��ز�����������ΪԴ�ļ�
*		V1.3	2020-04-21	JOY		������֤MODEID
*									���ӱ��浽EEPROM����
*									����ʶ��bootloader��λָ��
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


#define CMDPAYLOAD_POS  (sizeof(Cmdhead_TypeDef))	// ��Ч���ݵ�λ�ã���0��ʼ
#define CMDMIN_LENGTH (sizeof(Cmdhead_TypeDef) + 1)	// ͨ��Э���ʽ��С����

#define MODEID	0xA1		// ģ��ID������ͨѶ����

uint8_t CommTempbuff[128];


//static uint8_t Process_Data(CommType_TypdDef commtype, uint8_t* data, uint16_t length);
static bool Check_Cmd_Protocol(uint8_t* data, uint16_t length);
void Send_Response(CommType_TypdDef _commtype, uint8_t _flag, uint8_t* _data, uint16_t _datalen);
void Data_Switching(CommType_TypdDef dataType, unsigned char* data, int length );

/*
*********************************************************************************************************
*	�� �� ��: Command_Process
*	����˵��: ��ѯ���ڽ����жϷ��ص����ݣ������д���
*			  ��ʼ��(2�ֽ�)0xAA,0x99��ģ����(1)��������(1)����������(1)�����ͷ���־(1)�����ݳ���(2)��
*			  ���ݣ����У��(1)���ܹ�����9�ֽڡ�
*				���У����ݳ��Ƚ�Ϊ���ݵ��ֽ�����������ͷ��У�飬���ֽ���ǰ�����У��Ϊ��������������ֽڡ�
*				���ͷ���־�ֽڣ����ͷ�Ϊ0xFF��Ӧ��Ϊ0x00��������ֵ��
*	��    ��: ��
*	�� �� ֵ: �д������ݷ���������
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
		HAL_UARTEx_ReceiveToIdle_DMA(&huart3, Usart3RxBuffer, MAX_USART_SIZE);   // ������Ϻ�����
		__HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);                        // �ֶ��ر�DMA_IT_HT�ж�
	}
	
//	if(Usart2RxFlag)
//	{
////		Data_Switching(COMM_TYPE_USART_FINGERPRINT, (uint8_t*)Usart2RxBuffer, Usart2RxLength);
//		res = Process_Data(COMM_TYPE_USART_FINGERPRINT, (uint8_t*)Usart2RxBuffer, Usart2RxLength);

//		Usart2RxFlag = 0;
//		Usart2RxLength = 0;
//		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, Usart2RxBuffer, MAX_USART_SIZE);   // ������Ϻ�����
//		__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);                        // �ֶ��ر�DMA_IT_HT�ж�
//	}
	return res;
}

/*
*********************************************************************************************************
*	�� �� ��: Process_Data
*	����˵��: ���ݴ���֧��bootloaderЭ���ʽ��
*	��    ��: CommType_TypdDef commtype, uint8_t* data, uint16_t length
*	�� �� ֵ: ��Ӧ�𷵻������룬���򷵻�0
*********************************************************************************************************
*/
uint8_t Process_Data(CommType_TypdDef commtype, uint8_t* data, uint16_t length)
{
	uint8_t index = 0, cmd, subcmd, bNeedResponse = 0, flag = CMDFLAG_RES_OK;
	int16_t len;
	uint16_t prefix = 0; 
	int8_t temp8 = 0;
	
	prefix = ((Cmdhead_TypeDef*)data)->prefix;
	if( length < CMDMIN_LENGTH )	// ���Ȳ��㣬����
	{
		if(prefix != 0x90AA)// bootloaderЭ��ͷΪAA 90
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
		if((flag == CMDFLAG_SEND) && (cmd == CMD_RESET))// ��λ
		{
			// ����Ӧ��
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

	index = sizeof(Cmdhead_TypeDef);// ���ݵ�λ��
	cmd = ((Cmdhead_TypeDef*)data)->cmd;
	subcmd = ((Cmdhead_TypeDef*)data)->subcmd;
	len = ((Cmdhead_TypeDef*)data)->len;
	
	if (((Cmdhead_TypeDef*)data)->flag == CMDFLAG_SEND)// Ϊ������Ϣ����ҪӦ��
		bNeedResponse = 1;
	else// ΪӦ����Ϣ������Ҫ�ٴ�Ӧ��
		bNeedResponse = 0;

	switch(cmd)
	{
		case CMD_VERSION:	//0xA0,		// ��ѯ�汾��
		{
			len = 4;
			data[index] = FlagData.HardMainVersion;
			data[index+1] = FlagData.HardSubVersion;
			data[index+2] = FlagData.FirmwareMainVersion;
			data[index+3] = FlagData.FirmwareSubVersion;
			break;
		}
		case CMD_ACK:	// 0xA1 ͨ�Ų���
		{
			break;
		}		
		case CMD_RESET:// 0xA2 ϵͳ��λ
		{
			if(bNeedResponse)
				Send_Command(cmd, subcmd, CMDFLAG_RES_OK, 0, 0);
			HAL_Delay(100);
			NVIC_SystemReset();
			break;
		}
		case CMD_FACTORY_SET:// 0xA3,        // �ָ���������
		{
			
			// �ָ�����Ĭ��ֵ
			// ������
			ConfigParameter.baud = DEFAULT_BAUD;
			BLConfigParameter.baud = DEFAULT_BAUD;
			memset(ConfigParameter.password, DEFAULT_PASSWORD, MAX_PASSWORD_COUNT);
			
//			if(!SaveConfigData())	// ����ʧ��
//				flag = CMDFLAG_RES_ERR;
			break;
		}
		case CMD_BAUD:// = 0xB0,               // ���ڲ����ʣ�����������ʧ�Դ洢��
		{
			if(subcmd == 0)	// ��ȡ
			{
				data[index] = GetBaudCode(ConfigParameter.baud);
			}
			else	// ����
			{
				if(data[index] < 7)	// ����������Ч
				{
					if(ConfigParameter.baud != VALID_BAUD[data[index]])	// �����ʲ�ͬʱ������
					{
						ConfigParameter.baud = VALID_BAUD[data[index]];
						BLConfigParameter.baud = ConfigParameter.baud;
						
//						if(!SaveConfigData())	// ����ʧ��
//							flag = CMDFLAG_RES_ERR;
					#ifdef USE_BOOTLOADER
						if(!SaveConfigDataBL())	// ����ʧ��
							flag = CMDFLAG_RES_ERR;
					#endif
					}
				}
			}
			break;
		}
		case CMD_RELAY:// 0xA4,              // �̵�������
		{
//			if(subcmd == 0)	// ��ȡ
//			{
//				data[index] = RelayRead();
//			}
//			else 	// ����
//			{
//				if(data[index] == 0)
//					RelayOff();
//				else
//					RelayOn();
//			}
			break;
		}
//		case CMD_LCDTEST:// 0xA5,            // ��Ļ����
//		{
//			if(subcmd == 0)	// ��Ļ����
//			{
//				if(data[index] == 0)	// ��ʼ����
//					FlagData.CurrentMenu = MS_MAIN_DEBUG;
//				else
//					FlagData.CurrentMenu = MS_MAIN_WINDOW_PASSWORD;
//			}
//			else if(subcmd == 1 && len == 3) // ���ñ���ɫ
//			{
//				// ת����ɫ
//				LCD_ClrScr(Color24to16(data[index], data[index+1], data[index+2]));
//				HAL_Delay(2000);
//			}
//			break;
//		}
		case CMD_UID:// = 0xA6,                // ��ȡ���к�
		{
			len = 12;
			memcpy(&data[index], ConfigParameter.uid, 12);
			break;
		}
		case CMD_FW_NAME:// = 0xA7,            // ��ȡ�̼�����
		{
			len = strlen(FlagData.FirmwareName) + 1;
			memcpy(&data[index], FlagData.FirmwareName, len-1);
			data[index+len] = 0;// ����ĩβ��\0
			break;
		}
		
		//----��ʽָ��-----------------------------------------------------------
		case CMD_SWITCH_WINDOW:      // 0x01, �л�����
		{
			FlagData.CurrentMenu = data[index] % (MS_MAIN_DEBUG + 1);
			break;
		}
		case CMD_COMM_TRANSFER:	// 0x02,      // ͨ��ת��
		{
//			if(subcmd == 0)	// ��ȡ
//			{
//				data[index] = FlagData.CommunicationTransfer;
//			}
//			else	// ����
//			{
//				FlagData.CommunicationTransfer = data[index] % 4;	// ȡֵ��Χ0~3
//			}
			
			if(subcmd == 0)// ��ȡ
			{
				data[index] = FlagData.CommunicationTransfer;
			}
			else if(subcmd == 1)// ����
			{
				temp8 = (data[index] >> 4) & 0x0F;
				if((data[index] & 0x0F) <= 4 && (temp8 <= 4))
					FlagData.CommunicationTransfer = data[index];
				else
					bNeedResponse = false;
			}
			else
				FlagData.CommunicationTransfer = 0;	// ���ת��

			
			break;
		}
		case CMD_FINGERPRINT:// 0x03,        // ָ�Ʋ���
		{
			if(subcmd == 0)	// ����ָ��
			{
				uint16_t page = 0, score = 0;
				flag = Fingerprint_CheckFingerLoop(&temp8, &page, &score);
				*(uint16_t*)&data[index] = score;
				*(uint16_t*)&data[index+2] = page;
			}
			else if(subcmd == 1)	// ¼��ָ��
			{
				flag = Fingerprint_Register(&temp8);
				if(flag == RET_OK)	// �ɹ�
				{
					*(uint16_t*)&data[index] = FingerprintPara.ValidPageId;
				}
				else
				{
					data[index] = 0;
					data[index+1] = 0;
				}
			}
			else if(subcmd == 2)	// ɾ��ָ��
			{
				if(len == 2)
					flag = Fingerprint_DeleteOne(*(uint16_t*)&data[index]);// ɾ��ָ��ָ��
				else if(len == 0)
					flag = Fingerprint_DeleteAll();// ɾ������ָ��
				else
					bNeedResponse = false;
			}
			else if(subcmd == 3)	// Ӳ����Ϣ
			{
				int8_t res = -1;
				
				// ��ȡ������
				res = Fingerprint_ReadInfoPage();
				printf("��ȡ����������%d\r\n", res);
				
				// ��ȡģ�������ȷ��¼��ָ�Ƶĸ���
				res = Fingerprint_ReadTemplateNum(&FingerprintPara.TemplateNum);
				printf("��ȡģ����������%d\r\n", res);

				// ��ȡ������
				res = Fingerprint_ReadConList(FingerprintPara.ConList);
				printf("��ȡ����������%d\r\n", res);
				if(res == RET_OK)
				{
					// ȷ���´�ע���λ��
					FingerprintPara.ValidPageId = Fingerprint_GetValidTemplate();
				}
				
				len = 35;
				memcpy(&data[index], &FingerprintPara.FingerprintSize, 2);	// ָ�ƿ��С
				data[index+2] = FingerprintPara.RegisterTimes;	// ע�����
				memcpy(&data[index+3], &FingerprintPara.ConList, 32);		// ָ��ʹ���б�
			}
			else if(subcmd == 4)	// ͸��
			{
				flag = SendCmdAndWaitResponse(&data[index], len);
			}
			else if(subcmd == 5)	// ����ָ�ƿ⣨�ײ㣩
			{
				uint16_t page = 0, score = 0;
				flag = Fingerprint_Search(&page, &score);	// ����ָ�ƿ�
				memcpy(&data[index], &page, 2);
				memcpy(&data[index+2], &score, 2);
			}
			else
				bNeedResponse = false;
			break;
		}
//		case CMD_DATA_TIME:// = 0x04,          // ����ʱ��
//		{
//			struct tm nowTime;
//			if(subcmd == 0)	// ��ȡ
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
//			else // ����
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
//		case CMD_PASSWORD:// = 0x05,           // ����
//		{
//			if(subcmd == 0)	// ��ȡ
//			{
//				len = MAX_PASSWORD_COUNT;
//				memcpy(&data[index], ConfigParameter.password, MAX_PASSWORD_COUNT);
//			}
//			else	// ����
//			{
//				if(len == MAX_PASSWORD_COUNT)
//				{
//					memcpy(&ConfigParameter.password, &data[index], MAX_PASSWORD_COUNT);
//					if(!SaveConfigData())	// ����ʧ��
//						flag = CMDFLAG_RES_ERR;
//				}
//				else
//					flag = CMDFLAG_RES_ERR;
//			}
//			break;
//		}
		case CMD_CHK_PERIPH:// = 0x06,         // ��ȡ����״̬
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
			bNeedResponse = 0;// ��Чָ�Ӧ��
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
*	�� �� ��: Check_Cmd_Protocol
*	����˵��: У�鴮�ڽ������ݵ�crc�Ƿ���ȷ��֧��bootloaderЭ���ʽ��
*	��    ��: uint8_t* data, uint16_t length
*	�� �� ֵ: У����ȷ����true
*********************************************************************************************************
*/
static bool Check_Cmd_Protocol(uint8_t* data, uint16_t length)
{
	uint16_t prefix = 0, i = 0, len = 0;
	uint8_t crc = 0;
	
	prefix = ((Cmdhead_TypeDef*)data)->prefix;
	if((prefix != 0x99AA) && (prefix != 0x90AA))
		return false;
	
	if(prefix == 0x99AA)	// �û�ָ��Э��
	{
		len = CMDMIN_LENGTH + ((Cmdhead_TypeDef*)data)->len;// ���ݸ�ʽ�еĳ��ȼ�����������ĳ���
		if( len > length)
			return false;	
	}
	else if(prefix == 0x90AA)// bootloaderЭ��
	{
		len = *(uint16_t*)&data[2] + 5;// ���ݸ�ʽ�еĳ��ȼ�����������ĳ���
		if(len > length)// δ��������
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
*	�� �� ��: Crc8
*	����˵��: ���У��
*	��    ��: uint8_t *_data: ����
*			  uint16_t _datalen: ���ݳ���
*	�� �� ֵ: ��
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
*	�� �� ��: Send_Command
*	����˵��: ����ָ��
*	��    ��: uint8_t _cmd: �����룬1�ֽ�
*			  uint8_t *_data: ����
*			  uint16_t _datalen: ���ݳ���
*			  uint8_t _isresponse: �Ƿ�ΪӦ��0-����Ӧ��1-Ϊ��ȷӦ��2-Ϊ����Ӧ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Send_Command(uint8_t cmd, uint8_t subcmd, uint8_t flag, uint16_t datalen, uint8_t* data)
{
	uint16_t i,j;
	uint8_t crc;
	
	i = 0;
	TxBuffer[i++] = 0xAA;		// ��ʼ��
	TxBuffer[i++] = 0x99;
	TxBuffer[i++] = MODEID;		// ģ�����
	TxBuffer[i++] = cmd;		// ������
	TxBuffer[i++] = subcmd;		// ��������
	TxBuffer[i++] = flag;		// ���ͷ���־
	*((uint16_t*)(&TxBuffer[i])) = datalen;		// ���ݳ��ȣ����ֽ���ǰ
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
		case COMM_TYPE_USART_FINGERPRINT://=2,	// ָ�ƴ���1
			HAL_UART_Transmit_IT(&huart2, data, len);
			break;
		
		case COMM_TYPE_USART_DEBUG:// = 1,		// ����3
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

// ͨ�Žӿڼ�����ת��
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

