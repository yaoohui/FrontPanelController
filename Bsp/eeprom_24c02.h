#ifndef __EEPROM_24C02
#define __EEPROM_24C02

#include "main.h"
#include "i2c.h"

#define AT24CXX_HANDLE			hi2c2

#define AT24C01							127
#define AT24C02							255
#define AT24C04							511
#define AT24C08							1023
#define AT24C16							2047
#define AT24C32							4095
#define AT24C64							8191
#define AT24C128						16383
#define AT24C256						32767  

// AT24C02
#define EE_TYPE							AT24C02

#define ADDR_24C02_Write		0xA0
#define ADDR_24C02_Read			0xA1
#define MAX_SIZE						256
#define PAGE_SIZE						8
#define PAGE_TOTAL					MAX_SIZE / PAGE_SIZE

int AT24C02_write(uint8_t addr, uint8_t* dataPtr, uint16_t dataSize);
int AT24C02_read (uint8_t addr, uint8_t* dataPtr, uint16_t dataSize);
uint8_t AT24CXX_Check(void);


#endif