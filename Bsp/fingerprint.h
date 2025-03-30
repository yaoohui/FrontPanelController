/*
*********************************************************************************************************
*
*	模块名称 : 指纹识别模组 YX-F112S11
*	文件名称 : yxf112s11.h
*	版    本 : V1.0
*	说    明 : 使用串口通信
*			  
*	修改记录 :
*		版本号  日期       	作者    说明
*		V1.0	2020-10-03	JOY		
*
*********************************************************************************************************
*/
#ifndef __YXF112S11_H
#define __YXF112S11_H


#include "main.h"
#include <stdint.h>

#define FP_CMD_START	0xEF01
#define FP_CMD_ADDR		0xFFFFFFFF

// 通信格式，大端
typedef struct
{
	uint8_t start[2];
	uint8_t addr[4];
	uint8_t  pid;
	uint8_t length[2];		// 内容与校验和的长度
	uint8_t  *pPayload;
	uint8_t sum[2];			// 从PID开始校验和
	
}FingerprintCmdFormat_TypeDef;

// 包类型（PID）
typedef enum
{
	PID_CMD = 1,
	PID_DATA = 2,
	PID_RESPONSE = 7,
	PID_LASTDATA = 8,
	
}Fingerprint_PID_TypeDef;


// 指纹参数
typedef struct
{
	uint16_t RegisterTimes;			// 注册指纹需要的次数，默认为4
	uint16_t TemplateSize;			// 指纹模板大小，默认2048
	uint16_t FingerprintSize;		// 指纹库大小，默认120
	
	uint16_t TemplateNum;			// 模板数量，即已经存储的指纹个数
	uint8_t ConList[32];			// 读取的数据库中模板标记数组，按位使用，每个字节的低bit为低template id
	int16_t ValidPageId;			// 空闲的指纹位置，从0开始，<FingerprintSize。用于标记下一个存储位置，-1表示无空闲
	
}Fingerprint_Parameter_TypeDef;


// 命令码
typedef enum
{
	CMD_GETIMG = 1,			// 获取图像（包含手指检测）
	CMD_IMG2TZ = 2,			// 特征提取
	CMD_MATCH = 3,			// 匹配2个特征
	CMD_SEARCH = 4,			// 在数据库中搜索
	CMD_REGMODEL = 5,		// 将5个特征模板合并成1个模板
	CMD_STOREMODEL = 6,		// 将特征模板存入数据库
	CMD_DELETECHAR = 0x0C,	// 从数据库中删除模板
	CMD_EMPTY = 0x0D,		// 清空数据库中所有的指纹模板
	CMD_VERIFY_PASSWORD = 0x13, // 验证口令，默认密码：0x00000000
	CMD_READINFPAGE = 0x16,  // 读取FLASH information page 所在的参数页
	CMD_TEMPLATENUM = 0x1D, // 读取数据库中模板数量
	CMD_READCONLIST = 0x1F,	// 读取数据库中模板标记数组
	CMD_GETREGIMG = 0x29,   // 注册用获取图像
	
}Fingerprint_Command_TypeDef;

// 反馈码
typedef enum
{
	RET_OK = 0,				// 成功
	RET_INVALIDPACKET = 1,	// 无效数据包
	RET_NOFINGER = 2,		// 未检测到手指
	RET_STOREIMAGEFAIL = 3,	// 将图像存入ImageBuffer失败
	RET_TOOLOWQULITY = 6,	// 图像质量太差而无法提取特征
	RET_TOOFEWPOINT = 7,	// 特征点太少而无法提取特征
	RET_NOTMATCHED = 8,		// 指纹模板不匹配
	RET_NOTIDENTIFIED = 9,	// 没有找到匹配的指纹
	RET_MERGEFAIL = 0x0A,	// 合并特征失败
	RET_INVALIDTEMPID = 0x0B,	// 模板ID不合法
	RET_READTEMPFAIL = 0x0C,	// 从数据库中读出模板失败
	RET_DELETEFAIL = 0x10,		// 删除模板失败
	RET_PASSWORDERR = 0x13,		// 密码错误
	
}Fingerprint_Result_TypeDef;


extern Fingerprint_Parameter_TypeDef FingerprintPara;
extern bool FP_HAVE_Flag[9];



int16_t Fingerprint_GetValidTemplate(void);// 获得空闲的模板，即下一次存储位置，pageID
int8_t Fingerprint_VerifyPassword(uint32_t _pw);
int8_t Fingerprint_ReadInfoPage(void);	// 读取参数表
int8_t Fingerprint_ReadTemplateNum(uint16_t *_num);	// 读取模板数量
int8_t Fingerprint_ReadConList(uint8_t *_list);
int8_t Fingerprint_Search(uint16_t *_page, uint16_t *_score);
int8_t Fingerprint_Delete(uint16_t _id, uint16_t _count);


// 以下用于外部调用
void Fingerprintf_Init(void);

int8_t Fingerprint_CheckFinger(int8_t *_result);	// 验证指纹，调用一次检查一次，需要提前放置手指
int8_t Fingerprint_CheckFingerLoop(int8_t *_result, uint16_t *_page, uint16_t *_score); // 验证指纹，循环等待手指状态，等待手指的超时时间约10s
int8_t Fingerprint_Register(int8_t *_result);	// 录入指纹
int8_t Fingerprint_Register_At(uint8_t addr); // 在指定位置录入指纹
int8_t Fingerprint_DeleteOne(uint16_t _id);		// 删除一个指纹
int8_t Fingerprint_DeleteAll(void);				// 删除所有指纹

int8_t SendCmdAndWaitResponse(uint8_t *_cmdbuff, uint16_t _cmdlen);
int8_t Check_Fingerprint(void);

#endif

