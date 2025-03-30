/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen_11(lv_ui *ui)
{
    //Write codes screen_11
    ui->screen_11 = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_11, 240, 240);
    lv_obj_set_scrollbar_mode(ui->screen_11, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_11, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_11, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_11_imgbtn_1
    ui->screen_11_imgbtn_1 = lv_imgbtn_create(ui->screen_11);
    lv_obj_add_flag(ui->screen_11_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->screen_11_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_up_001_alpha_64x32, NULL);
    lv_imgbtn_set_src(ui->screen_11_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, &_up_001_alpha_64x32, NULL);
    lv_imgbtn_set_src(ui->screen_11_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_up_001_alpha_64x32, NULL);
    lv_imgbtn_set_src(ui->screen_11_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_up_001_alpha_64x32, NULL);
    ui->screen_11_imgbtn_1_label = lv_label_create(ui->screen_11_imgbtn_1);
    lv_label_set_text(ui->screen_11_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->screen_11_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_11_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_11_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->screen_11_imgbtn_1, 88, 8);
    lv_obj_set_size(ui->screen_11_imgbtn_1, 64, 32);

    //Write style for screen_11_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_11_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_11_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_11_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_11_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_11_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_11_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_11_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_11_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->screen_11_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->screen_11_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->screen_11_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->screen_11_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->screen_11_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->screen_11_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for screen_11_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->screen_11_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->screen_11_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->screen_11_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->screen_11_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->screen_11_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->screen_11_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for screen_11_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->screen_11_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->screen_11_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes screen_11_btn_1
    ui->screen_11_btn_1 = lv_btn_create(ui->screen_11);
    ui->screen_11_btn_1_label = lv_label_create(ui->screen_11_btn_1);
    lv_label_set_text(ui->screen_11_btn_1_label, "Password");
    lv_label_set_long_mode(ui->screen_11_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_11_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_11_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_11_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_11_btn_1, 40, 60);
    lv_obj_set_size(ui->screen_11_btn_1, 160, 50);

    //Write style for screen_11_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_11_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_11_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_11_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_11_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_11_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_11_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_11_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_11_btn_1, &lv_font_Acme_Regular_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_11_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_11_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_11_btn_2
    ui->screen_11_btn_2 = lv_btn_create(ui->screen_11);
    ui->screen_11_btn_2_label = lv_label_create(ui->screen_11_btn_2);
    lv_label_set_text(ui->screen_11_btn_2_label, "Fingerprint");
    lv_label_set_long_mode(ui->screen_11_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_11_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_11_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_11_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_11_btn_2, 40, 120);
    lv_obj_set_size(ui->screen_11_btn_2, 160, 50);

    //Write style for screen_11_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_11_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_11_btn_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_11_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_11_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_11_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_11_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_11_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_11_btn_2, &lv_font_Acme_Regular_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_11_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_11_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_11_btn_3
    ui->screen_11_btn_3 = lv_btn_create(ui->screen_11);
    ui->screen_11_btn_3_label = lv_label_create(ui->screen_11_btn_3);
    lv_label_set_text(ui->screen_11_btn_3_label, "System");
    lv_label_set_long_mode(ui->screen_11_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_11_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_11_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_11_btn_3_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_11_btn_3, 40, 180);
    lv_obj_set_size(ui->screen_11_btn_3, 160, 50);

    //Write style for screen_11_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_11_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_11_btn_3, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_11_btn_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_11_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_11_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_11_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_11_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_11_btn_3, &lv_font_Acme_Regular_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_11_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_11_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_11.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_11);

    //Init events for screen.
    events_init_screen_11(ui);
}
