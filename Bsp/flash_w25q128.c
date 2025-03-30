/*
 * W25Q128.c
 *
 *  Created on: May 12, 2024
 *      Author: Administrator
 */

#include "main.h"
#include "spi.h"
#include "stdio.h"
#include "string.h"
#include "flash_w25q128.h"
/*
 * @brief 读取器件ID、状态寄存器SR1和SR2
 * @param
 */
void Flash_TestReadStatus(void)
{
	uint16_t devID = Flash_ReadID();									/* 读取器件ID */
	uint8_t tempStrDevID[50];											/* 用来接字符串 */
	sprintf((char*)tempStrDevID,"Device ID = 0x%04X",devID);       	/* 将一个设备ID（devID）格式化为字符串，并存储在 tempStrDevID 变量中 */
	printf("%s\r\n",tempStrDevID);										/* 打印tempStrDevID */

	switch(devID){														/* 判读flash的型号 */
		case 0xEF17:
			printf("The chip is W25q128\r\n");
		break;
		default:
			printf("The chip is Unknow\r\n");
		break;
	}
	/* 读寄存器SR1的内容 */
	uint8_t tempStrSR1[50];
	sprintf((char*)tempStrSR1,"Status Reg1 = 0x%x",Flash_ReadSR1());  /* 将Flash_ReadSR1函数的返回值直接进行拼接 */
	printf("%s\r\n",tempStrSR1);

		/* 读寄存器SR2的内容 */
	uint8_t tempStrSR2[50];
	sprintf((char*)tempStrSR2,"Status Reg1 = 0x%x",Flash_ReadSR2());  /* 将Flash_ReadSR1函数的返回值直接进行拼接 */
	printf("%s\r\n",tempStrSR2);
}


/*
 * @brief  写flash测试
 * @param
 */
void Flash_TestWrite(void)
{
	uint8_t BlockNo = 0;																									/* 表示块号 */
	uint8_t SubSectorNo = 0;																									/* 表示扇区 */
	uint8_t  SubPageNo 	= 0;																									/* 表示页号 */
	uint32_t memAddress = 0;  																								/* 存储地址 */

	memAddress = Flash_Addr_byBlockSectorPage( BlockNo,SubSectorNo,SubPageNo);/* 计算内存地址，并将结果存储在memAddress变量中 */

	uint8_t bufStr1[30] = "Hello from brginning";
	Flash_WriteInPage(memAddress,bufStr1,strlen("Hello from brginning")+1);		/* 在指定的内存地址写入bufStr1（第0页的起始地址） */
	printf("Write in page 0 = %s\r\n",bufStr1);

	uint8_t bufStr2[30] = "Hello in page";
	Flash_WriteInPage(memAddress + 100,bufStr2,strlen("Hello from brginning")+1); /* 上一个位置偏移100个位置写入字符bufStr2 */
	printf("Write in page 100 = %s\r\n",bufStr2);

	uint8_t bufPage[FLASH_PAGE_SIZE];
	for(uint16_t i = 0;i < FLASH_PAGE_SIZE;++i){  /* 使用for循环将0 到 FLASH_PAGE_SIZE-1填充到bufPage数组 */
		bufPage[i] = i;
	}

	SubPageNo = 1; 																														/* 再到第1页 */
	memAddress = Flash_Addr_byBlockSectorPage( BlockNo,SubSectorNo,SubPageNo);/* 计算第一页的地址 */
	Flash_WriteInPage(memAddress ,bufPage,FLASH_PAGE_SIZE);  									/* 将填充好的 bufPage 数据写入到内存地址中 */
	printf("Write 0~255 in page1\r\n ");
}
/*
 * @brief   读flash测试
 * @param
 */
void Flash_TestRead(void)
{
	uint8_t BlockNo 		= 0;																									/* 表示块号 */
	uint8_t SubSectorNo = 0;																									/* 表示扇区 */
	uint8_t  SubPageNo 	= 0;																									/* 表示页号 */
	uint32_t memAddress = Flash_Addr_byBlockSectorPage( BlockNo,SubSectorNo,SubPageNo);
	uint8_t bufStr[50];
	Flash_ReadBytes(memAddress,bufStr,50);  																	/* 读50字节 */
	printf("Read in page 0 = %s\r\n",bufStr);																		/* 将50个字符串打印出来 */

	Flash_ReadBytes(memAddress + 100,bufStr,50);  														/* 读50字节 */
	printf("Read in page 100 = %s\r\n",bufStr);																	/* 将50个字符串打印出来 */

  SubPageNo 	= 1;
	memAddress = Flash_Addr_byBlockSectorPage( BlockNo,SubSectorNo,SubPageNo);/* 计算第一页的地址 */
	uint8_t randData12 = Flash_ReadOneByte(memAddress + 12);									/* 读取地址中偏移量为12的字节数据，并将其存储在randData12变量中 */
	uint8_t randData136 = Flash_ReadOneByte(memAddress + 136);								/* 读取地址中偏移量为136的字节数据，并将其存储在randData136变量中 */
	uint8_t randData210= Flash_ReadOneByte(memAddress + 210);									/* 读取地址中偏移量为210的字节数据，并将其存储在randData210变量中 */

	char tempStrRandData[100]="";      																				/* 使用前先清空 */
	sprintf((char*)tempStrRandData,"Page1[12] = %d,Page1[136] = %d,Page1[210] = %d",randData12,randData136,randData210);
	printf("%s\r\n",tempStrRandData);
}

