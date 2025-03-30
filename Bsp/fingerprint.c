/*
*********************************************************************************************************
*
*	ģ������ : ָ��ʶ��ģ�� YX-F112S11
*	�ļ����� : yxf112s11.c
*	��    �� : V1.0
*	˵    �� : ʹ�ô���ͨ��
*			  	��ʽ��ͷ(2�ֽ�)����ַ(4�ֽ�)��������PID(1�ֽ�)��������(2�ֽ�)�����ݣ�N-2�ֽڣ���У���(2�ֽ�)
*				������ݸ�ʽ
*	�޸ļ�¼ :
*		�汾��  ����       	����    ˵��
*		V1.0	2020-10-03	JOY		
*
*********************************************************************************************************
*/
#include "fingerprint.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
#include "global.h"
#include "io.h"
#include "custom.h"

#define MAX_TIMEOUT  1000                                 // ��λ��ms
#define MAXRXBUFFER  164
static uint8_t tempBuffer[MAXRXBUFFER];                   // ���ջ�����
volatile uint8_t* FingerprintFlag = &Usart2RxFlag;        // ������ɱ�־
volatile uint16_t* FingerprintLength = &Usart2RxLength;   // ���ճ���
volatile uint8_t* FingerprintBuffer = Usart2RxBuffer;     // ���ջ�����
uint8_t Timeout = 0;																			// ��ʱʱ��

Fingerprint_Parameter_TypeDef FingerprintPara;

/*
*********************************************************************************************************
*	�� �� ��: Fingerprintf_Init
*	����˵��: ��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void Fingerprintf_Init(void)
{
	int8_t res = -1;
	uint16_t tempu16 = 0;
	
	// ��ȡ��Ϣ
	
	memset(&FingerprintPara, 0, sizeof(FingerprintPara));
	
	// ��֤����
	res = Fingerprint_VerifyPassword(0);
	if(res != RET_OK)
	{
		printf("Fingerpint verify password error(%d)!\r\n", res);
		FlagData.chkFingerprintDevice = false;
	}
	else
		FlagData.chkFingerprintDevice = true;
	
	HAL_Delay(10);
	
	// ��ȡ������
	res = Fingerprint_ReadInfoPage();
	if(res == RET_OK)
	{
		printf("ָ��ע�������%d��ָ�ƿ��С��%d��ģ���С��%d\r\n",
		FingerprintPara.RegisterTimes, FingerprintPara.FingerprintSize, FingerprintPara.TemplateSize);
	}
	else
		printf("Fingerprint_ReadInfoPage error(%d)!\r\n", res);

	
	// ��ȡģ�������ȷ��¼��ָ�Ƶĸ���
	res = Fingerprint_ReadTemplateNum(&FingerprintPara.TemplateNum);
	if(res == RET_OK)
	{
		printf("ָ�Ƹ�����%d\r\n", FingerprintPara.TemplateNum);
	}
	else
		printf("Fingerprint get template error!\r\n");
	
	// ��ȡ������
	res = Fingerprint_ReadConList(FingerprintPara.ConList);
	if(res == RET_OK)
	{
		printf("Fingerprint conlist: \r\n");
		for(tempu16 = 0; tempu16 < 32; tempu16++)
		{
			printf("%02X ", FingerprintPara.ConList[tempu16]);
		}
		printf("\r\n");
    
    // ǰ9λָ�Ʒֲ����
    for(uint8_t i = 0; i < 8; i++)
    {
      if((FingerprintPara.ConList[0] & (1 << i)) != 0)
      {
        FP_HAVE_Flag[i] = true;
      }
    }
    if((FingerprintPara.ConList[1] & 1) != 0)
    {
      FP_HAVE_Flag[8] = true;
    }
  
		
		// ȷ���´�ע���λ��
		FingerprintPara.ValidPageId = Fingerprint_GetValidTemplate();
		if(FingerprintPara.ValidPageId >= 0)
			printf("��һ��ָ��ID��%d\r\n", FingerprintPara.ValidPageId);
		else
			printf("�޿���ָ�ƿ⣡\r\n");
	}
	else
		printf("Fingerprint get conlist error!\r\n");
}

/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_GetValidTemplate
*	����˵��: ��ÿ��е�ģ�壬����һ�δ洢λ�ã�pageID
*	��    ��: ��
*	�� �� ֵ: -1���޿��е�ģ�壬�������ɹ�������pageID
*********************************************************************************************************
*/
int16_t Fingerprint_GetValidTemplate(void)
{
	uint16_t i = 0, tempu16 = 0;
	
	for(tempu16 = 0; tempu16 < 32; tempu16++)
	{
		if(FingerprintPara.ConList[tempu16] != 0xFF)// �п��е�����
		{
			for(i = 0; i < 8; i++) // �ӵ�λ��ʼ
			{
				if((FingerprintPara.ConList[tempu16] & (1 << i)) == 0)// ����λ
				{
					return (i + tempu16*8);
				}
			}
		}
	}
	return -1;
}

void SendCmd(uint8_t *_cmdbuff, uint16_t _cmdlen)
{
	//FingerprintCmdFormat_TypeDef  cmdformat;
	uint16_t sum = 0, i = 0, len = _cmdlen + 2;
	uint16_t index = 0;
	
	memset(tempBuffer, 0, MAXRXBUFFER);
	tempBuffer[index++] = 0xEF;
	tempBuffer[index++] = 0x01;
	tempBuffer[index++] = 0xFF;
	tempBuffer[index++] = 0xFF;
	tempBuffer[index++] = 0xFF;
	tempBuffer[index++] = 0xFF;
	tempBuffer[index++] = PID_CMD;
	sum += PID_CMD;
	tempBuffer[index++] = len >> 8;
	tempBuffer[index++] = len & 0xFF;
	sum += (len >> 8);
	sum += (len & 0xFF);
	memcpy(&tempBuffer[index], _cmdbuff, _cmdlen);
	index += _cmdlen;
	for(i = 0; i < _cmdlen; i++)
		sum += _cmdbuff[i];
	tempBuffer[index++] = sum >> 8;
	tempBuffer[index++] = sum & 0xFF;
	
	#if 0
	printf("Send cmd: \r\n");
	for(i = 0; i < index; i++)
		printf("%02X \r\n", tempBuffer[i]);
	printf("\r\n");
	#endif

//	UsartSendData(Usart1, tempBuffer, index);
	HAL_UART_Transmit_IT(&huart2, tempBuffer, index);
}

/*
*********************************************************************************************************
*	�� �� ��: SendCmdAndWaitResponse
*	����˵��: ����ָ��ȴ�Ӧ��
*	��    ��:
*	�� �� ֵ: -1����Ӧ��0���ɹ���-2��У�����-3������Ӧ������@Fingerprint_Result_TypeDef
*********************************************************************************************************
*/
int8_t SendCmdAndWaitResponse(uint8_t *_cmdbuff, uint16_t _cmdlen)
{
	int8_t ret = 0;
	uint16_t timeout = 0, datalen = 0, i = 0, sum = 0, len = 0;
	
	*FingerprintLength = 0;
	*FingerprintFlag = 0;
	memset(tempBuffer, 0, MAXRXBUFFER);
	SendCmd(_cmdbuff, _cmdlen);
	
	while(!(*FingerprintFlag))
	{
		HAL_Delay(10);
		timeout += 10;
		if(timeout >= MAX_TIMEOUT)
			break;
//		IWDG_ReloadCounter();
	}
	
	if(*FingerprintFlag)	// ���յ�Ӧ��
	{
		HAL_Delay(100);	// �ȴ��������ݰ�
		datalen = *FingerprintLength;
		memcpy(tempBuffer, (void*)FingerprintBuffer, datalen);
		sum = 0;
		
		#if 0
		printf("Usart2 Recv cmd: \r\n");
		for(i = 0; i < datalen; i++)
			printf("%02X ", tempBuffer[i]);
		printf("\r\n");
		#endif
		
		if( ((FingerprintCmdFormat_TypeDef*)tempBuffer)->start[0] == 0xEF &&
			((FingerprintCmdFormat_TypeDef*)tempBuffer)->start[1] == 0x01 )
		{
			
			len = ((FingerprintCmdFormat_TypeDef*)tempBuffer)->length[0];
			len <<= 8;
			len += ((FingerprintCmdFormat_TypeDef*)tempBuffer)->length[1];
			sum += ((FingerprintCmdFormat_TypeDef*)tempBuffer)->pid;
			sum += ((FingerprintCmdFormat_TypeDef*)tempBuffer)->length[0];
			sum += ((FingerprintCmdFormat_TypeDef*)tempBuffer)->length[1];
			for(i = 0; i < len-2; i++)
				sum += tempBuffer[9+i];
			
			if((sum >> 8) == tempBuffer[9+i] &&
				(sum & 0xFF) == tempBuffer[10+i] )// У����ȷ
			{
				if( ((FingerprintCmdFormat_TypeDef*)tempBuffer)->pid == PID_RESPONSE)	// Ӧ��
				{
					ret = tempBuffer[9];
				}
				else if( ((FingerprintCmdFormat_TypeDef*)tempBuffer)->pid == PID_LASTDATA)	// �������
				{
					ret = 0;
				}
				else
					ret = -3;	// ����Ӧ��
			}
			else
			{
				ret = -2;	// У�����
			}
		}
		*FingerprintLength = 0;
		*FingerprintFlag = 0;
//		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, Usart2RxBuffer, MAX_USART_SIZE);   // ������Ϻ�����
//		__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);                        // �ֶ��ر�DMA_IT_HT�ж�
	}
	else
	{
		printf("NO response!\r\n");
		ret = -1;	// ��Ӧ��
	}
	
	return ret;	
}

/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_GetImg
*	����˵��: ��ȡָ��ͼ��
*	��    ��: ��
*	�� �� ֵ: -1����Ӧ��0���ɹ�
*********************************************************************************************************
*/
int8_t Fingerprint_GetImg(void)
{
	uint8_t data = CMD_GETIMG;
	int8_t ret = 0;
	// ����   EF 01 FF FF FF FF 01 00 03 01 00 05
	// ��ָ�� EF 01 FF FF FF FF 07 00 03 02 00 0C
	// ��⵽ EF 01 FF FF FF FF 07 00 03 00 00 0A
	ret = SendCmdAndWaitResponse(&data, 1);

	return ret;
}
/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_GetRegImg
*	����˵��: ��ȡע����ָ��ͼ��
*	��    ��: ��
*	�� �� ֵ: -1����Ӧ��0���ɹ�
*********************************************************************************************************
*/
int8_t Fingerprint_GetRegImg(void)
{
	uint8_t data = CMD_GETREGIMG;// = 0x29,   // ע���û�ȡͼ��
	int8_t ret = 0;
	// ����   EF 01 FF FF FF FF 01 00 03 29 00 2D
	// ��ָ�� EF 01 FF FF FF FF 07 00 03 02 00 0C
	// ��⵽ EF 01 FF FF FF FF 07 00 03 00 00 0A
	ret = SendCmdAndWaitResponse(&data, 1);

	return ret;
}

int8_t Fingerprint_Match(void)
{
	uint8_t data = CMD_MATCH;
	int8_t ret = 0;

	// ����  EF 01 FF FF FF FF 01 00 03 03 00 07
	//       EF 01 FF FF FF FF 07 00 05 08 00 00 00 14 
	ret = SendCmdAndWaitResponse(&data, 1);

	return ret;		
}

/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_GetTZ
*	����˵��: ������ȡ
*	��    ��: uint8_t _bufferid��bufferID����1��ʼ
*	�� �� ֵ: -1����Ӧ��0���ɹ�
*********************************************************************************************************
*/
int8_t Fingerprint_GetTZ(uint8_t _bufferid)
{
	uint8_t data[2] = {CMD_IMG2TZ, 1};
	int8_t ret = 0;

	// ����   EF 01 FF FF FF FF 01 00 04 02 0X xx xx
	// �ɹ�   EF 01 FF FF FF FF 07 00 03 00 00 0A
	if(_bufferid != 0)
		data[1] = _bufferid;
	ret = SendCmdAndWaitResponse(data, 2);

	return ret;		
}

/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_Search
*	����˵��: ����ָ��
*	��    ��: uint16_t _page����������ҳ��, uint16_t _score���÷�
*	�� �� ֵ: -1����Ӧ��0���ɹ�
*********************************************************************************************************
*/
int8_t Fingerprint_Search(uint16_t *_page, uint16_t *_score)
{
	uint8_t data[6] = {CMD_SEARCH, 1, 0,0, 0x01,0x2C};// �����������buffer��ţ�1��2��������ģ����ʼ��ţ�2�ֽڣ���������ģ��������2�ֽڣ�
	int8_t ret = 0;
	uint16_t tempu16 = 0;

	// ����   EF 01 FF FF FF FF 01 00 08  04  01  00 00  01 2C  00 3B
	// Ӧ��   EF 01 FF FF FF FF 07 00 07  09  00 00  00 00  00 17 // û���ҵ�ƥ���ָ��
	// Ӧ��   EF 01 FF FF FF FF 07 00 07  00  00 01  03 1D  00 2F // �ҵ�ָ�ƣ�ģ��ı��=1��score=0x031D

	ret = SendCmdAndWaitResponse(data, 6);
	if(ret == RET_OK)
	{
		tempu16 = tempBuffer[10];
		tempu16 <<= 8;
		*_page = tempu16 + tempBuffer[11];
		tempu16 = tempBuffer[12];
		tempu16 <<= 8;
		*_score = tempu16 + tempBuffer[13];
	}
	return ret;		
}

/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_RegModel
*	����˵��: �ϲ�����
*	��    ��: ��
*	�� �� ֵ: -1����Ӧ��0���ɹ�
*********************************************************************************************************
*/
int8_t Fingerprint_RegModel(void)
{
	uint8_t data = CMD_REGMODEL;// = 5, //��5������ģ��ϲ���1��ģ��
	int8_t ret = 0;

	// ����  EF 01 ff ff ff ff 01 00 03 05 00 09 	............�ϲ�ģ��
	// Ӧ��  01 ff ff ff ff 07 00 03 00 00 0a 	............�ɹ�

	ret = SendCmdAndWaitResponse(&data, 1);

	return ret;	
}

/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_StoreModel
*	����˵��: ����ģ��
*	��    ��: uint16_t _tempid���洢λ��
*	�� �� ֵ:
*********************************************************************************************************
*/
int8_t Fingerprint_StoreModel(uint16_t _tempid)
{
	uint8_t data[4] = {CMD_STOREMODEL, 1, 0, 0};// ����ָ��ģ�嵽ָ�ƿ⣬bufferID=1, TempIDΪ�浽���ݿ��е����
	int8_t ret = 0;
	data[2] = _tempid>>8;
	data[3] = _tempid& 0xFF;
	// ����  EF 01 ff ff ff ff 01 00 06  06  01  00 02  00 10 	...............����ָ��buffer1�������02
	// Ӧ��  EF 01 ff ff ff ff 07 00 03  00  00 0a 	............�ɹ�

	ret = SendCmdAndWaitResponse(data, 4);

	return ret;		
}

/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_Delete
*	����˵��: ɾ��ָ��
*	��    ��: uint16_t _id��ָ��id
*			  uint16_t _count������
*	�� �� ֵ: 0���ɹ���
*********************************************************************************************************
*/
int8_t Fingerprint_Delete(uint16_t _id, uint16_t _count)
{
	uint8_t data[5] = {CMD_DELETECHAR, 0,0, 0,1};// = 0x0C,	// �����ݿ���ɾ��ģ��
	int8_t ret = 0;
	// ����  EF 01 FF FF FF FF 01 00 07  0C  00 00  00 01  00 15  pageID=0, 1��
	// �ɹ�  EF 01 FF FF FF FF 07 00 03  00  00 0A
	data[1] = _id >> 8;	// ��ʼλ��
	data[2] = _id & 0xFF;
	data[3] = _count >> 8;
	data[4] = _count & 0xFF;
	
	ret = SendCmdAndWaitResponse(data, 5);

	return ret;
}
/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_DeleteAll
*	����˵��: ɾ������ָ��
*	��    ��: ��
*	�� �� ֵ: 0���ɹ�
*********************************************************************************************************
*/
int8_t Fingerprint_DeleteAll(void)
{
	uint8_t data = CMD_EMPTY;//= 0x0D,		// ������ݿ������е�ָ��ģ��
	int8_t ret = 0;

	ret = SendCmdAndWaitResponse(&data, 1);

	return ret;
}

/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_VerifyPassword
*	����˵��: ��֤���Ĭ������0x00000000
*	��    ��: uint32_t _pw
*	�� �� ֵ:
*********************************************************************************************************
*/
int8_t Fingerprint_VerifyPassword(uint32_t _pw)
{
	uint8_t data[5] = {CMD_VERIFY_PASSWORD,0,0,0,0};// 0x13, // ��֤���Ĭ�����룺0x00000000
	int8_t ret = 0;

//	���� EF 01 FF FF FF FF 01 00 07 13 00 00 00 00 00 1B	PID:0x13 ��֤ģ������VfyPwd
//	Ӧ�� EF 01 FF FF FF FF 07 00 03 00 00 0A				OK	*_num = 0;
	if(_pw != 0)
	{
		data[1] = (_pw >> 24) & 0xFF;
		data[2] = (_pw >> 16) & 0xFF;
		data[3] = (_pw >> 8) & 0xFF;
		data[4] = _pw & 0xFF;
	}
	ret = SendCmdAndWaitResponse(data, 5);
	return ret;		
}


/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_ReadInfoPage
*	����˵��: ��ȡinfomation page ���ڵĲ���ҳ
*	��    ��: ��
*	�� �� ֵ: 0:OK, -2��У�����-3���������ݰ���-4��û�����ݰ���ͷ������@Fingerprint_Result_TypeDef
*********************************************************************************************************
*/
int8_t Fingerprint_ReadInfoPage(void)
{
	uint8_t data = CMD_READINFPAGE;// 0x16,  // ��ȡFLASH information page ���ڵĲ���ҳ
	int8_t ret = 0;
	uint8_t *pdata = NULL;
	uint16_t len = 0, sum = 0, i = 0;
	const uint16_t datapos = 9;
	
	// ����  EF 01 FF FF FF FF 01 00 03 16 00 1A			PID:0x16 ������ҳPS_ReadINFpage��Ӧ���������������ݰ�
	// Ӧ��  EF 01 FF FF FF FF 07 00 03 00 00 0A EF 01 FF FF FF FF 08  00 82  00 04  08 00  00 78 00 03  FF FF FF FF ....
	ret = SendCmdAndWaitResponse(&data, 1);
	if(ret == RET_OK)
	{
		// Ӧ����������ݰ�����֤
		pdata = &tempBuffer[0];
		
		if( ((FingerprintCmdFormat_TypeDef*)pdata)->start[0] == 0xEF &&
			((FingerprintCmdFormat_TypeDef*)pdata)->start[1] == 0x01 )
		{
			
			len = ((FingerprintCmdFormat_TypeDef*)pdata)->length[0];
			len <<= 8;
			len += ((FingerprintCmdFormat_TypeDef*)pdata)->length[1];
			sum += ((FingerprintCmdFormat_TypeDef*)pdata)->pid;
			sum += ((FingerprintCmdFormat_TypeDef*)pdata)->length[0];
			sum += ((FingerprintCmdFormat_TypeDef*)pdata)->length[1];
			for(i = 0; i < len-2; i++)
				sum += pdata[9+i];
			
			if((sum >> 8) == pdata[9+i] &&
				(sum & 0xFF) == pdata[10+i] )// У����ȷ
			{
				if( ((FingerprintCmdFormat_TypeDef*)pdata)->pid == PID_LASTDATA)	// ���һ�����ݰ�
				{
					ret = RET_OK;
					pdata += datapos;
					FingerprintPara.RegisterTimes = *pdata;	// ע�����
					pdata++;
					FingerprintPara.RegisterTimes <<= 8;
					FingerprintPara.RegisterTimes += *pdata;
					pdata++;
					FingerprintPara.TemplateSize = *pdata;	// ģ���С
					pdata++;
					FingerprintPara.TemplateSize <<= 8;
					FingerprintPara.TemplateSize += *pdata;
					pdata++;
					FingerprintPara.FingerprintSize = *pdata;	// ָ�ƿ��С
					pdata++;
					FingerprintPara.FingerprintSize <<= 8;
					FingerprintPara.FingerprintSize += *pdata;
				}
				else
					ret = -3;	// ��������
			}
			else
			{
				ret = -2;	// У�����
			}
		}
		else
		{
			ret = -4;// û�����ݰ���ͷ
		}
	}
	return ret;		
}

/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_ReadTemplateNum
*	����˵��: ��ȡģ������
*	��    ��: uint16_t *_num��template number
*	�� �� ֵ:
*********************************************************************************************************
*/
int8_t Fingerprint_ReadTemplateNum(uint16_t *_num)	// ��ȡģ������
{
	uint8_t data = CMD_TEMPLATENUM;// = 0x1D, // ��ȡ���ݿ���ģ������
	int8_t ret = 0;
	uint16_t num = 0;

	// ����  EF 01 FF FF FF FF 01 00 03  1D  00 21			PID:0x1D ��ȡģ��ģ������ TemplateNum
	// Ӧ��  EF 01 FF FF FF FF 07 00 05  00  00 02  00 0E
	*_num = 0;
	ret = SendCmdAndWaitResponse(&data, 1);
	if(ret == RET_OK)
	{
		num = tempBuffer[10];
		num <<= 8;
		num += tempBuffer[11];
		*_num = num;
	}
	return ret;		
}

/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_ReadConList
*	����˵��: ��ȡ���ݿ�����Чģ�������飬��64�ֽ�512��ģ�壬��λʹ�ã�ÿ���ֽڵĵ�bitΪ��template id
*			  ���300~511��ģ�岻���ڣ���˶��صı�Ǿ�Ϊ0
*	��    ��: uint8_t *_list��64�ֽڵ�����
*	�� �� ֵ:
*********************************************************************************************************
*/
int8_t Fingerprint_ReadConList(uint8_t *_list)
{
	uint8_t data[2] = {CMD_READCONLIST, 0};// 0x1F,	// ��ȡ���ݿ���ģ�������顣������ҳ��0����Ӧģ��0~256������
	int8_t ret = 0;

	/*
		EF 01 FF FF FF FF 01 00 04  1F  00  00 24			PID:0x1F �����ݿ��ж�ȡ��Ч��ģ��������index0 ReadConList
		EF 01 FF FF FF FF 07 00 23 00 03 00 00 00 00 00
		 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
		 00 00 00 00 00 00 00 00 00 00 00 2D

		EF 01 FF FF FF FF 01 00 04  1F 01  00 25			PID:0x1F �����ݿ��ж�ȡ��Ч��ģ��������index1 ReadConList
		EF 01 FF FF FF FF 07 00 23 00 00 00 00 00 00 00
		 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
		 00 00 00 00 00 00 00 00 00 00 00 2A
	*/

	ret = SendCmdAndWaitResponse(data, 2);
	if(ret == RET_OK)
	{
		memcpy(_list, &tempBuffer[10], 32);
		#if 0	// ��֧��������ҳ��1
		data[0] = CMD_READCONLIST;
		data[1] = 1;
		HAL_Delay(10);
		ret = SendCmdAndWaitResponse(data, 2);
		if(ret == RET_OK)
		{
			memcpy(_list+32, &tempBuffer[10], 32);
		}
		#endif
	}
	return ret;		
}

/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_CheckFinger
*	����˵��: ��ָ֤�ƣ�����һ�μ��һ�Σ���Ҫ��ǰ������ָ
*	��    ��: uint8_t *_result������ָ��ƥ�����Ϣ
*	�� �� ֵ: -3����ָ�ƣ�0��ָ��ƥ�䣬-1����ȡ����ʧ�ܣ�-2������ָ�ƿ�ʧ��
*********************************************************************************************************
*/
int8_t Fingerprint_CheckFinger(int8_t *_result)
{
	int8_t ret = 0;
	uint16_t page = 0, score = 0;
	
	*_result = -1;
	ret = Fingerprint_GetImg();	// ��ȡͼ��
	*_result = ret;
	if(ret == RET_OK)
	{
		HAL_Delay(10);
		ret = Fingerprint_GetTZ(1);	// ��ȡ����
		*_result = ret;
		printf("get image OK. get feature %d\r\n", ret);
//		IWDG_ReloadCounter();
		if(ret == RET_OK)
		{
			HAL_Delay(10);
			ret = Fingerprint_Search(&page, &score);	// ����ָ�ƿ�
			*_result = ret;
			if(ret == RET_OK)
			{
				printf(">>ָ����֤�ɹ����÷֣�%d��λ�ã�%d\r\n", score, page);
				return 0;
			}
			else
			{
				printf("search error(%d)\r\n", ret);
				return -2;	// ����ָ�ƿ�ʧ��
			}
		}
		else
			return -1;// ��ȡ����ʧ��
	}
	else
	{
		return -3;// ��ָ��
	}
}

/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_CheckFingerLoop
*	����˵��: ��ָ֤�ƣ�ѭ���ȴ���ָ״̬���ȴ���ָ�ĳ�ʱʱ��Լ10s
*	��    ��: uint8_t *_result������ָ��ƥ�����Ϣ
*			  uint16_t *_page, uint16_t *_score
*	�� �� ֵ: 0���ɹ���-1����ȡ����ʧ�ܣ�-2������ָ�ƿ�ʧ�ܣ�-3����ȡͼ��ʧ�ܣ�-6����ָ�Ƴ�ʱ
*********************************************************************************************************
*/
int8_t Fingerprint_CheckFingerLoop(int8_t *_result, uint16_t *_page, uint16_t *_score)
{
	int8_t ret = 0;
	uint16_t page = 0, score = 0;
	uint32_t tim = LocalTime;

	*_result = -1;
	*_page = 0;
	*_score = 0;

	//---- ��ȡͼ��----------------------------------------------------
	printf(">>�ȴ�����ָ��...\r\n");
	while(1)
	{
//		IWDG_ReloadCounter();
		ret = Fingerprint_GetImg();	// ��ȡͼ��

		*_result = ret;
		if(ret == RET_OK)
		{
			printf("OK\r\n");
			break;
		}
		else if(ret == RET_NOFINGER)	// û����ָ
		{
			if(LocalTime > tim + 100000)	// 10s��ʱ
			{
				printf("��ʱ��\r\n");
				return -6;	// û����ָ
			}
		}
		else
		{
			printf("����%d\r\n", ret);
			return -3;
		}
		HAL_Delay(100);
	}
	
	//---- ������ȡ-----------------------------------------------------
	printf(">>������ȡ...\r\n");
	HAL_Delay(10);
	ret = Fingerprint_GetTZ(1);	// ��ȡ����
	*_result = ret;
//	IWDG_ReloadCounter();
	if(ret != RET_OK)
	{
		printf("����%d\r\n", ret);
		return -1;// ��ȡ����ʧ��
	}
	else
		printf("OK\r\n");

	
	//---- ����ָ��----------------------------------------------------
	ret = Fingerprint_Search(&page, &score);	// ����ָ�ƿ�
	*_result = ret;
	if(ret == RET_OK)
	{
		*_page = page;
		*_score = score;

		printf(">>ָ����֤�ɹ����÷֣�%d��λ�ã�%d\r\n", score, page);
		return 0;
	}
	else
	{
		printf("search error(%d)\r\n", ret);
		return -2;	// ����ָ�ƿ�ʧ��
	}
}


/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_Register_At
*	����˵��: ��ָ��λ��¼��ָ�ƣ��ȴ���ָ�ĳ�ʱʱ��Լ10s
*	��    ��: 
*	�� �� ֵ: 0��¼��ɹ���-1����ȡ����ʧ�ܣ�-3����ȡͼ��ʧ�ܣ�-4���ϲ�ģ��ʧ�ܣ�-5���洢ʧ�ܣ�-6����ָ�Ƴ�ʱ
*********************************************************************************************************
*/
int8_t Fingerprint_Register_At(uint8_t addr)
{
	int8_t ret = 0;	

	if(FP_Reg_Times < Max_Reg_Time) // ע�����
	{
		//---- ��ȡͼ��----------------------------------------------------

		if(Wait_For_Finger_Flag)
		{
			Timeout++;
			
			printf(">>�ȴ�����ָ��...\r\n");
			lv_label_set_text(guider_ui.screen_17_label_1, "Waiting for the finger to be pressed...");
      ret = Fingerprint_GetRegImg(); // ��ȡע����ͼ��

			if(ret == RET_OK)
			{
				Timeout = 0;
				//---- ������ȡ-----------------------------------------------------
				printf(">>������ȡ...\r\n");
				HAL_Delay(10);
				ret = Fingerprint_GetTZ(FP_Reg_Times + 1); // ��ȡ����
				if(ret != RET_OK)
				{
					printf("��ȡ����ʧ�ܣ�����%d\r\n", ret);
					return -1; // ��ȡ����ʧ��
				}
				else
				{
					printf("OK\r\n");
					
					Wait_For_Finger_Flag = false;
					Wait_For_Lift_Flag = true;
				}
			}
			else if(ret == RET_NOFINGER) // û����ָ
			{
				if(Timeout > 50) // 10s��ʱ
				{
					Timeout = 0;
					printf("��ʱ��\r\n");
          lv_label_set_text(guider_ui.screen_17_label_1, "No finger!\nTime out...");

					FP_Reg_Times = 0;
					Wait_For_Finger_Flag = false;
					Wait_For_Lift_Flag = false;
					Fingerprint_Register_Flag = false;

					return -6; // û����ָ
				}
			}
			else
			{
				printf("����%d\r\n", ret);
        lv_label_set_text(guider_ui.screen_17_label_1, "Error...");

				FP_Reg_Times = 0;
				Wait_For_Finger_Flag = false;
				Wait_For_Lift_Flag = false;
				Fingerprint_Register_Flag = false;

				return -3;
			}
			HAL_Delay(100);
		}


		//---- ��ȡͼ��----------------------------------------------------
		if(Wait_For_Lift_Flag)
		{
			printf(">>�ȴ�̧����ָ...\r\n");
			lv_label_set_text(guider_ui.screen_17_label_1, "OK!\nlift the finger.");
      HAL_Delay(100);
			
			ret = Fingerprint_GetImg(); // ��ȡͼ��
			if(ret == RET_NOFINGER) // û����ָ
			{
				printf("��ָ���뿪��OK\r\n");
				
				Wait_For_Finger_Flag = true;
				Wait_For_Lift_Flag = false;
				FP_Reg_Times ++; // ���һ��ʶ�𣬴�����1
			}
			else
			{
				printf("��ָδ�뿪��״̬��%d\r\n", ret);
				return -3;
			}
		}
	}
	
	
	//---- �ϲ�ģ��-----------------------------------------------------
	if(FP_Reg_Times == Max_Reg_Time) // ע������ﵽ
	{
		FP_Reg_Times = 0;
		Wait_For_Finger_Flag = false;
		Wait_For_Lift_Flag = false;
		Fingerprint_Register_Flag = false;

		ret = Fingerprint_RegModel(); // �ϲ�ģ��
		printf("RegModel %02X\r\n", ret);
		if(ret != RET_OK)
			return -4;// �ϲ�ģ��ʧ��
		
		//---- ����ָ��-----------------------------------------------------
		printf(">>����...\r\n");
		HAL_Delay(10);
		ret = Fingerprint_StoreModel(addr); // �洢
	//	printf("Store Model id:%d ? %02X\r\n", 1, ret);
		if(ret == RET_OK)
		{
			printf("ע��ɹ���FingerID=%d\r\n", addr);
			lv_label_set_text(guider_ui.screen_17_label_1, "Registration success!");
			
			FP_HAVE_Flag[addr] = true;
			return 0; // �ɹ�
		}
		else
			return -5;
	}
	
	return -6;
}


/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_Register
*	����˵��: ¼��ָ�ƣ��ȴ���ָ�ĳ�ʱʱ��Լ10s
*	��    ��: uint8_t *_result������ָ��ƥ�����Ϣ
*	�� �� ֵ: 0��¼��ɹ���-1����ȡ����ʧ�ܣ�-3����ȡͼ��ʧ�ܣ�-4���ϲ�ģ��ʧ�ܣ�-5���洢ʧ�ܣ�-6����ָ�Ƴ�ʱ
*			  -7��ָ�ƿ�����
*********************************************************************************************************
*/
int8_t Fingerprint_Register(int8_t *_result)
{
	int8_t ret = 0, i = 0;	
	uint32_t tim = LocalTime;
	
	// ��ÿ��е�ģ�壬����һ�δ洢λ�ã�pageID
	FingerprintPara.ValidPageId = Fingerprint_GetValidTemplate();
	if(FingerprintPara.ValidPageId < 0)
	{
		printf(">>ָ�ƿ���������ɾ��ָ�ƺ���¼��ָ�ơ�\r\n");
		return -7;
	}
	else
	{
		printf(">>����λ��Ϊ��%d\r\n", FingerprintPara.ValidPageId);
	}
	
	for(i = 0; i < FingerprintPara.RegisterTimes; i++) // ע�����
	{
		tim = LocalTime;
		//---- ��ȡͼ��----------------------------------------------------
		printf(">>�ȴ�����ָ��...\r\n");
		while(1)
		{
//			IWDG_ReloadCounter();
			ret = Fingerprint_GetRegImg();	// ��ȡע����ͼ��

			*_result = ret;
			if(ret == RET_OK)
			{
				printf("OK\r\n");
				break;
			}
			else if(ret == RET_NOFINGER)	// û����ָ
			{
				if(LocalTime > tim + 100000)	// 10s��ʱ
				{
					printf("��ʱ��\r\n");
					return -6;	// û����ָ
				}
			}
			else
			{
				printf("����%d\r\n", ret);
				return -3;
			}
			HAL_Delay(100);
		}
		
		//---- ������ȡ-----------------------------------------------------
		printf(">>������ȡ...\r\n");
		HAL_Delay(10);
		ret = Fingerprint_GetTZ(i+1);	// ��ȡ����
		*_result = ret;
//		IWDG_ReloadCounter();
		if(ret != RET_OK)
		{
			printf("����%d\r\n", ret);
			return -1;// ��ȡ����ʧ��
		}
		else
			printf("OK\r\n");
		
		
		//---- ��ȡͼ��----------------------------------------------------
		printf(">>�ȴ�̧����ָ...\r\n");
		tim = LocalTime;
		while(1)
		{
//			IWDG_ReloadCounter();
			HAL_Delay(100);
			ret = Fingerprint_GetImg();	// ��ȡͼ��
			*_result = ret;
			if(ret == RET_OK)
				continue;
			else if(ret == RET_NOFINGER)	// û����ָ
			{
				printf("OK\r\n");
				break;
			}
			else
			{
				printf("����%d\r\n", ret);
				return -3;
			}
		}
		
		//---- ����ָ��----------------------------------------------------

	}
	
	
	//---- �ϲ�ģ��-----------------------------------------------------
	HAL_Delay(10);
	ret = Fingerprint_RegModel();// �ϲ�ģ��
	*_result = ret;
	printf("RegModel %02X\r\n", ret);
	if(ret != RET_OK)
		return -4;// �ϲ�ģ��ʧ��
	
	//---- ����ָ��-----------------------------------------------------
	printf(">>����...\r\n");
	HAL_Delay(10);
	ret = Fingerprint_StoreModel(FingerprintPara.ValidPageId);// �洢
	*_result = ret;
//	printf("Store Model id:%d ? %02X\r\n", 1, ret);
	if(ret == RET_OK)
	{
		printf("OK\r\nFingerID=%d\r\n", FingerprintPara.ValidPageId);
		FingerprintPara.TemplateNum++;// ָ�Ƹ�������
		return 0;	// �ɹ�
	}
	else
		return -5;

}

/*
*********************************************************************************************************
*	�� �� ��: Fingerprint_DeleteOne
*	����˵��: ɾ��һ��ָ��
*	��    ��: uint16_t _id��ָ��id
*	�� �� ֵ: 0���ɹ�
*********************************************************************************************************
*/
int8_t Fingerprint_DeleteOne(uint16_t _id)
{
	int8_t ret = 0;
	
	ret = Fingerprint_Delete(_id, 1);

	return ret;
}

/*
 *********************************************************************************************************
 *	�� �� ��: Check_Fingerprint
 *	����˵��: ÿ ms���һ��ָ��
 *	��    ��: ��
 *	�� �� ֵ: 0��δ������1��ָ��ƥ�䣬-1����ȡ����ʧ�ܣ�-2��ָ����֤ʧ��
 *********************************************************************************************************
 */
int8_t Check_Fingerprint(void)
{
    int8_t fgresult = 0, ret = 0;

    ret = Fingerprint_CheckFinger(&fgresult);
    if (ret == 0)	// ��ѯָ�ƣ��ɹ�
    {
        printf("Fingerprint OK\r\n");

        // ����
        HWPWR(1);
        HAL_Delay(500);
        HWPWR(0);

        return 1;
    }
    else if (ret == -1)	// ��ȡ����ʧ��
    {
        printf("Fingerprint error: %d\r\n", ret);
        return ret;
    }
    else if (ret == -2)	// ָ����֤ʧ��
    {
        printf(">>ָ����֤ʧ��(%d)\r\n", ret);
        return ret;
    }

    return 0;
}
