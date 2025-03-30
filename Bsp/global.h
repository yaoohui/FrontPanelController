/*
*********************************************************************************************************
*
*	模块名称 : 全局变量声明
*	文件名称 : global.h
*   作    者 : 耀辉工作室   https://shop108339233.taobao.com/
*	版    本 : V1.0
*	说    明 :
*	修改记录 :
*		版本号	日期       	作者	说明
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


// 配置参数中的默认值
#define DEFAULT_BLFLAG				0x42544631	// bootloader固定值 "BTF1"，与bootloader保持一致
#define DEFAULT_FLAG				0x46314338	// 参数固定值 "F1C8"
#define DEFAULT_CONFV				0xF1030000  // 版本号，修改结构体 ConfigParameter_TypeDef 时版本号增加
#define DEFAULT_BAUD				9600		// 默认波特率，单位：bps
#define DEFAULT_PASSWORD			0x38		// 默认初始密码，ASCII码


// STM32F1xx产品唯一身份标识寄存器（96位，12字节）
//#define UID_BASE	0x1FFFF7E8



#define countof(a)   (sizeof(a) / sizeof(*(a)))

//#define STANDBY_DELAY 60		// 待机延时时间，单位s
#define MAX_PASSWORD_COUNT 6	// 密码位数


// 有效波特率，与 VALID_BAUD[]对应
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


// 主程序状态字定义, MS = Main Status
enum
{
	MS_MAIN_WINDOW_PASSWORD = 0,	// 输入密码
	MS_MAIN_WINDOW_PINGERPRINT,		// 指纹
	MS_MAIN_WINDOW_DATETIME,		// 日期时间
	
	MS_MAIN_DEBUG,		// 调试界面。必须为最后一个
};


typedef struct
{
	unsigned char   HardMainVersion;			// 硬件版本
	unsigned char   HardSubVersion;
	unsigned char   FirmwareMainVersion;		// 固件版本
	unsigned char   FirmwareSubVersion;	
	unsigned int    Hclk;						// 系统时钟
	
	// 外设检查，按顺序
	bool chkClock;								// 检查主频HCLK是否为72MHz。true:OK
	bool chkCTP;								// 检查触摸屏ID
	bool chkFingerprintDevice;					// 检查指纹设备
	bool chkUsb;								// 检查USB
	
	unsigned char   CurrentMenu;				// 当前显示的界面
	unsigned char  FingerprintOk;				// 获得指纹标志
	unsigned char  CommunicationTransfer;		// 通信转发，高4bit和低4bit分别表示转发类型，0：不转发
//1：调试串口1和指纹串口2，2：调试串口1和USBEP1，3：指纹串口和USBEP1，4：调试串口1和USBEP2
	unsigned char  CommandTypePre;				// 上一次指令类型，用于向电台转发并应答。0：无效
//	unsigned short  voltage;					// 电压，单位：mV
//	volatile unsigned short  standby_delay_cnt;	// 待机延时计数器。计数达到 STANDBY_DELAY 时，进入停机模式。
//	unsigned char   battery_low_flag;			// 低电压标志，0：正常，1：电压低于 LOW_BATTERY
//	unsigned char   charge_state;				// 充电状态，见LiChargeState_TypeDef 枚举，LCS_NONE：未充电，LCS_CHARGING：充电中，LCS_DONE：充电完成，LCS_ERROR：充电错误
//	unsigned char   connect_usb;				// 是否连接USB，0：未连接，1：连接
//	unsigned char   enter_low_power;			// 0:正常运行，LCD有显示。1:进入低功耗模式(stop或standby)
//	volatile unsigned char  wakeupkey_state;	// Wakeup按键ON/OFF状态，按一下0/1翻转
//	unsigned char   unused8;
	unsigned char  bNeedRefresh;	// 是否需要刷新显示
	char FirmwareName[32];				// 固件名称

}FlagData_TypeDef;


// 保存到FLASH中的参数结构体，需要4字节对齐
typedef struct
{
	//====固定部分 bootloader与用户代码部分保持一致============================================================
	unsigned int config_flag;				// 固件参数的固定标识，为固定值：取值@DEFAULT_FLAG
	unsigned int config_version;			// 固件参数的版本，见 DEFAULT_CONFV，用于记录保存参数时 ConfigData_TypeDef 的版本，每次加载时此值与固件中的值对应，只有相同才能加载，否则恢复默认值。
	unsigned char  uid[12];					// MCU的序列号，共96bit，12字节。
	unsigned int  baud;						// 波特率
	//===============================================================
	
	char password[MAX_PASSWORD_COUNT+1];	// 存储的密码，为ASCII码字符串，\0为结束符。默认值为888888
	
	unsigned int crc;	// 校验，用于判断flash中是否保存有正确的设定参数
	
}ConfigParameter_TypeDef;



// bootloader 保存到FLASH中的参数结构体，需要4字节对齐
typedef struct
{
	//====固定部分 bootloader与用户代码部分保持一致============================================================
	unsigned int config_flag;				// 固件参数的固定标识，为固定值：取值@DEFAULT_BLFLAG
	unsigned int config_version;			// 固件参数的版本，见 DEFAULT_CONFV，用于记录保存参数时 ConfigData_TypeDef 的版本，每次加载时此值与固件中的值对应，只有相同才能加载，否则恢复默认值。
	unsigned char  uid[12];					// MCU的序列号，共96bit，12字节。
	unsigned int  baud;						// 波特率
	//===============================================================
	
	unsigned int crc;	// 校验，用于判断flash中是否保存有正确的设定参数
	
}BLConfigParameter_TypeDef;


// USB端点标志
typedef struct
{
	volatile uint8_t  int_read;		// EndPoint1 OUT
	volatile uint8_t  int_write;		// EndPoint1 IN
	volatile uint8_t  bulk_read;		// EndPoint2 OUT
	volatile uint8_t  bulk_write;	// EndPoint2 IN
	
}USB_EndpointFlag_TypeDef;



//extern volatile unsigned int LocalTime;	// 本地时间，单位：ms
extern FlagData_TypeDef  FlagData;		// 全局标志变量结构体
extern ConfigParameter_TypeDef  ConfigParameter;	// 全局参数结构体变量
extern BLConfigParameter_TypeDef  BLConfigParameter;	// bootloader 全局参数结构体变量
extern const uint32_t VALID_BAUD[7];	// 有效波特率

extern USB_EndpointFlag_TypeDef UsbEPFlagStruct;	// USB


void GetMachineID(unsigned char* idBuffer);
uint8_t GetBaudCode(uint32_t _baud);


//************ RTC ************//
extern volatile uint8_t g_TimeDisplayFlag;			// 用于RTC秒中断标志，置位时更新显示


extern volatile uint32_t g_RunTime;					// 全局运行时间，单位1ms，用于计算运行时间


#endif
