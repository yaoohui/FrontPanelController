#include "stdio.h"
#include "io.h"
#include "custom.h"

void Check_PWR_Std(void)
{
	if(!PWR_STD)
	{
//		printf(">>״̬������\r\n");
//		LCD_BL(1); //LCD�������
    pwr_flag = true;
	}
	else
	{
//		printf(">>״̬���ػ�\r\n");
//		LCD_BL(0); //LCD����Ϩ��
    pwr_flag = false;
	}
}
