/*
*********************************************************************************************************
*
*	ģ������ : ȫ�ֱ�������
*	�ļ����� : global.h
*   ��    �� : ҫ�Թ�����   https://shop108339233.taobao.com/
*	��    �� : V1.0
*	˵    �� :
*	�޸ļ�¼ :
*		�汾��	����       	����	˵��
*		V1.0	2017-02-17	JOY
*
*********************************************************************************************************
*/
#ifndef __GLOBAL_H
#define __GLOBAL_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>



//#define TRUE 1
//#define FALSE 0


// ���ò����е�Ĭ��ֵ
#define DEFAULT_BLFLAG				0x42544631	// bootloader�̶�ֵ "BTF1"����bootloader����һ��
#define DEFAULT_FLAG				0x46314338	// �����̶�ֵ "F1C8"
#define DEFAULT_CONFV				0xF1030000  // �汾�ţ��޸Ľṹ�� ConfigParameter_TypeDef ʱ�汾������
#define DEFAULT_BAUD				9600		// Ĭ�ϲ����ʣ���λ��bps
#define DEFAULT_PASSWORD			0x38		// Ĭ�ϳ�ʼ���룬ASCII��


// STM32F1xx��ƷΨһ��ݱ�ʶ�Ĵ�����96λ��12�ֽڣ�
//#define UID_BASE	0x1FFFF7E8



#define countof(a)   (sizeof(a) / sizeof(*(a)))

//#define STANDBY_DELAY 60		// ������ʱʱ�䣬��λs
#define MAX_PASSWORD_COUNT 6	// ����λ��


// ��Ч�����ʣ��� VALID_BAUD[]��Ӧ
typedef enum
{
	BAUDCODE_9600 = 0,		// 9600
	BAUDCODE_4800,
	BAUDCODE_14400,
	BAUDCODE_19200,
	BAUDCODE_38400,
	BAUDCODE_57600,
	BAUDCODE_115200,
}BaudCode_TypeDef;


// ������״̬�ֶ���, MS = Main Status
enum
{
	MS_MAIN_WINDOW_PASSWORD = 0,	// ��������
	MS_MAIN_WINDOW_PINGERPRINT,		// ָ��
	MS_MAIN_WINDOW_DATETIME,		// ����ʱ��
	
	MS_MAIN_DEBUG,		// ���Խ��档����Ϊ���һ��
};


typedef struct
{
	unsigned char   HardMainVersion;			// Ӳ���汾
	unsigned char   HardSubVersion;
	unsigned char   FirmwareMainVersion;		// �̼��汾
	unsigned char   FirmwareSubVersion;	
	unsigned int    Hclk;						// ϵͳʱ��
	
	// �����飬��˳��
	bool chkClock;								// �����ƵHCLK�Ƿ�Ϊ72MHz��true:OK
	bool chkCTP;								// ��鴥����ID
	bool chkFingerprintDevice;					// ���ָ���豸
	bool chkUsb;								// ���USB
	
	unsigned char   CurrentMenu;				// ��ǰ��ʾ�Ľ���
	unsigned char  FingerprintOk;				// ���ָ�Ʊ�־
	unsigned char  CommunicationTransfer;		// ͨ��ת������4bit�͵�4bit�ֱ��ʾת�����ͣ�0����ת��
//1�����Դ���1��ָ�ƴ���2��2�����Դ���1��USBEP1��3��ָ�ƴ��ں�USBEP1��4�����Դ���1��USBEP2
	unsigned char  CommandTypePre;				// ��һ��ָ�����ͣ��������̨ת����Ӧ��0����Ч
//	unsigned short  voltage;					// ��ѹ����λ��mV
//	volatile unsigned short  standby_delay_cnt;	// ������ʱ�������������ﵽ STANDBY_DELAY ʱ������ͣ��ģʽ��
//	unsigned char   battery_low_flag;			// �͵�ѹ��־��0��������1����ѹ���� LOW_BATTERY
//	unsigned char   charge_state;				// ���״̬����LiChargeState_TypeDef ö�٣�LCS_NONE��δ��磬LCS_CHARGING������У�LCS_DONE�������ɣ�LCS_ERROR��������
//	unsigned char   connect_usb;				// �Ƿ�����USB��0��δ���ӣ�1������
//	unsigned char   enter_low_power;			// 0:�������У�LCD����ʾ��1:����͹���ģʽ(stop��standby)
//	volatile unsigned char  wakeupkey_state;	// Wakeup����ON/OFF״̬����һ��0/1��ת
//	unsigned char   unused8;
	unsigned char  bNeedRefresh;	// �Ƿ���Ҫˢ����ʾ
	char FirmwareName[32];				// �̼�����

}FlagData_TypeDef;


// ���浽FLASH�еĲ����ṹ�壬��Ҫ4�ֽڶ���
typedef struct
{
	//====�̶����� bootloader���û����벿�ֱ���һ��============================================================
	unsigned int config_flag;				// �̼������Ĺ̶���ʶ��Ϊ�̶�ֵ��ȡֵ@DEFAULT_FLAG
	unsigned int config_version;			// �̼������İ汾���� DEFAULT_CONFV�����ڼ�¼�������ʱ ConfigData_TypeDef �İ汾��ÿ�μ���ʱ��ֵ��̼��е�ֵ��Ӧ��ֻ����ͬ���ܼ��أ�����ָ�Ĭ��ֵ��
	unsigned char  uid[12];					// MCU�����кţ���96bit��12�ֽڡ�
	unsigned int  baud;						// ������
	//===============================================================
	
	char password[MAX_PASSWORD_COUNT+1];	// �洢�����룬ΪASCII���ַ�����\0Ϊ��������Ĭ��ֵΪ888888
	
	unsigned int crc;	// У�飬�����ж�flash���Ƿ񱣴�����ȷ���趨����
	
}ConfigParameter_TypeDef;



// bootloader ���浽FLASH�еĲ����ṹ�壬��Ҫ4�ֽڶ���
typedef struct
{
	//====�̶����� bootloader���û����벿�ֱ���һ��============================================================
	unsigned int config_flag;				// �̼������Ĺ̶���ʶ��Ϊ�̶�ֵ��ȡֵ@DEFAULT_BLFLAG
	unsigned int config_version;			// �̼������İ汾���� DEFAULT_CONFV�����ڼ�¼�������ʱ ConfigData_TypeDef �İ汾��ÿ�μ���ʱ��ֵ��̼��е�ֵ��Ӧ��ֻ����ͬ���ܼ��أ�����ָ�Ĭ��ֵ��
	unsigned char  uid[12];					// MCU�����кţ���96bit��12�ֽڡ�
	unsigned int  baud;						// ������
	//===============================================================
	
	unsigned int crc;	// У�飬�����ж�flash���Ƿ񱣴�����ȷ���趨����
	
}BLConfigParameter_TypeDef;


// USB�˵��־
typedef struct
{
	volatile uint8_t  int_read;		// EndPoint1 OUT
	volatile uint8_t  int_write;		// EndPoint1 IN
	volatile uint8_t  bulk_read;		// EndPoint2 OUT
	volatile uint8_t  bulk_write;	// EndPoint2 IN
	
}USB_EndpointFlag_TypeDef;



//extern volatile unsigned int LocalTime;	// ����ʱ�䣬��λ��ms
extern FlagData_TypeDef  FlagData;		// ȫ�ֱ�־�����ṹ��
extern ConfigParameter_TypeDef  ConfigParameter;	// ȫ�ֲ����ṹ�����
extern BLConfigParameter_TypeDef  BLConfigParameter;	// bootloader ȫ�ֲ����ṹ�����
extern const uint32_t VALID_BAUD[7];	// ��Ч������

extern USB_EndpointFlag_TypeDef UsbEPFlagStruct;	// USB


void GetMachineID(unsigned char* idBuffer);
uint8_t GetBaudCode(uint32_t _baud);


//************ RTC ************//
extern volatile uint8_t g_TimeDisplayFlag;			// ����RTC���жϱ�־����λʱ������ʾ


extern volatile uint32_t g_RunTime;					// ȫ������ʱ�䣬��λ1ms�����ڼ�������ʱ��


#endif
