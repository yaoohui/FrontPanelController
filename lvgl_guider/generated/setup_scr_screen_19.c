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



void setup_scr_screen_19(lv_ui *ui)
{
    //Write codes screen_19
    ui->screen_19 = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_19, 240, 240);
    lv_obj_set_scrollbar_mode(ui->screen_19, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_19, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_19, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_19_label_1
    ui->screen_19_label_1 = lv_label_create(ui->screen_19);
    lv_label_set_text(ui->screen_19_label_1, "Black screen");
    lv_label_set_long_mode(ui->screen_19_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_19_label_1, 24, 45);
    lv_obj_set_size(ui->screen_19_label_1, 120, 32);

    //Write style for screen_19_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_19_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_19_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_19_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_19_label_1, &lv_font_Acme_Regular_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_19_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_19_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_19_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_19_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_19_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_19_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_19_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_19_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_19_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_19_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_19_btn_2
    ui->screen_19_btn_2 = lv_btn_create(ui->screen_19);
    ui->screen_19_btn_2_label = lv_label_create(ui->screen_19_btn_2);
    lv_label_set_text(ui->screen_19_btn_2_label, "OK");
    lv_label_set_long_mode(ui->screen_19_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_19_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_19_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_19_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_19_btn_2, 16, 160);
    lv_obj_set_size(ui->screen_19_btn_2, 100, 50);

    //Write style for screen_19_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_19_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_19_btn_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_19_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_19_btn_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_19_btn_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_19_btn_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_19_btn_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_19_btn_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_19_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_19_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->screen_19_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->screen_19_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_19_btn_2, lv_color_hex(0x191717), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_19_btn_2, &lv_font_Acme_Regular_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_19_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_19_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_19_btn_1
    ui->screen_19_btn_1 = lv_btn_create(ui->screen_19);
    ui->screen_19_btn_1_label = lv_label_create(ui->screen_19_btn_1);
    lv_label_set_text(ui->screen_19_btn_1_label, "Cancel");
    lv_label_set_long_mode(ui->screen_19_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_19_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_19_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_19_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_19_btn_1, 125, 160);
    lv_obj_set_size(ui->screen_19_btn_1, 100, 50);

    //Write style for screen_19_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_19_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_19_btn_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_19_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_19_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_19_btn_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_19_btn_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_19_btn_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->screen_19_btn_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->screen_19_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->screen_19_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->screen_19_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->screen_19_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_19_btn_1, lv_color_hex(0x191717), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_19_btn_1, &lv_font_Acme_Regular_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_19_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_19_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_19_sw_1
    ui->screen_19_sw_1 = lv_switch_create(ui->screen_19);
    lv_obj_set_pos(ui->screen_19_sw_1, 163, 51);
    lv_obj_set_size(ui->screen_19_sw_1, 40, 20);

    //Write style for screen_19_sw_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_19_sw_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_19_sw_1, lv_color_hex(0xe6e2e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_19_sw_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_19_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_19_sw_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_19_sw_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_19_sw_1, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->screen_19_sw_1, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->screen_19_sw_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->screen_19_sw_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->screen_19_sw_1, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

    //Write style for screen_19_sw_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_19_sw_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_19_sw_1, lv_color_hex(0xffffff), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_19_sw_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_19_sw_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_19_sw_1, 10, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes screen_19_spinbox_1
    ui->screen_19_spinbox_1 = lv_spinbox_create(ui->screen_19);
    lv_obj_set_pos(ui->screen_19_spinbox_1, 83, 100);
    lv_obj_set_width(ui->screen_19_spinbox_1, 74);
    lv_obj_set_height(ui->screen_19_spinbox_1, 48);
    lv_spinbox_set_digit_format(ui->screen_19_spinbox_1, 2, 2);
    lv_spinbox_set_range(ui->screen_19_spinbox_1, -99, 99);
    lv_coord_t screen_19_spinbox_1_h = lv_obj_get_height(ui->screen_19_spinbox_1);
    ui->screen_19_spinbox_1_btn_plus = lv_btn_create(ui->screen_19);
    lv_obj_set_size(ui->screen_19_spinbox_1_btn_plus, screen_19_spinbox_1_h, screen_19_spinbox_1_h);
    lv_obj_align_to(ui->screen_19_spinbox_1_btn_plus, ui->screen_19_spinbox_1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_19_spinbox_1_btn_plus, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(ui->screen_19_spinbox_1_btn_plus, lv_screen_19_spinbox_1_increment_event_cb, LV_EVENT_ALL, NULL);
    ui->screen_19_spinbox_1_btn_minus = lv_btn_create(ui->screen_19);
    lv_obj_set_size(ui->screen_19_spinbox_1_btn_minus, screen_19_spinbox_1_h, screen_19_spinbox_1_h);
    lv_obj_align_to(ui->screen_19_spinbox_1_btn_minus, ui->screen_19_spinbox_1, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_19_spinbox_1_btn_minus, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(ui->screen_19_spinbox_1_btn_minus, lv_screen_19_spinbox_1_decrement_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->screen_19_spinbox_1, 83, 100);

    //Write style for screen_19_spinbox_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_19_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_19_spinbox_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_19_spinbox_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_19_spinbox_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_19_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_19_spinbox_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_19_spinbox_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_19_spinbox_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_19_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_19_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_19_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_19_spinbox_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_19_spinbox_1, &lv_font_Acme_Regular_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_19_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_19_spinbox_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_19_spinbox_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_19_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_19_spinbox_1, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_19_spinbox_1, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_19_spinbox_1, &lv_font_Acme_Regular_24, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_19_spinbox_1, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_19_spinbox_1, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_19_spinbox_1, lv_color_hex(0x2195f6), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_19_spinbox_1, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_19_spinbox_1_extra_btns_main_default
    static lv_style_t style_screen_19_spinbox_1_extra_btns_main_default;
    ui_init_style(&style_screen_19_spinbox_1_extra_btns_main_default);

    lv_style_set_text_color(&style_screen_19_spinbox_1_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_screen_19_spinbox_1_extra_btns_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_19_spinbox_1_extra_btns_main_default, 255);
    lv_style_set_bg_opa(&style_screen_19_spinbox_1_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_screen_19_spinbox_1_extra_btns_main_default, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_screen_19_spinbox_1_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_19_spinbox_1_extra_btns_main_default, 0);
    lv_style_set_radius(&style_screen_19_spinbox_1_extra_btns_main_default, 5);
    lv_style_set_shadow_width(&style_screen_19_spinbox_1_extra_btns_main_default, 0);
    lv_obj_add_style(ui->screen_19_spinbox_1_btn_plus, &style_screen_19_spinbox_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_19_spinbox_1_btn_minus, &style_screen_19_spinbox_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_19.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_19);

    //Init events for screen.
    events_init_screen_19(ui);
}
