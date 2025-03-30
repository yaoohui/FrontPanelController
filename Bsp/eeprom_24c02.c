#include "eeprom_24c02.h"


int AT24C02_write(uint8_t addr, uint8_t* dataPtr, uint16_t dataSize)
{
	if (dataSize == 0)
	{
		return -1;
	}
    
	int res = HAL_OK;

	int selectPage_idx  = addr % PAGE_SIZE;
	int selectPage_rest = PAGE_SIZE - selectPage_idx;

	if (dataSize <= selectPage_rest)
	{
		res = HAL_I2C_Mem_Write(&AT24CXX_HANDLE, ADDR_24C02_Write,  addr, I2C_MEMADD_SIZE_8BIT,  dataPtr, dataSize, 0xFF);

		if (HAL_OK != res)
		{
			return -1;
		}

		HAL_Delay(10);
	}
	else
	{
		res = HAL_I2C_Mem_Write(&AT24CXX_HANDLE, ADDR_24C02_Write, addr, I2C_MEMADD_SIZE_8BIT, dataPtr, selectPage_rest, 0xFF);

		if (HAL_OK != res) { return -1; }

		addr     += selectPage_rest;
		dataSize -= selectPage_rest;
		dataPtr  += selectPage_rest;

		HAL_Delay(5);

		/*! 2 write nextPage full */
		int fullPage = dataSize/PAGE_SIZE;
		for (int iPage = 0; iPage < fullPage; ++iPage)
		{
			res = HAL_I2C_Mem_Write(&AT24CXX_HANDLE, ADDR_24C02_Write, addr, I2C_MEMADD_SIZE_8BIT, dataPtr, PAGE_SIZE, 0xFF);

			if (HAL_OK != res)
			{
				return -1;
			}

			HAL_Delay(5);

			addr     += PAGE_SIZE;
			dataSize -= PAGE_SIZE;
			dataPtr  += PAGE_SIZE;
		}

		/*! 3 write rest */
		if (dataSize != 0)
		{
			res = HAL_I2C_Mem_Write(&AT24CXX_HANDLE, ADDR_24C02_Write, addr, I2C_MEMADD_SIZE_8BIT, dataPtr, dataSize, 0xFF);

			if (HAL_OK != res)
			{
				return -1;
			}

			HAL_Delay(5);
		}
	}

	return 0;
}
 

int AT24C02_read(uint8_t addr, uint8_t* dataPtr, uint16_t dataSize)
{
	int res = HAL_I2C_Mem_Read(&AT24CXX_HANDLE, ADDR_24C02_Read, addr, I2C_MEMADD_SIZE_8BIT, dataPtr, dataSize, 0xFF);

	if (HAL_OK != res)
	{
		return -1;
	}

	return 0;
}


void Write_Init_Password(void)
{
	uint8_t password[] = "123456";
	
	AT24C02_write(0, password, 7);
}


void Write_Init_Black_Screen_Settings(void)
{
	uint8_t Black_Screen_Settings[2];
  
  Black_Screen_Settings[0] = 1; // 使能
  Black_Screen_Settings[1] = 1; // 分钟
	
	AT24C02_write(9, Black_Screen_Settings, 2);
}


void Write_Init_Screensaver_Settings(void)
{
	uint8_t Screensaver_Settings[2] = {1, 3}; // 使能，3分钟
	
	AT24C02_write(11, Screensaver_Settings, 2);
}


uint8_t AT24CXX_Check(void)
{
	uint8_t temp;
	uint8_t data = 0xAA;
	
	AT24C02_read(EE_TYPE, &temp, 1); // 避免每次开机都写AT24C02
	
	if(temp == data)
		return 0;
	
	AT24C02_write(EE_TYPE, &data, 1);
	AT24C02_read(EE_TYPE, &temp, 1);
	
	if(temp != data)
	{
		return 1;
	}
	else
	{
		Write_Init_Password();
    Write_Init_Black_Screen_Settings();
    Write_Init_Screensaver_Settings();
	}
	
	return 0;
}
