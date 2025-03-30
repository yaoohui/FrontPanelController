#include "touch_CST816D.h"
#include "stdio.h"


const uint16_t CST816_TPX_TBL[5] = {CST816D_TP1_REG, CST816D_TP2_REG, CST816D_TP3_REG, CST816D_TP4_REG, CST816D_TP5_REG};
TouchPointRefTypeDef TPR_Structure;
uint16_t touch_x = 0, touch_y = 0;

void CST816D_Write_Reg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen)
{
	HAL_I2C_Mem_Write(&CST816D_I2C, CST816D_CMD_WR, _usRegAddr, I2C_MEMADD_SIZE_16BIT, _pRegBuf, _ucLen, 0xff);
}

void CST816D_Read_Reg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen)
{
	HAL_I2C_Mem_Read(&CST816D_I2C, CST816D_CMD_RD, _usRegAddr, I2C_MEMADD_SIZE_16BIT, _pRegBuf, _ucLen, 0xff);
}

// ��Ҫ����
static void i2c_hw_reset(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = TP_SCL_Pin | TP_SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(TP_I2C_GPIO_Port, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(TP_I2C_GPIO_Port, TP_SCL_Pin | TP_SDA_Pin, GPIO_PIN_SET);

	if (HAL_GPIO_ReadPin(TP_I2C_GPIO_Port, TP_SCL_Pin) == GPIO_PIN_RESET || HAL_GPIO_ReadPin(TP_I2C_GPIO_Port, TP_SDA_Pin) == GPIO_PIN_RESET)
	{
		//HAL_Delay(10);
	}

	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	HAL_GPIO_Init(TP_I2C_GPIO_Port, &GPIO_InitStruct);
	CST816D_I2C.Instance->CR1 |= I2C_CR1_SWRST;
	CST816D_I2C.Instance->CR1 &= ~I2C_CR1_SWRST;
	HAL_I2C_DeInit(&CST816D_I2C);								// �ͷ�IO��ΪGPIO����λ���״̬
	HAL_I2C_Init(&CST816D_I2C);									// ������³�ʼ��I2C����
}


/**
  * @brief  ������ʼ����
  * @param  None. 
  * @retval None.
  */
void CST816D_Init(void)
{
	uint8_t CST816D_ID;
	uint8_t temp = 0;
	uint8_t tempbuff[8];
	
	CST816_RST(0);
	HAL_Delay(50);
	CST816_RST(1);
	HAL_Delay(100);

	temp = 0;
	CST816D_Write_Reg(CST816D_DEVIDE_MODE, &temp, 1);					//������������ģʽ
	
	// ������Чֵ��22��ԽСԽ����
	temp = 22;
	CST816D_Write_Reg(CST816D_ID_G_THGROUP, &temp, 1);					//���ô�����Чֵ
	
	// �������ڣ�����С��12�����14
	temp = 14;
	CST816D_Write_Reg(CST816D_ID_G_PERIODACTIVE, &temp, 1);

//	CST816D_Read_Reg(Chip_Vendor_ID, &CST816D_ID, 1);
//	printf("CST816D_ID:%x\r\n", CST816D_ID);
	CST816D_Read_Reg(Chip_Vendor_ID, tempbuff, 3);
	printf("CST816 ID: 0x%02X, ProjID: %d, FwVersion: %d\r\n", tempbuff[0],tempbuff[1],tempbuff[2]);//CST816 ID: 0xB5, ProjID: 0, FwVersion: 1

	if(tempbuff[0] == 0xB6)
	{
		printf("������ʼ���ɹ���\r\n");
	}
	else
	{
		printf("������ʼ��ʧ�ܣ�\r\n");
	}
}


/**
  * @brief  ����ɨ�衣
  * @param  None. 
  * @retval None.
  */
void CST816D_Scan(void)
{
	uint8_t fingerNum = 0, st = 0, gesture = 0;
	uint8_t buf[7] = {0,0,0,0,0,0,0};
	
	CST816D_Read_Reg(0x00, buf, 7); // �ӼĴ���0������7���ֽ�
	gesture = buf[1];	// ����
	fingerNum = buf[2];	// ��ָ����
	
//	printf("��ָ������%d\r\n", buf[2]);
	
	if((fingerNum == 0xFF) || (fingerNum == 0))	// ����ָʱ��Ҳ����0xFF
	{
		tp_pressed = 0;
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
		
		return;
	}
	
	touch_x = buf[3] & 0x0F;	// x ���ֽ�
	touch_x <<= 8;
	touch_x += buf[4];
	touch_y = buf[5] & 0x0F;	// y ���ֽ�
	touch_y <<= 8;
	touch_y += buf[6];
	st = buf[3] >> 6;
//	printf("num:%02XH, mode:%02XH, st:%d, g:%02XH\r\n", fingerNum,buf[0], st, gesture);
//	printf("x:%d,y:%d\r\n", touch_x, touch_y);
	
//	tp_pressed = 1;
}
