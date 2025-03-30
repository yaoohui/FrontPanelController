/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *screen_img_1;
	lv_obj_t *screen_imgbtn_1;
	lv_obj_t *screen_imgbtn_1_label;
	lv_obj_t *screen_label_1;
	lv_obj_t *screen_1;
	bool screen_1_del;
	lv_obj_t *screen_1_img_1;
	lv_obj_t *screen_1_label_1;
	lv_obj_t *screen_1_imgbtn_2;
	lv_obj_t *screen_1_imgbtn_2_label;
	lv_obj_t *screen_1_imgbtn_1;
	lv_obj_t *screen_1_imgbtn_1_label;
	lv_obj_t *screen_2;
	bool screen_2_del;
	lv_obj_t *screen_2_img_1;
	lv_obj_t *screen_2_label_1;
	lv_obj_t *screen_2_imgbtn_2;
	lv_obj_t *screen_2_imgbtn_2_label;
	lv_obj_t *screen_2_imgbtn_1;
	lv_obj_t *screen_2_imgbtn_1_label;
	lv_obj_t *screen_3;
	bool screen_3_del;
	lv_obj_t *screen_3_img_1;
	lv_obj_t *screen_3_label_1;
	lv_obj_t *screen_3_imgbtn_2;
	lv_obj_t *screen_3_imgbtn_2_label;
	lv_obj_t *screen_3_imgbtn_1;
	lv_obj_t *screen_3_imgbtn_1_label;
	lv_obj_t *screen_4;
	bool screen_4_del;
	lv_obj_t *screen_4_img_1;
	lv_obj_t *screen_4_label_1;
	lv_obj_t *screen_4_imgbtn_2;
	lv_obj_t *screen_4_imgbtn_2_label;
	lv_obj_t *screen_4_imgbtn_1;
	lv_obj_t *screen_4_imgbtn_1_label;
	lv_obj_t *screen_5;
	bool screen_5_del;
	lv_obj_t *screen_5_img_1;
	lv_obj_t *screen_5_label_1;
	lv_obj_t *screen_5_imgbtn_2;
	lv_obj_t *screen_5_imgbtn_2_label;
	lv_obj_t *screen_5_imgbtn_1;
	lv_obj_t *screen_5_imgbtn_1_label;
	lv_obj_t *screen_6;
	bool screen_6_del;
	lv_obj_t *screen_6_img_1;
	lv_obj_t *screen_6_label_1;
	lv_obj_t *screen_6_imgbtn_2;
	lv_obj_t *screen_6_imgbtn_2_label;
	lv_obj_t *screen_6_imgbtn_1;
	lv_obj_t *screen_6_imgbtn_1_label;
	lv_obj_t *screen_7;
	bool screen_7_del;
	lv_obj_t *screen_7_label_1;
	lv_obj_t *screen_7_imgbtn_2;
	lv_obj_t *screen_7_imgbtn_2_label;
	lv_obj_t *screen_7_qrcode_1;
	lv_obj_t *screen_8;
	bool screen_8_del;
	lv_obj_t *screen_8_label_1;
	lv_obj_t *screen_8_btn_1;
	lv_obj_t *screen_8_btn_1_label;
	lv_obj_t *screen_8_btn_2;
	lv_obj_t *screen_8_btn_2_label;
	lv_obj_t *screen_9;
	bool screen_9_del;
	lv_obj_t *screen_9_ta_1;
	lv_obj_t *screen_9_btn_2;
	lv_obj_t *screen_9_btn_2_label;
	lv_obj_t *screen_9_btn_1;
	lv_obj_t *screen_9_btn_1_label;
	lv_obj_t *screen_9_label_1;
	lv_obj_t *screen_10;
	bool screen_10_del;
	lv_obj_t *screen_10_btn_2;
	lv_obj_t *screen_10_btn_2_label;
	lv_obj_t *screen_10_btn_1;
	lv_obj_t *screen_10_btn_1_label;
	lv_obj_t *screen_10_ta_1;
	lv_obj_t *screen_10_label_1;
	lv_obj_t *screen_11;
	bool screen_11_del;
	lv_obj_t *screen_11_imgbtn_1;
	lv_obj_t *screen_11_imgbtn_1_label;
	lv_obj_t *screen_11_btn_1;
	lv_obj_t *screen_11_btn_1_label;
	lv_obj_t *screen_11_btn_2;
	lv_obj_t *screen_11_btn_2_label;
	lv_obj_t *screen_11_btn_3;
	lv_obj_t *screen_11_btn_3_label;
	lv_obj_t *screen_12;
	bool screen_12_del;
	lv_obj_t *screen_12_btn_2;
	lv_obj_t *screen_12_btn_2_label;
	lv_obj_t *screen_12_btn_1;
	lv_obj_t *screen_12_btn_1_label;
	lv_obj_t *screen_12_cb_1;
	lv_obj_t *screen_13;
	bool screen_13_del;
	lv_obj_t *screen_13_label_1;
	lv_obj_t *screen_13_ta_1;
	lv_obj_t *screen_13_btn_2;
	lv_obj_t *screen_13_btn_2_label;
	lv_obj_t *screen_13_btn_1;
	lv_obj_t *screen_13_btn_1_label;
	lv_obj_t *screen_14;
	bool screen_14_del;
	lv_obj_t *screen_14_label_1;
	lv_obj_t *screen_14_ta_1;
	lv_obj_t *screen_14_btn_2;
	lv_obj_t *screen_14_btn_2_label;
	lv_obj_t *screen_14_btn_1;
	lv_obj_t *screen_14_btn_1_label;
	lv_obj_t *screen_15;
	bool screen_15_del;
	lv_obj_t *screen_15_imgbtn_1;
	lv_obj_t *screen_15_imgbtn_1_label;
	lv_obj_t *screen_15_img_1;
	lv_obj_t *screen_15_img_2;
	lv_obj_t *screen_15_img_3;
	lv_obj_t *screen_15_img_4;
	lv_obj_t *screen_15_img_5;
	lv_obj_t *screen_15_img_6;
	lv_obj_t *screen_15_img_7;
	lv_obj_t *screen_15_img_8;
	lv_obj_t *screen_15_img_9;
	lv_obj_t *screen_15_line_1;
	lv_obj_t *screen_15_line_2;
	lv_obj_t *screen_15_line_3;
	lv_obj_t *screen_15_line_4;
	lv_obj_t *screen_16;
	bool screen_16_del;
	lv_obj_t *screen_16_label_1;
	lv_obj_t *screen_16_btn_2;
	lv_obj_t *screen_16_btn_2_label;
	lv_obj_t *screen_16_btn_1;
	lv_obj_t *screen_16_btn_1_label;
	lv_obj_t *screen_17;
	bool screen_17_del;
	lv_obj_t *screen_17_label_1;
	lv_obj_t *screen_17_btn_3;
	lv_obj_t *screen_17_btn_3_label;
	lv_obj_t *screen_17_btn_2;
	lv_obj_t *screen_17_btn_2_label;
	lv_obj_t *screen_17_btn_1;
	lv_obj_t *screen_17_btn_1_label;
	lv_obj_t *screen_18;
	bool screen_18_del;
	lv_obj_t *screen_18_label_1;
	lv_obj_t *screen_18_btn_2;
	lv_obj_t *screen_18_btn_2_label;
	lv_obj_t *screen_18_btn_1;
	lv_obj_t *screen_18_btn_1_label;
	lv_obj_t *screen_18_sw_1;
	lv_obj_t *screen_18_spinbox_1;
	lv_obj_t *screen_18_spinbox_1_btn_plus;
	lv_obj_t *screen_18_spinbox_1_btn_minus;
	lv_obj_t *screen_19;
	bool screen_19_del;
	lv_obj_t *screen_19_label_1;
	lv_obj_t *screen_19_btn_2;
	lv_obj_t *screen_19_btn_2_label;
	lv_obj_t *screen_19_btn_1;
	lv_obj_t *screen_19_btn_1_label;
	lv_obj_t *screen_19_sw_1;
	lv_obj_t *screen_19_spinbox_1;
	lv_obj_t *screen_19_spinbox_1_btn_plus;
	lv_obj_t *screen_19_spinbox_1_btn_minus;
	lv_obj_t *screen_20;
	bool screen_20_del;
	lv_obj_t *screen_20_imgbtn_1;
	lv_obj_t *screen_20_imgbtn_1_label;
	lv_obj_t *screen_20_btn_1;
	lv_obj_t *screen_20_btn_1_label;
	lv_obj_t *screen_20_btn_2;
	lv_obj_t *screen_20_btn_2_label;
	lv_obj_t *screen_20_btn_3;
	lv_obj_t *screen_20_btn_3_label;
	lv_obj_t *g_kb_top_layer;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen(lv_ui *ui);
void setup_scr_screen_1(lv_ui *ui);
void setup_scr_screen_2(lv_ui *ui);
void setup_scr_screen_3(lv_ui *ui);
void setup_scr_screen_4(lv_ui *ui);
void setup_scr_screen_5(lv_ui *ui);
void setup_scr_screen_6(lv_ui *ui);
void setup_scr_screen_7(lv_ui *ui);
void setup_scr_screen_8(lv_ui *ui);
void setup_scr_screen_9(lv_ui *ui);
void setup_scr_screen_10(lv_ui *ui);
void setup_scr_screen_11(lv_ui *ui);
void setup_scr_screen_12(lv_ui *ui);
void setup_scr_screen_13(lv_ui *ui);
void setup_scr_screen_14(lv_ui *ui);
void setup_scr_screen_15(lv_ui *ui);
void setup_scr_screen_16(lv_ui *ui);
void setup_scr_screen_17(lv_ui *ui);
void setup_scr_screen_18(lv_ui *ui);
void setup_scr_screen_19(lv_ui *ui);
void setup_scr_screen_20(lv_ui *ui);
LV_IMG_DECLARE(_power_005_alpha_128x128);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_fingerprint_006_alpha_128x128);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_reset_007_alpha_128x128);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_setup_001_alpha_128x128);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_CPU_002_alpha_128x128);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_CPU_fan_001_alpha_128x128);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_fan_001_alpha_128x128);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_right_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_left_003_alpha_32x64);
LV_IMG_DECLARE(_up_001_alpha_64x32);
LV_IMG_DECLARE(_up_001_alpha_64x32);
LV_IMG_DECLARE(_up_001_alpha_64x32);
LV_IMG_DECLARE(_up_001_alpha_64x32);
LV_IMG_DECLARE(_up_001_alpha_64x32);
LV_IMG_DECLARE(_up_001_alpha_64x32);
LV_IMG_DECLARE(_up_001_alpha_64x32);
LV_IMG_DECLARE(_up_001_alpha_64x32);
LV_IMG_DECLARE(_fingerprint_006_alpha_48x48);
LV_IMG_DECLARE(_fingerprint_006_alpha_48x48);
LV_IMG_DECLARE(_fingerprint_006_alpha_48x48);
LV_IMG_DECLARE(_fingerprint_006_alpha_48x48);
LV_IMG_DECLARE(_fingerprint_006_alpha_48x48);
LV_IMG_DECLARE(_fingerprint_006_alpha_48x48);
LV_IMG_DECLARE(_fingerprint_006_alpha_48x48);
LV_IMG_DECLARE(_fingerprint_006_alpha_48x48);
LV_IMG_DECLARE(_fingerprint_006_alpha_48x48);
LV_IMG_DECLARE(_up_001_alpha_64x32);
LV_IMG_DECLARE(_up_001_alpha_64x32);
LV_IMG_DECLARE(_up_001_alpha_64x32);
LV_IMG_DECLARE(_up_001_alpha_64x32);

LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_Acme_Regular_24)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_Acme_Regular_32)
LV_FONT_DECLARE(lv_font_SourceHanSerifSC_Regular_18)


#ifdef __cplusplus
}
#endif
#endif
