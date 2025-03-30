/*
* Copyright 2023 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

#ifdef USE_HARDWARE

#include "main.h"
#include "io.h"
#include "eeprom_24c02.h"
#include "fingerprint.h"

#endif

extern bool FP_HAVE_Flag[9];
extern bool pwr_flag;  // 开机状态标志位
extern bool black_screen_mode;
extern bool screensaver_mode;
extern uint8_t black_screen_delay;
extern uint8_t screensaver_delay;
extern uint8_t FP_Num;
extern uint8_t Max_Reg_Time;
extern uint8_t FP_Reg_Times;
extern bool Wait_For_Finger_Flag; // 等待手指按下标志位
extern bool Wait_For_Lift_Flag; // 等待手指抬起标志位
extern bool Fingerprint_Register_Flag;

void custom_init(lv_ui *ui);
void Power_On_Off(void);
void HW_Reset(void);
void touch_IRQ_Reset(void);
bool Comp_psw(char *psw);
void Psw_Msgbox(void);
void New_Psw_Msgbox(void);
void Invalid_Psw_Msgbox(void);
void Delete_failed_Msgbox(void);
void Num_Keyboard_Init(lv_ui *ui);
void Touch_Img_Init(lv_ui *ui);
void Pwr_Std_Init(lv_ui *ui);
void Black_Screen_Init(lv_ui *ui);
void Screensaver_Init(lv_ui *ui);
void About_Msgbox(void);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
