/*
*********************************************************************************************************
*
*	模块名称 : 指纹识别模组 YX-F112S11
*	文件名称 : yxf112s11.c
*	版    本 : V1.0
*	说    明 : 使用串口通信
*			  	格式：头(2字节)，地址(4字节)，包类型PID(1字节)，包长度(2字节)，内容（N-2字节），校验和(2字节)
*				大端数据格式
*	修改记录 :
*		版本号  日期       	作者    说明
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

#define MAX_TIMEOUT  1000                                 // 单位：ms
#define MAXRXBUFFER  164
static uint8_t tempBuffer[MAXRXBUFFER];                   // 接收缓冲区
volatile uint8_t* FingerprintFlag = &Usart2RxFlag;        // 接收完成标志
volatile uint16_t* FingerprintLength = &Usart2RxLength;   // 接收长度
volatile uint8_t* FingerprintBuffer = Usart2RxBuffer;     // 接收缓冲区
uint8_t Timeout = 0;																			// 超时时间

Fingerprint_Parameter_TypeDef FingerprintPara;

/*
*********************************************************************************************************
*	函 数 名: Fingerprintf_Init
*	功能说明: 初始化变量
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void Fingerprintf_Init(void)
{
	int8_t res = -1;
	uint16_t tempu16 = 0;
	
	// 读取信息
	
	memset(&FingerprintPara, 0, sizeof(FingerprintPara));
	
	// 验证密码
	res = Fingerprint_VerifyPassword(0);
	if(res != RET_OK)
	{
		printf("Fingerpint verify password error(%d)!\r\n", res);
		FlagData.chkFingerprintDevice = false;
	}
	else
		FlagData.chkFingerprintDevice = true;
	
	HAL_Delay(10);
	
	// 读取参数表
	res = Fingerprint_ReadInfoPage();
	if(res == RET_OK)
	{
		printf("指纹注册次数：%d，指纹库大小：%d，模板大小：%d\r\n",
		FingerprintPara.RegisterTimes, FingerprintPara.FingerprintSize, FingerprintPara.TemplateSize);
	}
	else
		printf("Fingerprint_ReadInfoPage error(%d)!\r\n", res);

	
	// 读取模板个数，确认录入指纹的个数
	res = Fingerprint_ReadTemplateNum(&FingerprintPara.TemplateNum);
	if(res == RET_OK)
	{
		printf("指纹个数：%d\r\n", FingerprintPara.TemplateNum);
	}
	else
		printf("Fingerprint get template error!\r\n");
	
	// 读取索引表
	res = Fingerprint_ReadConList(FingerprintPara.ConList);
	if(res == RET_OK)
	{
		printf("Fingerprint conlist: \r\n");
		for(tempu16 = 0; tempu16 < 32; tempu16++)
		{
			printf("%02X ", FingerprintPara.ConList[tempu16]);
		}
		printf("\r\n");
    
    // 前9位指纹分布情况
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
  
		
		// 确认下次注册的位置
		FingerprintPara.ValidPageId = Fingerprint_GetValidTemplate();
		if(FingerprintPara.ValidPageId >= 0)
			printf("下一个指纹ID：%d\r\n", FingerprintPara.ValidPageId);
		else
			printf("无空闲指纹库！\r\n");
	}
	else
		printf("Fingerprint get conlist error!\r\n");
}

/*
*********************************************************************************************************
*	函 数 名: Fingerprint_GetValidTemplate
*	功能说明: 获得空闲的模板，即下一次存储位置，pageID
*	形    参: 无
*	返 回 值: -1：无空闲的模板，其它：成功，返回pageID
*********************************************************************************************************
*/
int16_t Fingerprint_GetValidTemplate(void)
{
	uint16_t i = 0, tempu16 = 0;
	
	for(tempu16 = 0; tempu16 < 32; tempu16++)
	{
		if(FingerprintPara.ConList[tempu16] != 0xFF)// 有空闲的索引
		{
			for(i = 0; i < 8; i++) // 从低位开始
			{
				if((FingerprintPara.ConList[tempu16] & (1 << i)) == 0)// 空闲位
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
*	函 数 名: SendCmdAndWaitResponse
*	功能说明: 发送指令并等待应答
*	形    参:
*	返 回 值: -1：无应答，0：成功，-2：校验错误，-3：不是应答，其它@Fingerprint_Result_TypeDef
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
	
	if(*FingerprintFlag)	// 接收到应答
	{
		HAL_Delay(100);	// 等待接收数据包
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
				(sum & 0xFF) == tempBuffer[10+i] )// 校验正确
			{
				if( ((FingerprintCmdFormat_TypeDef*)tempBuffer)->pid == PID_RESPONSE)	// 应答
				{
					ret = tempBuffer[9];
				}
				else if( ((FingerprintCmdFormat_TypeDef*)tempBuffer)->pid == PID_LASTDATA)	// 最后数据
				{
					ret = 0;
				}
				else
					ret = -3;	// 不是应答
			}
			else
			{
				ret = -2;	// 校验错误
			}
		}
		*FingerprintLength = 0;
		*FingerprintFlag = 0;
//		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, Usart2RxBuffer, MAX_USART_SIZE);   // 接收完毕后重启
//		__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);                        // 手动关闭DMA_IT_HT中断
	}
	else
	{
		printf("NO response!\r\n");
		ret = -1;	// 无应答
	}
	
	return ret;	
}

/*
*********************************************************************************************************
*	函 数 名: Fingerprint_GetImg
*	功能说明: 获取指纹图像
*	形    参: 无
*	返 回 值: -1：无应答，0：成功
*********************************************************************************************************
*/
int8_t Fingerprint_GetImg(void)
{
	uint8_t data = CMD_GETIMG;
	int8_t ret = 0;
	// 发送   EF 01 FF FF FF FF 01 00 03 01 00 05
	// 无指纹 EF 01 FF FF FF FF 07 00 03 02 00 0C
	// 检测到 EF 01 FF FF FF FF 07 00 03 00 00 0A
	ret = SendCmdAndWaitResponse(&data, 1);

	return ret;
}
/*
*********************************************************************************************************
*	函 数 名: Fingerprint_GetRegImg
*	功能说明: 获取注册用指纹图像
*	形    参: 无
*	返 回 值: -1：无应答，0：成功
*********************************************************************************************************
*/
int8_t Fingerprint_GetRegImg(void)
{
	uint8_t data = CMD_GETREGIMG;// = 0x29,   // 注册用获取图像
	int8_t ret = 0;
	// 发送   EF 01 FF FF FF FF 01 00 03 29 00 2D
	// 无指纹 EF 01 FF FF FF FF 07 00 03 02 00 0C
	// 检测到 EF 01 FF FF FF FF 07 00 03 00 00 0A
	ret = SendCmdAndWaitResponse(&data, 1);

	return ret;
}

int8_t Fingerprint_Match(void)
{
	uint8_t data = CMD_MATCH;
	int8_t ret = 0;

	// 发送  EF 01 FF FF FF FF 01 00 03 03 00 07
	//       EF 01 FF FF FF FF 07 00 05 08 00 00 00 14 
	ret = SendCmdAndWaitResponse(&data, 1);

	return ret;		
}

/*
*********************************************************************************************************
*	函 数 名: Fingerprint_GetTZ
*	功能说明: 特征提取
*	形    参: uint8_t _bufferid：bufferID，从1开始
*	返 回 值: -1：无应答，0：成功
*********************************************************************************************************
*/
int8_t Fingerprint_GetTZ(uint8_t _bufferid)
{
	uint8_t data[2] = {CMD_IMG2TZ, 1};
	int8_t ret = 0;

	// 发送   EF 01 FF FF FF FF 01 00 04 02 0X xx xx
	// 成功   EF 01 FF FF FF FF 07 00 03 00 00 0A
	if(_bufferid != 0)
		data[1] = _bufferid;
	ret = SendCmdAndWaitResponse(data, 2);

	return ret;		
}

/*
*********************************************************************************************************
*	函 数 名: Fingerprint_Search
*	功能说明: 搜索指纹
*	形    参: uint16_t _page：搜索到的页码, uint16_t _score：得分
*	返 回 值: -1：无应答，0：成功
*********************************************************************************************************
*/
int8_t Fingerprint_Search(uint16_t *_page, uint16_t *_score)
{
	uint8_t data[6] = {CMD_SEARCH, 1, 0,0, 0x01,0x2C};// 搜索命令，特征buffer序号（1或2），搜索模板起始编号（2字节），搜索的模板数量（2字节）
	int8_t ret = 0;
	uint16_t tempu16 = 0;

	// 发送   EF 01 FF FF FF FF 01 00 08  04  01  00 00  01 2C  00 3B
	// 应答   EF 01 FF FF FF FF 07 00 07  09  00 00  00 00  00 17 // 没有找到匹配的指纹
	// 应答   EF 01 FF FF FF FF 07 00 07  00  00 01  03 1D  00 2F // 找到指纹，模板的编号=1，score=0x031D

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
*	函 数 名: Fingerprint_RegModel
*	功能说明: 合并特征
*	形    参: 无
*	返 回 值: -1：无应答，0：成功
*********************************************************************************************************
*/
int8_t Fingerprint_RegModel(void)
{
	uint8_t data = CMD_REGMODEL;// = 5, //将5个特征模板合并成1个模板
	int8_t ret = 0;

	// 发送  EF 01 ff ff ff ff 01 00 03 05 00 09 	............合并模板
	// 应答  01 ff ff ff ff 07 00 03 00 00 0a 	............成功

	ret = SendCmdAndWaitResponse(&data, 1);

	return ret;	
}

/*
*********************************************************************************************************
*	函 数 名: Fingerprint_StoreModel
*	功能说明: 储存模板
*	形    参: uint16_t _tempid：存储位置
*	返 回 值:
*********************************************************************************************************
*/
int8_t Fingerprint_StoreModel(uint16_t _tempid)
{
	uint8_t data[4] = {CMD_STOREMODEL, 1, 0, 0};// 保存指纹模板到指纹库，bufferID=1, TempID为存到数据库中的序号
	int8_t ret = 0;
	data[2] = _tempid>>8;
	data[3] = _tempid& 0xFF;
	// 发送  EF 01 ff ff ff ff 01 00 06  06  01  00 02  00 10 	...............保存指纹buffer1，到序号02
	// 应答  EF 01 ff ff ff ff 07 00 03  00  00 0a 	............成功

	ret = SendCmdAndWaitResponse(data, 4);

	return ret;		
}

/*
*********************************************************************************************************
*	函 数 名: Fingerprint_Delete
*	功能说明: 删除指纹
*	形    参: uint16_t _id：指纹id
*			  uint16_t _count：个数
*	返 回 值: 0：成功，
*********************************************************************************************************
*/
int8_t Fingerprint_Delete(uint16_t _id, uint16_t _count)
{
	uint8_t data[5] = {CMD_DELETECHAR, 0,0, 0,1};// = 0x0C,	// 从数据库中删除模板
	int8_t ret = 0;
	// 发送  EF 01 FF FF FF FF 01 00 07  0C  00 00  00 01  00 15  pageID=0, 1个
	// 成功  EF 01 FF FF FF FF 07 00 03  00  00 0A
	data[1] = _id >> 8;	// 起始位置
	data[2] = _id & 0xFF;
	data[3] = _count >> 8;
	data[4] = _count & 0xFF;
	
	ret = SendCmdAndWaitResponse(data, 5);

	return ret;
}
/*
*********************************************************************************************************
*	函 数 名: Fingerprint_DeleteAll
*	功能说明: 删除所有指纹
*	形    参: 无
*	返 回 值: 0：成功
*********************************************************************************************************
*/
int8_t Fingerprint_DeleteAll(void)
{
	uint8_t data = CMD_EMPTY;//= 0x0D,		// 清空数据库中所有的指纹模板
	int8_t ret = 0;

	ret = SendCmdAndWaitResponse(&data, 1);

	return ret;
}

/*
*********************************************************************************************************
*	函 数 名: Fingerprint_VerifyPassword
*	功能说明: 验证口令，默认密码0x00000000
*	形    参: uint32_t _pw
*	返 回 值:
*********************************************************************************************************
*/
int8_t Fingerprint_VerifyPassword(uint32_t _pw)
{
	uint8_t data[5] = {CMD_VERIFY_PASSWORD,0,0,0,0};// 0x13, // 验证口令，默认密码：0x00000000
	int8_t ret = 0;

//	发送 EF 01 FF FF FF FF 01 00 07 13 00 00 00 00 00 1B	PID:0x13 验证模组密码VfyPwd
//	应答 EF 01 FF FF FF FF 07 00 03 00 00 0A				OK	*_num = 0;
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
*	函 数 名: Fingerprint_ReadInfoPage
*	功能说明: 读取infomation page 所在的参数页
*	形    参: 无
*	返 回 值: 0:OK, -2：校验错误，-3：不是数据包，-4：没有数据包的头，其它@Fingerprint_Result_TypeDef
*********************************************************************************************************
*/
int8_t Fingerprint_ReadInfoPage(void)
{
	uint8_t data = CMD_READINFPAGE;// 0x16,  // 读取FLASH information page 所在的参数页
	int8_t ret = 0;
	uint8_t *pdata = NULL;
	uint16_t len = 0, sum = 0, i = 0;
	const uint16_t datapos = 9;
	
	// 发送  EF 01 FF FF FF FF 01 00 03 16 00 1A			PID:0x16 读参数页PS_ReadINFpage。应答后面紧接着是数据包
	// 应答  EF 01 FF FF FF FF 07 00 03 00 00 0A EF 01 FF FF FF FF 08  00 82  00 04  08 00  00 78 00 03  FF FF FF FF ....
	ret = SendCmdAndWaitResponse(&data, 1);
	if(ret == RET_OK)
	{
		// 应答后面是数据包，验证
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
				(sum & 0xFF) == pdata[10+i] )// 校验正确
			{
				if( ((FingerprintCmdFormat_TypeDef*)pdata)->pid == PID_LASTDATA)	// 最后一个数据包
				{
					ret = RET_OK;
					pdata += datapos;
					FingerprintPara.RegisterTimes = *pdata;	// 注册次数
					pdata++;
					FingerprintPara.RegisterTimes <<= 8;
					FingerprintPara.RegisterTimes += *pdata;
					pdata++;
					FingerprintPara.TemplateSize = *pdata;	// 模板大小
					pdata++;
					FingerprintPara.TemplateSize <<= 8;
					FingerprintPara.TemplateSize += *pdata;
					pdata++;
					FingerprintPara.FingerprintSize = *pdata;	// 指纹库大小
					pdata++;
					FingerprintPara.FingerprintSize <<= 8;
					FingerprintPara.FingerprintSize += *pdata;
				}
				else
					ret = -3;	// 不是数据
			}
			else
			{
				ret = -2;	// 校验错误
			}
		}
		else
		{
			ret = -4;// 没有数据包的头
		}
	}
	return ret;		
}

/*
*********************************************************************************************************
*	函 数 名: Fingerprint_ReadTemplateNum
*	功能说明: 读取模板数量
*	形    参: uint16_t *_num：template number
*	返 回 值:
*********************************************************************************************************
*/
int8_t Fingerprint_ReadTemplateNum(uint16_t *_num)	// 读取模板数量
{
	uint8_t data = CMD_TEMPLATENUM;// = 0x1D, // 读取数据库中模板数量
	int8_t ret = 0;
	uint16_t num = 0;

	// 发送  EF 01 FF FF FF FF 01 00 03  1D  00 21			PID:0x1D 读取模组模板数量 TemplateNum
	// 应答  EF 01 FF FF FF FF 07 00 05  00  00 02  00 0E
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
*	函 数 名: Fingerprint_ReadConList
*	功能说明: 读取数据库中有效模板标记数组，共64字节512个模板，按位使用，每个字节的低bit为低template id
*			  序号300~511的模板不存在，因此读回的标记均为0
*	形    参: uint8_t *_list：64字节的数组
*	返 回 值:
*********************************************************************************************************
*/
int8_t Fingerprint_ReadConList(uint8_t *_list)
{
	uint8_t data[2] = {CMD_READCONLIST, 0};// 0x1F,	// 读取数据库中模板标记数组。索引表页码0，对应模板0~256的索引
	int8_t ret = 0;

	/*
		EF 01 FF FF FF FF 01 00 04  1F  00  00 24			PID:0x1F 从数据库中读取有效的模板标记数组index0 ReadConList
		EF 01 FF FF FF FF 07 00 23 00 03 00 00 00 00 00
		 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
		 00 00 00 00 00 00 00 00 00 00 00 2D

		EF 01 FF FF FF FF 01 00 04  1F 01  00 25			PID:0x1F 从数据库中读取有效的模板标记数组index1 ReadConList
		EF 01 FF FF FF FF 07 00 23 00 00 00 00 00 00 00
		 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
		 00 00 00 00 00 00 00 00 00 00 00 2A
	*/

	ret = SendCmdAndWaitResponse(data, 2);
	if(ret == RET_OK)
	{
		memcpy(_list, &tempBuffer[10], 32);
		#if 0	// 不支持索引表页码1
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
*	函 数 名: Fingerprint_CheckFinger
*	功能说明: 验证指纹，调用一次检查一次，需要提前放置手指
*	形    参: uint8_t *_result：返回指纹匹配的信息
*	返 回 值: -3：无指纹，0：指纹匹配，-1：提取特征失败，-2：搜索指纹库失败
*********************************************************************************************************
*/
int8_t Fingerprint_CheckFinger(int8_t *_result)
{
	int8_t ret = 0;
	uint16_t page = 0, score = 0;
	
	*_result = -1;
	ret = Fingerprint_GetImg();	// 获取图像
	*_result = ret;
	if(ret == RET_OK)
	{
		HAL_Delay(10);
		ret = Fingerprint_GetTZ(1);	// 提取特征
		*_result = ret;
		printf("get image OK. get feature %d\r\n", ret);
//		IWDG_ReloadCounter();
		if(ret == RET_OK)
		{
			HAL_Delay(10);
			ret = Fingerprint_Search(&page, &score);	// 搜索指纹库
			*_result = ret;
			if(ret == RET_OK)
			{
				printf(">>指纹验证成功！得分：%d，位置：%d\r\n", score, page);
				return 0;
			}
			else
			{
				printf("search error(%d)\r\n", ret);
				return -2;	// 搜索指纹库失败
			}
		}
		else
			return -1;// 提取特征失败
	}
	else
	{
		return -3;// 无指纹
	}
}

/*
*********************************************************************************************************
*	函 数 名: Fingerprint_CheckFingerLoop
*	功能说明: 验证指纹，循环等待手指状态，等待手指的超时时间约10s
*	形    参: uint8_t *_result：返回指纹匹配的信息
*			  uint16_t *_page, uint16_t *_score
*	返 回 值: 0：成功，-1：提取特征失败，-2：搜索指纹库失败，-3：获取图像失败，-6：无指纹超时
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

	//---- 获取图像----------------------------------------------------
	printf(">>等待按下指纹...\r\n");
	while(1)
	{
//		IWDG_ReloadCounter();
		ret = Fingerprint_GetImg();	// 获取图像

		*_result = ret;
		if(ret == RET_OK)
		{
			printf("OK\r\n");
			break;
		}
		else if(ret == RET_NOFINGER)	// 没有手指
		{
			if(LocalTime > tim + 100000)	// 10s超时
			{
				printf("超时！\r\n");
				return -6;	// 没有手指
			}
		}
		else
		{
			printf("错误%d\r\n", ret);
			return -3;
		}
		HAL_Delay(100);
	}
	
	//---- 特征提取-----------------------------------------------------
	printf(">>特征提取...\r\n");
	HAL_Delay(10);
	ret = Fingerprint_GetTZ(1);	// 提取特征
	*_result = ret;
//	IWDG_ReloadCounter();
	if(ret != RET_OK)
	{
		printf("错误%d\r\n", ret);
		return -1;// 提取特征失败
	}
	else
		printf("OK\r\n");

	
	//---- 搜索指纹----------------------------------------------------
	ret = Fingerprint_Search(&page, &score);	// 搜索指纹库
	*_result = ret;
	if(ret == RET_OK)
	{
		*_page = page;
		*_score = score;

		printf(">>指纹验证成功！得分：%d，位置：%d\r\n", score, page);
		return 0;
	}
	else
	{
		printf("search error(%d)\r\n", ret);
		return -2;	// 搜索指纹库失败
	}
}


/*
*********************************************************************************************************
*	函 数 名: Fingerprint_Register_At
*	功能说明: 在指定位置录入指纹，等待手指的超时时间约10s
*	形    参: 
*	返 回 值: 0：录入成功，-1：提取特征失败，-3：获取图像失败，-4：合并模板失败，-5：存储失败，-6：无指纹超时
*********************************************************************************************************
*/
int8_t Fingerprint_Register_At(uint8_t addr)
{
	int8_t ret = 0;	

	if(FP_Reg_Times < Max_Reg_Time) // 注册次数
	{
		//---- 获取图像----------------------------------------------------

		if(Wait_For_Finger_Flag)
		{
			Timeout++;
			
			printf(">>等待按下指纹...\r\n");
			lv_label_set_text(guider_ui.screen_17_label_1, "Waiting for the finger to be pressed...");
      ret = Fingerprint_GetRegImg(); // 获取注册用图像

			if(ret == RET_OK)
			{
				Timeout = 0;
				//---- 特征提取-----------------------------------------------------
				printf(">>特征提取...\r\n");
				HAL_Delay(10);
				ret = Fingerprint_GetTZ(FP_Reg_Times + 1); // 提取特征
				if(ret != RET_OK)
				{
					printf("提取特征失败，错误：%d\r\n", ret);
					return -1; // 提取特征失败
				}
				else
				{
					printf("OK\r\n");
					
					Wait_For_Finger_Flag = false;
					Wait_For_Lift_Flag = true;
				}
			}
			else if(ret == RET_NOFINGER) // 没有手指
			{
				if(Timeout > 50) // 10s超时
				{
					Timeout = 0;
					printf("超时！\r\n");
          lv_label_set_text(guider_ui.screen_17_label_1, "No finger!\nTime out...");

					FP_Reg_Times = 0;
					Wait_For_Finger_Flag = false;
					Wait_For_Lift_Flag = false;
					Fingerprint_Register_Flag = false;

					return -6; // 没有手指
				}
			}
			else
			{
				printf("错误：%d\r\n", ret);
        lv_label_set_text(guider_ui.screen_17_label_1, "Error...");

				FP_Reg_Times = 0;
				Wait_For_Finger_Flag = false;
				Wait_For_Lift_Flag = false;
				Fingerprint_Register_Flag = false;

				return -3;
			}
			HAL_Delay(100);
		}


		//---- 获取图像----------------------------------------------------
		if(Wait_For_Lift_Flag)
		{
			printf(">>等待抬起手指...\r\n");
			lv_label_set_text(guider_ui.screen_17_label_1, "OK!\nlift the finger.");
      HAL_Delay(100);
			
			ret = Fingerprint_GetImg(); // 获取图像
			if(ret == RET_NOFINGER) // 没有手指
			{
				printf("手指已离开，OK\r\n");
				
				Wait_For_Finger_Flag = true;
				Wait_For_Lift_Flag = false;
				FP_Reg_Times ++; // 完成一次识别，次数加1
			}
			else
			{
				printf("手指未离开，状态：%d\r\n", ret);
				return -3;
			}
		}
	}
	
	
	//---- 合并模板-----------------------------------------------------
	if(FP_Reg_Times == Max_Reg_Time) // 注册次数达到
	{
		FP_Reg_Times = 0;
		Wait_For_Finger_Flag = false;
		Wait_For_Lift_Flag = false;
		Fingerprint_Register_Flag = false;

		ret = Fingerprint_RegModel(); // 合并模板
		printf("RegModel %02X\r\n", ret);
		if(ret != RET_OK)
			return -4;// 合并模板失败
		
		//---- 保存指纹-----------------------------------------------------
		printf(">>保存...\r\n");
		HAL_Delay(10);
		ret = Fingerprint_StoreModel(addr); // 存储
	//	printf("Store Model id:%d ? %02X\r\n", 1, ret);
		if(ret == RET_OK)
		{
			printf("注册成功，FingerID=%d\r\n", addr);
			lv_label_set_text(guider_ui.screen_17_label_1, "Registration success!");
			
			FP_HAVE_Flag[addr] = true;
			return 0; // 成功
		}
		else
			return -5;
	}
	
	return -6;
}


/*
*********************************************************************************************************
*	函 数 名: Fingerprint_Register
*	功能说明: 录入指纹，等待手指的超时时间约10s
*	形    参: uint8_t *_result：返回指纹匹配的信息
*	返 回 值: 0：录入成功，-1：提取特征失败，-3：获取图像失败，-4：合并模板失败，-5：存储失败，-6：无指纹超时
*			  -7：指纹库已满
*********************************************************************************************************
*/
int8_t Fingerprint_Register(int8_t *_result)
{
	int8_t ret = 0, i = 0;	
	uint32_t tim = LocalTime;
	
	// 获得空闲的模板，即下一次存储位置，pageID
	FingerprintPara.ValidPageId = Fingerprint_GetValidTemplate();
	if(FingerprintPara.ValidPageId < 0)
	{
		printf(">>指纹库已满！清删除指纹后再录入指纹。\r\n");
		return -7;
	}
	else
	{
		printf(">>储存位置为：%d\r\n", FingerprintPara.ValidPageId);
	}
	
	for(i = 0; i < FingerprintPara.RegisterTimes; i++) // 注册次数
	{
		tim = LocalTime;
		//---- 获取图像----------------------------------------------------
		printf(">>等待按下指纹...\r\n");
		while(1)
		{
//			IWDG_ReloadCounter();
			ret = Fingerprint_GetRegImg();	// 获取注册用图像

			*_result = ret;
			if(ret == RET_OK)
			{
				printf("OK\r\n");
				break;
			}
			else if(ret == RET_NOFINGER)	// 没有手指
			{
				if(LocalTime > tim + 100000)	// 10s超时
				{
					printf("超时！\r\n");
					return -6;	// 没有手指
				}
			}
			else
			{
				printf("错误%d\r\n", ret);
				return -3;
			}
			HAL_Delay(100);
		}
		
		//---- 特征提取-----------------------------------------------------
		printf(">>特征提取...\r\n");
		HAL_Delay(10);
		ret = Fingerprint_GetTZ(i+1);	// 提取特征
		*_result = ret;
//		IWDG_ReloadCounter();
		if(ret != RET_OK)
		{
			printf("错误%d\r\n", ret);
			return -1;// 提取特征失败
		}
		else
			printf("OK\r\n");
		
		
		//---- 获取图像----------------------------------------------------
		printf(">>等待抬起手指...\r\n");
		tim = LocalTime;
		while(1)
		{
//			IWDG_ReloadCounter();
			HAL_Delay(100);
			ret = Fingerprint_GetImg();	// 获取图像
			*_result = ret;
			if(ret == RET_OK)
				continue;
			else if(ret == RET_NOFINGER)	// 没有手指
			{
				printf("OK\r\n");
				break;
			}
			else
			{
				printf("错误%d\r\n", ret);
				return -3;
			}
		}
		
		//---- 搜索指纹----------------------------------------------------

	}
	
	
	//---- 合并模板-----------------------------------------------------
	HAL_Delay(10);
	ret = Fingerprint_RegModel();// 合并模板
	*_result = ret;
	printf("RegModel %02X\r\n", ret);
	if(ret != RET_OK)
		return -4;// 合并模板失败
	
	//---- 保存指纹-----------------------------------------------------
	printf(">>保存...\r\n");
	HAL_Delay(10);
	ret = Fingerprint_StoreModel(FingerprintPara.ValidPageId);// 存储
	*_result = ret;
//	printf("Store Model id:%d ? %02X\r\n", 1, ret);
	if(ret == RET_OK)
	{
		printf("OK\r\nFingerID=%d\r\n", FingerprintPara.ValidPageId);
		FingerprintPara.TemplateNum++;// 指纹个数增加
		return 0;	// 成功
	}
	else
		return -5;

}

/*
*********************************************************************************************************
*	函 数 名: Fingerprint_DeleteOne
*	功能说明: 删除一个指纹
*	形    参: uint16_t _id：指纹id
*	返 回 值: 0：成功
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
 *	函 数 名: Check_Fingerprint
 *	功能说明: 每 ms检查一次指纹
 *	形    参: 无
 *	返 回 值: 0：未检索，1：指纹匹配，-1：提取特征失败，-2：指纹验证失败
 *********************************************************************************************************
 */
int8_t Check_Fingerprint(void)
{
    int8_t fgresult = 0, ret = 0;

    ret = Fingerprint_CheckFinger(&fgresult);
    if (ret == 0)	// 查询指纹，成功
    {
        printf("Fingerprint OK\r\n");

        // 开机
        HWPWR(1);
        HAL_Delay(500);
        HWPWR(0);

        return 1;
    }
    else if (ret == -1)	// 提取特征失败
    {
        printf("Fingerprint error: %d\r\n", ret);
        return ret;
    }
    else if (ret == -2)	// 指纹验证失败
    {
        printf(">>指纹验证失败(%d)\r\n", ret);
        return ret;
    }

    return 0;
}
