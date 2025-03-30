#include "stdio.h"
#include "io.h"
#include "custom.h"

void Check_PWR_Std(void)
{
	if(!PWR_STD)
	{
//		printf(">>状态：开机\r\n");
//		LCD_BL(1); //LCD背光点亮
    pwr_flag = true;
	}
	else
	{
//		printf(">>状态：关机\r\n");
//		LCD_BL(0); //LCD背光熄灭
    pwr_flag = false;
	}
}
