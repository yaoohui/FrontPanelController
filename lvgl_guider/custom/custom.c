/*
* Copyright 2023 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include "extra/widgets/msgbox/lv_msgbox.h"
#include "misc/lv_types.h"
#include "extra/widgets/keyboard/lv_keyboard.h"


/*********************
 *      DEFINES
 *********************/

bool pwr_flag = false;  // 开机状态标志位
bool black_screen_mode = true; // 关机黑屏
bool screensaver_mode = true; // 屏幕保护
uint8_t black_screen_delay = 1; // 黑屏延时时间（分钟）
uint8_t screensaver_delay = 3; // 屏保延时时间（分钟）
uint8_t FP_Num = 0;
uint8_t Max_Reg_Time = 4; // 最大注册次数
uint8_t FP_Reg_Times = 0; // 第几次注册
bool Wait_For_Finger_Flag = false; // 等待手指按下标志位
bool Wait_For_Lift_Flag = false; // 等待手指抬起标志位
bool Fingerprint_Register_Flag = false; // 进行指纹注册标志位

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
	Num_Keyboard_Init(ui);
}

void Power_On_Off(void)
{
#ifdef USE_HARDWARE
	HWPWR(1);
	HAL_Delay(500);
	HWPWR(0);
#endif
}

void HW_Reset(void)
{
#ifdef USE_HARDWARE
	HWRST(1);
	HAL_Delay(500);
	HWRST(0);
#endif
}

void touch_IRQ_Reset(void)
{
#ifdef USE_HARDWARE
	
	touch_IRQ = 0;
	
#endif
}

bool Comp_psw(char *psw)
{
#ifdef USE_HARDWARE
	
	if(strcmp(password, psw))
	{
		return false;
	}
	else
	{
		return true;
	}
	
#endif
	return false;
}


void Psw_Msgbox(void)
{
	lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Warning!!!", "Invalid password!", NULL, true);
	lv_obj_center(mbox1);
}

void New_Psw_Msgbox(void)
{
	lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Warning!!!", "Different password!", NULL, true);
	lv_obj_center(mbox1);
}

void Invalid_Psw_Msgbox(void)
{
	lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Warning!!!", "Must 6 numbers!", NULL, true);
	lv_obj_center(mbox1);
}

void Delete_failed_Msgbox(void)
{
	lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Warning!!!", "Deleted failed!", NULL, true);
	lv_obj_center(mbox1);
}

void About_Msgbox(void)
{
	lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Hello!", "www.yaoanji.com Ver: 1.0", NULL, true);
	lv_obj_center(mbox1);
}

void Num_Keyboard_Init(lv_ui *ui)
{
//  lv_keyboard_set_mode(ui->g_kb_top_layer, LV_KEYBOARD_MODE_NUMBER);
  static const char * btnm_map[] = {"1", "2", "3", "\n",
                                    "4", "5", "6", "\n",
                                    "7", "8", "9", "\n",
                                    LV_SYMBOL_BACKSPACE, "0", LV_SYMBOL_KEYBOARD, ""
                                    };
  lv_btnmatrix_set_map(ui->g_kb_top_layer, btnm_map);
}


void Touch_Img_Init(lv_ui *ui)
{
  if(FP_HAVE_Flag[0] == false)
  {
    lv_obj_set_style_img_opa(ui->screen_15_img_1, 127, LV_PART_MAIN|LV_STATE_DEFAULT);
  }
  if(FP_HAVE_Flag[1] == false)
  {
    lv_obj_set_style_img_opa(ui->screen_15_img_2, 127, LV_PART_MAIN|LV_STATE_DEFAULT);
  }
  if(FP_HAVE_Flag[2] == false)
  {
    lv_obj_set_style_img_opa(ui->screen_15_img_3, 127, LV_PART_MAIN|LV_STATE_DEFAULT);
  }
  if(FP_HAVE_Flag[3] == false)
  {
    lv_obj_set_style_img_opa(ui->screen_15_img_4, 127, LV_PART_MAIN|LV_STATE_DEFAULT);
  }
  if(FP_HAVE_Flag[4] == false)
  {
    lv_obj_set_style_img_opa(ui->screen_15_img_5, 127, LV_PART_MAIN|LV_STATE_DEFAULT);
  }
  if(FP_HAVE_Flag[5] == false)
  {
    lv_obj_set_style_img_opa(ui->screen_15_img_6, 127, LV_PART_MAIN|LV_STATE_DEFAULT);
  }
  if(FP_HAVE_Flag[6] == false)
  {
    lv_obj_set_style_img_opa(ui->screen_15_img_7, 127, LV_PART_MAIN|LV_STATE_DEFAULT);
  }
  if(FP_HAVE_Flag[7] == false)
  {
    lv_obj_set_style_img_opa(ui->screen_15_img_8, 127, LV_PART_MAIN|LV_STATE_DEFAULT);
  }
  if(FP_HAVE_Flag[8] == false)
  {
    lv_obj_set_style_img_opa(ui->screen_15_img_9, 127, LV_PART_MAIN|LV_STATE_DEFAULT);
  }
}


void Pwr_Std_Init(lv_ui *ui)
{
  if(pwr_flag)
	{
//		printf(">>状态：开机\r\n");
    lv_obj_set_style_img_opa(ui->screen_2_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	}
	else
	{
//		printf(">>状态：关机\r\n");
    lv_obj_set_style_img_opa(ui->screen_2_img_1, 127, LV_PART_MAIN|LV_STATE_DEFAULT);
	}
}


void Black_Screen_Init(lv_ui *ui)
{
  if(black_screen_mode)
  {
    lv_obj_add_state(ui->screen_19_sw_1, LV_STATE_CHECKED);
  }
  else
  {
    lv_obj_clear_state(ui->screen_19_sw_1, LV_STATE_CHECKED);
  }
  
  lv_spinbox_set_value(ui->screen_19_spinbox_1, black_screen_delay);
}


void Screensaver_Init(lv_ui *ui)
{
  if(screensaver_mode)
  {
    lv_obj_add_state(ui->screen_18_sw_1, LV_STATE_CHECKED);
  }
  else
  {
    lv_obj_clear_state(ui->screen_18_sw_1, LV_STATE_CHECKED);
  }
  
  lv_spinbox_set_value(ui->screen_18_spinbox_1, screensaver_delay);
}