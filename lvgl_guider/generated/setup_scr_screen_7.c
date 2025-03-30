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



void setup_scr_screen_7(lv_ui *ui)
{
    //Write codes screen_7
    ui->screen_7 = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_7, 240, 240);
    lv_obj_set_scrollbar_mode(ui->screen_7, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_7_label_1
    ui->screen_7_label_1 = lv_label_create(ui->screen_7);
    lv_label_set_text(ui->screen_7_label_1, "Ver: 1.0");
    lv_label_set_long_mode(ui->screen_7_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_7_label_1, 60, 190);
    lv_obj_set_size(ui->screen_7_label_1, 120, 32);

    //Write style for screen_7_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_7_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_7_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_7_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_7_label_1, &lv_font_Acme_Regular_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_7_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_7_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_7_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_7_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_7_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_7_label_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_7_label_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_7_label_1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_7_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_7_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_7_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_7_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_7_imgbtn_2
    ui->screen_7_imgbtn_2 = lv_imgbtn_create(ui->screen_7);
    lv_obj_add_flag(ui->screen_7_imgbtn_2, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->screen_7_imgbtn_2, LV_IMGBTN_STATE_RELEASED, NULL, &_left_003_alpha_32x64, NULL);
    lv_imgbtn_set_src(ui->screen_7_imgbtn_2, LV_IMGBTN_STATE_PRESSED, NULL, &_left_003_alpha_32x64, NULL);
    lv_imgbtn_set_src(ui->screen_7_imgbtn_2, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_left_003_alpha_32x64, NULL);
    lv_imgbtn_set_src(ui->screen_7_imgbtn_2, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_left_003_alpha_32x64, NULL);
    ui->screen_7_imgbtn_2_label = lv_label_create(ui->screen_7_imgbtn_2);
    lv_label_set_text(ui->screen_7_imgbtn_2_label, "");
    lv_label_set_long_mode(ui->screen_7_imgbtn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_7_imgbtn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_7_imgbtn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->screen_7_imgbtn_2, 8, 88);
    lv_obj_set_size(ui->screen_7_imgbtn_2, 32, 64);

    //Write style for screen_7_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_7_imgbtn_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_7_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_7_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_7_imgbtn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_7_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_7_imgbtn_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_7_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_7_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->screen_7_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->screen_7_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->screen_7_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->screen_7_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->screen_7_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->screen_7_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for screen_7_imgbtn_2, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->screen_7_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->screen_7_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->screen_7_imgbtn_2, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->screen_7_imgbtn_2, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->screen_7_imgbtn_2, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->screen_7_imgbtn_2, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for screen_7_imgbtn_2, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->screen_7_imgbtn_2, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->screen_7_imgbtn_2, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes screen_7_qrcode_1
    ui->screen_7_qrcode_1 = lv_qrcode_create(ui->screen_7, 128, lv_color_hex(0x861078), lv_color_hex(0xffffff));
    const char * screen_7_qrcode_1_data = "http://www.yaoanji.com/";
    lv_qrcode_update(ui->screen_7_qrcode_1, screen_7_qrcode_1_data, 23);
    lv_obj_set_pos(ui->screen_7_qrcode_1, 56, 36);
    lv_obj_set_size(ui->screen_7_qrcode_1, 128, 128);

    //The custom code of screen_7.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_7);

    //Init events for screen.
    events_init_screen_7(ui);
}
