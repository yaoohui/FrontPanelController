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
 * @brief ��ȡ����ID��״̬�Ĵ���SR1��SR2
 * @param
 */
void Flash_TestReadStatus(void)
{
	uint16_t devID = Flash_ReadID();									/* ��ȡ����ID */
	uint8_t tempStrDevID[50];											/* �������ַ��� */
	sprintf((char*)tempStrDevID,"Device ID = 0x%04X",devID);       	/* ��һ���豸ID��devID����ʽ��Ϊ�ַ��������洢�� tempStrDevID ������ */
	printf("%s\r\n",tempStrDevID);										/* ��ӡtempStrDevID */

	switch(devID){														/* �ж�flash���ͺ� */
		case 0xEF17:
			printf("The chip is W25q128\r\n");
		break;
		default:
			printf("The chip is Unknow\r\n");
		break;
	}
	/* ���Ĵ���SR1������ */
	uint8_t tempStrSR1[50];
	sprintf((char*)tempStrSR1,"Status Reg1 = 0x%x",Flash_ReadSR1());  /* ��Flash_ReadSR1�����ķ���ֱֵ�ӽ���ƴ�� */
	printf("%s\r\n",tempStrSR1);

		/* ���Ĵ���SR2������ */
	uint8_t tempStrSR2[50];
	sprintf((char*)tempStrSR2,"Status Reg1 = 0x%x",Flash_ReadSR2());  /* ��Flash_ReadSR1�����ķ���ֱֵ�ӽ���ƴ�� */
	printf("%s\r\n",tempStrSR2);
}


/*
 * @brief  дflash����
 * @param
 */
void Flash_TestWrite(void)
{
	uint8_t BlockNo = 0;																									/* ��ʾ��� */
	uint8_t SubSectorNo = 0;																									/* ��ʾ���� */
	uint8_t  SubPageNo 	= 0;																									/* ��ʾҳ�� */
	uint32_t memAddress = 0;  																								/* �洢��ַ */

	memAddress = Flash_Addr_byBlockSectorPage( BlockNo,SubSectorNo,SubPageNo);/* �����ڴ��ַ����������洢��memAddress������ */

	uint8_t bufStr1[30] = "Hello from brginning";
	Flash_WriteInPage(memAddress,bufStr1,strlen("Hello from brginning")+1);		/* ��ָ�����ڴ��ַд��bufStr1����0ҳ����ʼ��ַ�� */
	printf("Write in page 0 = %s\r\n",bufStr1);

	uint8_t bufStr2[30] = "Hello in page";
	Flash_WriteInPage(memAddress + 100,bufStr2,strlen("Hello from brginning")+1); /* ��һ��λ��ƫ��100��λ��д���ַ�bufStr2 */
	printf("Write in page 100 = %s\r\n",bufStr2);

	uint8_t bufPage[FLASH_PAGE_SIZE];
	for(uint16_t i = 0;i < FLASH_PAGE_SIZE;++i){  /* ʹ��forѭ����0 �� FLASH_PAGE_SIZE-1��䵽bufPage���� */
		bufPage[i] = i;
	}

	SubPageNo = 1; 																														/* �ٵ���1ҳ */
	memAddress = Flash_Addr_byBlockSectorPage( BlockNo,SubSectorNo,SubPageNo);/* �����һҳ�ĵ�ַ */
	Flash_WriteInPage(memAddress ,bufPage,FLASH_PAGE_SIZE);  									/* �����õ� bufPage ����д�뵽�ڴ��ַ�� */
	printf("Write 0~255 in page1\r\n ");
}
/*
 * @brief   ��flash����
 * @param
 */
void Flash_TestRead(void)
{
	uint8_t BlockNo 		= 0;																									/* ��ʾ��� */
	uint8_t SubSectorNo = 0;																									/* ��ʾ���� */
	uint8_t  SubPageNo 	= 0;																									/* ��ʾҳ�� */
	uint32_t memAddress = Flash_Addr_byBlockSectorPage( BlockNo,SubSectorNo,SubPageNo);
	uint8_t bufStr[50];
	Flash_ReadBytes(memAddress,bufStr,50);  																	/* ��50�ֽ� */
	printf("Read in page 0 = %s\r\n",bufStr);																		/* ��50���ַ�����ӡ���� */

	Flash_ReadBytes(memAddress + 100,bufStr,50);  														/* ��50�ֽ� */
	printf("Read in page 100 = %s\r\n",bufStr);																	/* ��50���ַ�����ӡ���� */

  SubPageNo 	= 1;
	memAddress = Flash_Addr_byBlockSectorPage( BlockNo,SubSectorNo,SubPageNo);/* �����һҳ�ĵ�ַ */
	uint8_t randData12 = Flash_ReadOneByte(memAddress + 12);									/* ��ȡ��ַ��ƫ����Ϊ12���ֽ����ݣ�������洢��randData12������ */
	uint8_t randData136 = Flash_ReadOneByte(memAddress + 136);								/* ��ȡ��ַ��ƫ����Ϊ136���ֽ����ݣ�������洢��randData136������ */
	uint8_t randData210= Flash_ReadOneByte(memAddress + 210);									/* ��ȡ��ַ��ƫ����Ϊ210���ֽ����ݣ�������洢��randData210������ */

	char tempStrRandData[100]="";      																				/* ʹ��ǰ����� */
	sprintf((char*)tempStrRandData,"Page1[12] = %d,Page1[136] = %d,Page1[210] = %d",randData12,randData136,randData210);
	printf("%s\r\n",tempStrRandData);
}

