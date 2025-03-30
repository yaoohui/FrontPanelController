/*
*********************************************************************************************************
*
*	ģ������ : ָ��ʶ��ģ�� YX-F112S11
*	�ļ����� : yxf112s11.h
*	��    �� : V1.0
*	˵    �� : ʹ�ô���ͨ��
*			  
*	�޸ļ�¼ :
*		�汾��  ����       	����    ˵��
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

// ͨ�Ÿ�ʽ�����
typedef struct
{
	uint8_t start[2];
	uint8_t addr[4];
	uint8_t  pid;
	uint8_t length[2];		// ������У��͵ĳ���
	uint8_t  *pPayload;
	uint8_t sum[2];			// ��PID��ʼУ���
	
}FingerprintCmdFormat_TypeDef;

// �����ͣ�PID��
typedef enum
{
	PID_CMD = 1,
	PID_DATA = 2,
	PID_RESPONSE = 7,
	PID_LASTDATA = 8,
	
}Fingerprint_PID_TypeDef;


// ָ�Ʋ���
typedef struct
{
	uint16_t RegisterTimes;			// ע��ָ����Ҫ�Ĵ�����Ĭ��Ϊ4
	uint16_t TemplateSize;			// ָ��ģ���С��Ĭ��2048
	uint16_t FingerprintSize;		// ָ�ƿ��С��Ĭ��120
	
	uint16_t TemplateNum;			// ģ�����������Ѿ��洢��ָ�Ƹ���
	uint8_t ConList[32];			// ��ȡ�����ݿ���ģ�������飬��λʹ�ã�ÿ���ֽڵĵ�bitΪ��template id
	int16_t ValidPageId;			// ���е�ָ��λ�ã���0��ʼ��<FingerprintSize�����ڱ����һ���洢λ�ã�-1��ʾ�޿���
	
}Fingerprint_Parameter_TypeDef;


// ������
typedef enum
{
	CMD_GETIMG = 1,			// ��ȡͼ�񣨰�����ָ��⣩
	CMD_IMG2TZ = 2,			// ������ȡ
	CMD_MATCH = 3,			// ƥ��2������
	CMD_SEARCH = 4,			// �����ݿ�������
	CMD_REGMODEL = 5,		// ��5������ģ��ϲ���1��ģ��
	CMD_STOREMODEL = 6,		// ������ģ��������ݿ�
	CMD_DELETECHAR = 0x0C,	// �����ݿ���ɾ��ģ��
	CMD_EMPTY = 0x0D,		// ������ݿ������е�ָ��ģ��
	CMD_VERIFY_PASSWORD = 0x13, // ��֤���Ĭ�����룺0x00000000
	CMD_READINFPAGE = 0x16,  // ��ȡFLASH information page ���ڵĲ���ҳ
	CMD_TEMPLATENUM = 0x1D, // ��ȡ���ݿ���ģ������
	CMD_READCONLIST = 0x1F,	// ��ȡ���ݿ���ģ��������
	CMD_GETREGIMG = 0x29,   // ע���û�ȡͼ��
	
}Fingerprint_Command_TypeDef;

// ������
typedef enum
{
	RET_OK = 0,				// �ɹ�
	RET_INVALIDPACKET = 1,	// ��Ч���ݰ�
	RET_NOFINGER = 2,		// δ��⵽��ָ
	RET_STOREIMAGEFAIL = 3,	// ��ͼ�����ImageBufferʧ��
	RET_TOOLOWQULITY = 6,	// ͼ������̫����޷���ȡ����
	RET_TOOFEWPOINT = 7,	// ������̫�ٶ��޷���ȡ����
	RET_NOTMATCHED = 8,		// ָ��ģ�岻ƥ��
	RET_NOTIDENTIFIED = 9,	// û���ҵ�ƥ���ָ��
	RET_MERGEFAIL = 0x0A,	// �ϲ�����ʧ��
	RET_INVALIDTEMPID = 0x0B,	// ģ��ID���Ϸ�
	RET_READTEMPFAIL = 0x0C,	// �����ݿ��ж���ģ��ʧ��
	RET_DELETEFAIL = 0x10,		// ɾ��ģ��ʧ��
	RET_PASSWORDERR = 0x13,		// �������
	
}Fingerprint_Result_TypeDef;


extern Fingerprint_Parameter_TypeDef FingerprintPara;
extern bool FP_HAVE_Flag[9];



int16_t Fingerprint_GetValidTemplate(void);// ��ÿ��е�ģ�壬����һ�δ洢λ�ã�pageID
int8_t Fingerprint_VerifyPassword(uint32_t _pw);
int8_t Fingerprint_ReadInfoPage(void);	// ��ȡ������
int8_t Fingerprint_ReadTemplateNum(uint16_t *_num);	// ��ȡģ������
int8_t Fingerprint_ReadConList(uint8_t *_list);
int8_t Fingerprint_Search(uint16_t *_page, uint16_t *_score);
int8_t Fingerprint_Delete(uint16_t _id, uint16_t _count);


// ���������ⲿ����
void Fingerprintf_Init(void);

int8_t Fingerprint_CheckFinger(int8_t *_result);	// ��ָ֤�ƣ�����һ�μ��һ�Σ���Ҫ��ǰ������ָ
int8_t Fingerprint_CheckFingerLoop(int8_t *_result, uint16_t *_page, uint16_t *_score); // ��ָ֤�ƣ�ѭ���ȴ���ָ״̬���ȴ���ָ�ĳ�ʱʱ��Լ10s
int8_t Fingerprint_Register(int8_t *_result);	// ¼��ָ��
int8_t Fingerprint_Register_At(uint8_t addr); // ��ָ��λ��¼��ָ��
int8_t Fingerprint_DeleteOne(uint16_t _id);		// ɾ��һ��ָ��
int8_t Fingerprint_DeleteAll(void);				// ɾ������ָ��

int8_t SendCmdAndWaitResponse(uint8_t *_cmdbuff, uint16_t _cmdlen);
int8_t Check_Fingerprint(void);

#endif

