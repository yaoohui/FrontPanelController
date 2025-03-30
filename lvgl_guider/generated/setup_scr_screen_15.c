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



void setup_scr_screen_15(lv_ui *ui)
{
    //Write codes screen_15
    ui->screen_15 = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_15, 240, 240);
    lv_obj_set_scrollbar_mode(ui->screen_15, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_15, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_15, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_15_imgbtn_1
    ui->screen_15_imgbtn_1 = lv_imgbtn_create(ui->screen_15);
    lv_obj_add_flag(ui->screen_15_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);
    lv_imgbtn_set_src(ui->screen_15_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_up_001_alpha_64x32, NULL);
    lv_imgbtn_set_src(ui->screen_15_imgbtn_1, LV_IMGBTN_STATE_PRESSED, NULL, &_up_001_alpha_64x32, NULL);
    lv_imgbtn_set_src(ui->screen_15_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_up_001_alpha_64x32, NULL);
    lv_imgbtn_set_src(ui->screen_15_imgbtn_1, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &_up_001_alpha_64x32, NULL);
    ui->screen_15_imgbtn_1_label = lv_label_create(ui->screen_15_imgbtn_1);
    lv_label_set_text(ui->screen_15_imgbtn_1_label, "");
    lv_label_set_long_mode(ui->screen_15_imgbtn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_15_imgbtn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_15_imgbtn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_pos(ui->screen_15_imgbtn_1, 88, 8);
    lv_obj_set_size(ui->screen_15_imgbtn_1, 64, 32);

    //Write style for screen_15_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_15_imgbtn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_15_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_15_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_15_imgbtn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_15_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_15_imgbtn_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_15_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_15_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_img_recolor_opa(ui->screen_15_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_img_opa(ui->screen_15_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->screen_15_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->screen_15_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->screen_15_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->screen_15_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for screen_15_imgbtn_1, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_img_recolor_opa(ui->screen_15_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_img_opa(ui->screen_15_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->screen_15_imgbtn_1, lv_color_hex(0xFF33FF), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->screen_15_imgbtn_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->screen_15_imgbtn_1, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->screen_15_imgbtn_1, 0, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style for screen_15_imgbtn_1, Part: LV_PART_MAIN, State: LV_IMGBTN_STATE_RELEASED.
    lv_obj_set_style_img_recolor_opa(ui->screen_15_imgbtn_1, 0, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);
    lv_obj_set_style_img_opa(ui->screen_15_imgbtn_1, 255, LV_PART_MAIN|LV_IMGBTN_STATE_RELEASED);

    //Write codes screen_15_img_1
    ui->screen_15_img_1 = lv_img_create(ui->screen_15);
    lv_obj_add_flag(ui->screen_15_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_15_img_1, &_fingerprint_006_alpha_48x48);
    lv_img_set_pivot(ui->screen_15_img_1, 50,50);
    lv_img_set_angle(ui->screen_15_img_1, 0);
    lv_obj_set_pos(ui->screen_15_img_1, 32, 56);
    lv_obj_set_size(ui->screen_15_img_1, 48, 48);

    //Write style for screen_15_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_15_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_15_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_15_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_15_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_15_img_2
    ui->screen_15_img_2 = lv_img_create(ui->screen_15);
    lv_obj_add_flag(ui->screen_15_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_15_img_2, &_fingerprint_006_alpha_48x48);
    lv_img_set_pivot(ui->screen_15_img_2, 50,50);
    lv_img_set_angle(ui->screen_15_img_2, 0);
    lv_obj_set_pos(ui->screen_15_img_2, 96, 56);
    lv_obj_set_size(ui->screen_15_img_2, 48, 48);

    //Write style for screen_15_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_15_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_15_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_15_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_15_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_15_img_3
    ui->screen_15_img_3 = lv_img_create(ui->screen_15);
    lv_obj_add_flag(ui->screen_15_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_15_img_3, &_fingerprint_006_alpha_48x48);
    lv_img_set_pivot(ui->screen_15_img_3, 50,50);
    lv_img_set_angle(ui->screen_15_img_3, 0);
    lv_obj_set_pos(ui->screen_15_img_3, 160, 56);
    lv_obj_set_size(ui->screen_15_img_3, 48, 48);

    //Write style for screen_15_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_15_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_15_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_15_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_15_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_15_img_4
    ui->screen_15_img_4 = lv_img_create(ui->screen_15);
    lv_obj_add_flag(ui->screen_15_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_15_img_4, &_fingerprint_006_alpha_48x48);
    lv_img_set_pivot(ui->screen_15_img_4, 50,50);
    lv_img_set_angle(ui->screen_15_img_4, 0);
    lv_obj_set_pos(ui->screen_15_img_4, 32, 120);
    lv_obj_set_size(ui->screen_15_img_4, 48, 48);

    //Write style for screen_15_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_15_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_15_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_15_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_15_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_15_img_5
    ui->screen_15_img_5 = lv_img_create(ui->screen_15);
    lv_obj_add_flag(ui->screen_15_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_15_img_5, &_fingerprint_006_alpha_48x48);
    lv_img_set_pivot(ui->screen_15_img_5, 50,50);
    lv_img_set_angle(ui->screen_15_img_5, 0);
    lv_obj_set_pos(ui->screen_15_img_5, 96, 120);
    lv_obj_set_size(ui->screen_15_img_5, 48, 48);

    //Write style for screen_15_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_15_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_15_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_15_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_15_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_15_img_6
    ui->screen_15_img_6 = lv_img_create(ui->screen_15);
    lv_obj_add_flag(ui->screen_15_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_15_img_6, &_fingerprint_006_alpha_48x48);
    lv_img_set_pivot(ui->screen_15_img_6, 50,50);
    lv_img_set_angle(ui->screen_15_img_6, 0);
    lv_obj_set_pos(ui->screen_15_img_6, 160, 120);
    lv_obj_set_size(ui->screen_15_img_6, 48, 48);

    //Write style for screen_15_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_15_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_15_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_15_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_15_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_15_img_7
    ui->screen_15_img_7 = lv_img_create(ui->screen_15);
    lv_obj_add_flag(ui->screen_15_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_15_img_7, &_fingerprint_006_alpha_48x48);
    lv_img_set_pivot(ui->screen_15_img_7, 50,50);
    lv_img_set_angle(ui->screen_15_img_7, 0);
    lv_obj_set_pos(ui->screen_15_img_7, 32, 184);
    lv_obj_set_size(ui->screen_15_img_7, 48, 48);

    //Write style for screen_15_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_15_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_15_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_15_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_15_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_15_img_8
    ui->screen_15_img_8 = lv_img_create(ui->screen_15);
    lv_obj_add_flag(ui->screen_15_img_8, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_15_img_8, &_fingerprint_006_alpha_48x48);
    lv_img_set_pivot(ui->screen_15_img_8, 50,50);
    lv_img_set_angle(ui->screen_15_img_8, 0);
    lv_obj_set_pos(ui->screen_15_img_8, 96, 184);
    lv_obj_set_size(ui->screen_15_img_8, 48, 48);

    //Write style for screen_15_img_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_15_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_15_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_15_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_15_img_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_15_img_9
    ui->screen_15_img_9 = lv_img_create(ui->screen_15);
    lv_obj_add_flag(ui->screen_15_img_9, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_15_img_9, &_fingerprint_006_alpha_48x48);
    lv_img_set_pivot(ui->screen_15_img_9, 50,50);
    lv_img_set_angle(ui->screen_15_img_9, 0);
    lv_obj_set_pos(ui->screen_15_img_9, 160, 184);
    lv_obj_set_size(ui->screen_15_img_9, 48, 48);

    //Write style for screen_15_img_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_15_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_15_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_15_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_15_img_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_15_line_1
    ui->screen_15_line_1 = lv_line_create(ui->screen_15);
    static lv_point_t screen_15_line_1[] = {{0, 0},{0, 180},};
    lv_line_set_points(ui->screen_15_line_1, screen_15_line_1, 2);
    lv_obj_set_pos(ui->screen_15_line_1, 88, 56);
    lv_obj_set_size(ui->screen_15_line_1, 1, 176);

    //Write style for screen_15_line_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->screen_15_line_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->screen_15_line_1, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->screen_15_line_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->screen_15_line_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_15_line_2
    ui->screen_15_line_2 = lv_line_create(ui->screen_15);
    static lv_point_t screen_15_line_2[] = {{0, 0},{0, 180},};
    lv_line_set_points(ui->screen_15_line_2, screen_15_line_2, 2);
    lv_obj_set_pos(ui->screen_15_line_2, 152, 56);
    lv_obj_set_size(ui->screen_15_line_2, 1, 176);

    //Write style for screen_15_line_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->screen_15_line_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->screen_15_line_2, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->screen_15_line_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->screen_15_line_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_15_line_3
    ui->screen_15_line_3 = lv_line_create(ui->screen_15);
    static lv_point_t screen_15_line_3[] = {{0, 0},{180, 0},};
    lv_line_set_points(ui->screen_15_line_3, screen_15_line_3, 2);
    lv_obj_set_pos(ui->screen_15_line_3, 32, 112);
    lv_obj_set_size(ui->screen_15_line_3, 176, 1);

    //Write style for screen_15_line_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->screen_15_line_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->screen_15_line_3, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->screen_15_line_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->screen_15_line_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_15_line_4
    ui->screen_15_line_4 = lv_line_create(ui->screen_15);
    static lv_point_t screen_15_line_4[] = {{0, 0},{180, 0},};
    lv_line_set_points(ui->screen_15_line_4, screen_15_line_4, 2);
    lv_obj_set_pos(ui->screen_15_line_4, 32, 176);
    lv_obj_set_size(ui->screen_15_line_4, 176, 1);

    //Write style for screen_15_line_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->screen_15_line_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->screen_15_line_4, lv_color_hex(0x757575), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->screen_15_line_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->screen_15_line_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_15.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_15);

    //Init events for screen.
    events_init_screen_15(ui);
}
