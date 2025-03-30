/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

#include "custom.h"

bool From_Power_Flag = false;
bool From_Reset_Flag = false;
bool psw_res = false;
bool From_Fingerprint_Flag = false;
char new_psw1[8];
char new_psw2[8];
bool FP_Touched_Flag[9] = {false, false, false, false, false, false, false, false, false};
bool FP_HAVE_Flag[9] = {false, false, false, false, false, false, false, false, false};

static void screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {

        break;
    }
    default:
        break;
    }
}

static void screen_img_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        From_Power_Flag = true;
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_9, guider_ui.screen_9_del, &guider_ui.screen_del, setup_scr_screen_9, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, false, true);
        break;
    }
    case LV_EVENT_RELEASED:
    {
        touch_IRQ_Reset();
        break;
    }
    default:
        break;
    }
}

static void screen_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_1, guider_ui.screen_1_del, &guider_ui.screen_del, setup_scr_screen_1, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen, screen_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_img_1, screen_img_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_imgbtn_1, screen_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_1_imgbtn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen_1_del, setup_scr_screen, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_1_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_2, guider_ui.screen_2_del, &guider_ui.screen_1_del, setup_scr_screen_2, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_1 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_1_imgbtn_2, screen_1_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_1_imgbtn_1, screen_1_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START:
    {
        Pwr_Std_Init(&guider_ui);
        break;
    }
    default:
        break;
    }
}

static void screen_2_img_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        if (pwr_flag) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_8, guider_ui.screen_8_del, &guider_ui.screen_2_del, setup_scr_screen_8, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, false, true);
        }
        break;
    }
    case LV_EVENT_RELEASED:
    {
        touch_IRQ_Reset();
        break;
    }
    default:
        break;
    }
}

static void screen_2_imgbtn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_1, guider_ui.screen_1_del, &guider_ui.screen_2_del, setup_scr_screen_1, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_2_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_3, guider_ui.screen_3_del, &guider_ui.screen_2_del, setup_scr_screen_3, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_2 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_2, screen_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_2_img_1, screen_2_img_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_2_imgbtn_2, screen_2_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_2_imgbtn_1, screen_2_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_3_img_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_11, guider_ui.screen_11_del, &guider_ui.screen_3_del, setup_scr_screen_11, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_3_imgbtn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_2, guider_ui.screen_2_del, &guider_ui.screen_3_del, setup_scr_screen_2, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_3_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_4, guider_ui.screen_4_del, &guider_ui.screen_3_del, setup_scr_screen_4, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_3 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_3_img_1, screen_3_img_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_3_imgbtn_2, screen_3_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_3_imgbtn_1, screen_3_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_4_imgbtn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_3, guider_ui.screen_3_del, &guider_ui.screen_4_del, setup_scr_screen_3, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_4_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_5, guider_ui.screen_5_del, &guider_ui.screen_4_del, setup_scr_screen_5, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_4 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_4_imgbtn_2, screen_4_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_4_imgbtn_1, screen_4_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_5_imgbtn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_4, guider_ui.screen_4_del, &guider_ui.screen_5_del, setup_scr_screen_4, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_5_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_6, guider_ui.screen_6_del, &guider_ui.screen_5_del, setup_scr_screen_6, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_5 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_5_imgbtn_2, screen_5_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_5_imgbtn_1, screen_5_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_6_imgbtn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_5, guider_ui.screen_5_del, &guider_ui.screen_6_del, setup_scr_screen_5, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_6_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_7, guider_ui.screen_7_del, &guider_ui.screen_6_del, setup_scr_screen_7, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_6 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_6_imgbtn_2, screen_6_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_6_imgbtn_1, screen_6_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_7_imgbtn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_RELEASED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_6, guider_ui.screen_6_del, &guider_ui.screen_7_del, setup_scr_screen_6, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_7 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_7_imgbtn_2, screen_7_imgbtn_2_event_handler, LV_EVENT_ALL, ui);
}

static void screen_8_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_9, guider_ui.screen_9_del, &guider_ui.screen_8_del, setup_scr_screen_9, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 200, false, true);
        From_Reset_Flag = true;

        break;
    }
    default:
        break;
    }
}

static void screen_8_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_2, guider_ui.screen_2_del, &guider_ui.screen_8_del, setup_scr_screen_2, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_8 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_8_btn_1, screen_8_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_8_btn_2, screen_8_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void screen_9_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        if (From_Power_Flag) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen_9_del, setup_scr_screen, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 200, false, true);
            From_Power_Flag = false;
        } else if (From_Reset_Flag) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_2, guider_ui.screen_2_del, &guider_ui.screen_9_del, setup_scr_screen_2, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
            From_Reset_Flag = false;
        } else if (From_Fingerprint_Flag) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_11, guider_ui.screen_11_del, &guider_ui.screen_9_del, setup_scr_screen_11, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 200, false, true);
            From_Fingerprint_Flag = false;
        }
        break;
    }
    default:
        break;
    }
}

static void screen_9_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        const char *psw = lv_textarea_get_text(guider_ui.screen_9_ta_1);

        psw_res = Comp_psw((char*)psw);
        if (From_Power_Flag && psw_res) {
            Power_On_Off();
            From_Power_Flag = false;
            ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen_9_del, setup_scr_screen, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 500, false, true);
        } else if (From_Reset_Flag && psw_res) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_2, guider_ui.screen_2_del, &guider_ui.screen_9_del, setup_scr_screen_2, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
            HW_Reset();
            From_Reset_Flag = false;
        } else if (From_Fingerprint_Flag && psw_res) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_15, guider_ui.screen_15_del, &guider_ui.screen_9_del, setup_scr_screen_15, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
            From_Fingerprint_Flag = false;
        } else {
            Psw_Msgbox();
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen_9 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_9_btn_2, screen_9_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_9_btn_1, screen_9_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_10_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_11, guider_ui.screen_11_del, &guider_ui.screen_10_del, setup_scr_screen_11, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_10_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        const char *psw = lv_textarea_get_text(guider_ui.screen_10_ta_1);

        psw_res = Comp_psw((char*)psw);
        if (psw_res) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_13, guider_ui.screen_13_del, &guider_ui.screen_10_del, setup_scr_screen_13, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        } else {
            Psw_Msgbox();
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen_10 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_10_btn_2, screen_10_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_10_btn_1, screen_10_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_11_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_3, guider_ui.screen_3_del, &guider_ui.screen_11_del, setup_scr_screen_3, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_11_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_10, guider_ui.screen_10_del, &guider_ui.screen_11_del, setup_scr_screen_10, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_11_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_9, guider_ui.screen_9_del, &guider_ui.screen_11_del, setup_scr_screen_9, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        From_Fingerprint_Flag = true;
        break;
    }
    default:
        break;
    }
}

static void screen_11_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_20, guider_ui.screen_20_del, &guider_ui.screen_11_del, setup_scr_screen_20, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_11 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_11_imgbtn_1, screen_11_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_11_btn_1, screen_11_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_11_btn_2, screen_11_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_11_btn_3, screen_11_btn_3_event_handler, LV_EVENT_ALL, ui);
}

static void screen_12_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_13, guider_ui.screen_13_del, &guider_ui.screen_12_del, setup_scr_screen_13, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_12_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_11, guider_ui.screen_11_del, &guider_ui.screen_12_del, setup_scr_screen_11, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_12 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_12_btn_2, screen_12_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_12_btn_1, screen_12_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_13_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        memset(new_psw1, 0, sizeof(new_psw1));
        const char* temp = lv_textarea_get_text(guider_ui.screen_13_ta_1);
        memcpy(new_psw1, temp, strlen(temp));

        bool psw1_flag = false;

        if(strlen(new_psw1) != 6)
        {
            Invalid_Psw_Msgbox();
        }
        else
        {
            psw1_flag = true;
        }

        if (psw1_flag) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_14, guider_ui.screen_14_del, &guider_ui.screen_13_del, setup_scr_screen_14, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        }
        break;
    }
    default:
        break;
    }
}

static void screen_13_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_11, guider_ui.screen_11_del, &guider_ui.screen_13_del, setup_scr_screen_11, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_13 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_13_btn_2, screen_13_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_13_btn_1, screen_13_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_14_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        bool next_screen = false;

        memset(new_psw2, 0, sizeof(new_psw2));
        const char* temp = lv_textarea_get_text(guider_ui.screen_14_ta_1);
        memcpy(new_psw2, temp, strlen(temp));

        if(strlen(new_psw2) != 6)
        {
            Invalid_Psw_Msgbox();
        }
        else if(strcmp(new_psw1, new_psw2))
        {
            New_Psw_Msgbox();
        }
        else
        {
#ifdef USE_HARDWARE
            AT24C02_write(0, (uint8_t*)new_psw2, 7);
            memcpy(password, temp, strlen(temp));
#endif
            next_screen = true;
        }
        if (next_screen) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_11, guider_ui.screen_11_del, &guider_ui.screen_14_del, setup_scr_screen_11, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        }
        break;
    }
    default:
        break;
    }
}

static void screen_14_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_11, guider_ui.screen_11_del, &guider_ui.screen_14_del, setup_scr_screen_11, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_14 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_14_btn_2, screen_14_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_14_btn_1, screen_14_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_15_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START:
    {
        Touch_Img_Init(&guider_ui);
        break;
    }
    default:
        break;
    }
}

static void screen_15_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_11, guider_ui.screen_11_del, &guider_ui.screen_15_del, setup_scr_screen_11, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_15_img_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        FP_Num = 0;
        if (FP_HAVE_Flag[FP_Num]) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_16, guider_ui.screen_16_del, &guider_ui.screen_15_del, setup_scr_screen_16, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        } else {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_17, guider_ui.screen_17_del, &guider_ui.screen_15_del, setup_scr_screen_17, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        }
        break;
    }
    default:
        break;
    }
}

static void screen_15_img_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        FP_Num = 1;
        if (FP_HAVE_Flag[FP_Num]) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_16, guider_ui.screen_16_del, &guider_ui.screen_15_del, setup_scr_screen_16, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        } else {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_17, guider_ui.screen_17_del, &guider_ui.screen_15_del, setup_scr_screen_17, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        }
        break;
    }
    default:
        break;
    }
}

static void screen_15_img_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        FP_Num = 2;
        if (FP_HAVE_Flag[FP_Num]) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_16, guider_ui.screen_16_del, &guider_ui.screen_15_del, setup_scr_screen_16, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        } else {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_17, guider_ui.screen_17_del, &guider_ui.screen_15_del, setup_scr_screen_17, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        }
        break;
    }
    default:
        break;
    }
}

static void screen_15_img_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        FP_Num = 3;
        if (FP_HAVE_Flag[FP_Num]) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_16, guider_ui.screen_16_del, &guider_ui.screen_15_del, setup_scr_screen_16, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        } else {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_17, guider_ui.screen_17_del, &guider_ui.screen_15_del, setup_scr_screen_17, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        }
        break;
    }
    default:
        break;
    }
}

static void screen_15_img_5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        FP_Num = 4;
        if (FP_HAVE_Flag[FP_Num]) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_16, guider_ui.screen_16_del, &guider_ui.screen_15_del, setup_scr_screen_16, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        } else {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_17, guider_ui.screen_17_del, &guider_ui.screen_15_del, setup_scr_screen_17, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        }
        break;
    }
    default:
        break;
    }
}

static void screen_15_img_6_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        FP_Num = 5;
        if (FP_HAVE_Flag[FP_Num]) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_16, guider_ui.screen_16_del, &guider_ui.screen_15_del, setup_scr_screen_16, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        } else {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_17, guider_ui.screen_17_del, &guider_ui.screen_15_del, setup_scr_screen_17, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        }
        break;
    }
    default:
        break;
    }
}

static void screen_15_img_7_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        FP_Num = 6;
        if (FP_HAVE_Flag[FP_Num]) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_16, guider_ui.screen_16_del, &guider_ui.screen_15_del, setup_scr_screen_16, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        } else {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_17, guider_ui.screen_17_del, &guider_ui.screen_15_del, setup_scr_screen_17, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        }
        break;
    }
    default:
        break;
    }
}

static void screen_15_img_8_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        FP_Num = 7;
        if (FP_HAVE_Flag[FP_Num]) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_16, guider_ui.screen_16_del, &guider_ui.screen_15_del, setup_scr_screen_16, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        } else {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_17, guider_ui.screen_17_del, &guider_ui.screen_15_del, setup_scr_screen_17, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        }
        break;
    }
    default:
        break;
    }
}

static void screen_15_img_9_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        FP_Num = 8;
        if (FP_HAVE_Flag[FP_Num]) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_16, guider_ui.screen_16_del, &guider_ui.screen_15_del, setup_scr_screen_16, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        } else {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_17, guider_ui.screen_17_del, &guider_ui.screen_15_del, setup_scr_screen_17, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        }
        break;
    }
    default:
        break;
    }
}

void events_init_screen_15 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_15, screen_15_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_15_imgbtn_1, screen_15_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_15_img_1, screen_15_img_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_15_img_2, screen_15_img_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_15_img_3, screen_15_img_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_15_img_4, screen_15_img_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_15_img_5, screen_15_img_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_15_img_6, screen_15_img_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_15_img_7, screen_15_img_7_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_15_img_8, screen_15_img_8_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_15_img_9, screen_15_img_9_event_handler, LV_EVENT_ALL, ui);
}

static void screen_16_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        bool Deleted_Flag = false;

#ifdef USE_HARDWARE


        if(Fingerprint_DeleteOne(FP_Num) == 0)
        {
            Deleted_Flag = true;

            FP_HAVE_Flag[FP_Num] = false;
            FP_Touched_Flag[FP_Num] = false;
        }
        else
        {
            Delete_failed_Msgbox();
        }


#endif
        if (Deleted_Flag) {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_15, guider_ui.screen_15_del, &guider_ui.screen_16_del, setup_scr_screen_15, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
            Deleted_Flag = false;
        }
        break;
    }
    default:
        break;
    }
}

static void screen_16_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_15, guider_ui.screen_15_del, &guider_ui.screen_16_del, setup_scr_screen_15, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_16 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_16_btn_2, screen_16_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_16_btn_1, screen_16_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_17_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_15, guider_ui.screen_15_del, &guider_ui.screen_17_del, setup_scr_screen_15, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        FP_Reg_Times = 0;
        Wait_For_Finger_Flag = false;
        Wait_For_Lift_Flag = false;
        Fingerprint_Register_Flag = false;

        break;
    }
    default:
        break;
    }
}

static void screen_17_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_add_flag(guider_ui.screen_17_btn_1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(guider_ui.screen_17_btn_2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.screen_17_btn_3, LV_OBJ_FLAG_HIDDEN);
        Fingerprint_Register_Flag = true;
        Wait_For_Finger_Flag = true;
        FP_Reg_Times = 0;
        break;
    }
    default:
        break;
    }
}

static void screen_17_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_15, guider_ui.screen_15_del, &guider_ui.screen_17_del, setup_scr_screen_15, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_17 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_17_btn_3, screen_17_btn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_17_btn_2, screen_17_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_17_btn_1, screen_17_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_18_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START:
    {
        Screensaver_Init(&guider_ui);
        break;
    }
    default:
        break;
    }
}

static void screen_18_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        uint8_t temp[2] = {0, 0};

        temp[0] = lv_obj_has_state(guider_ui.screen_18_sw_1, LV_STATE_CHECKED);
        temp[1] = lv_spinbox_get_value(guider_ui.screen_18_spinbox_1);

#ifdef USE_HARDWARE

        AT24C02_write(11, temp, 2);
        screensaver_mode = temp[0];
        screensaver_delay = temp[1];

#endif
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_20, guider_ui.screen_20_del, &guider_ui.screen_18_del, setup_scr_screen_20, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_18_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_20, guider_ui.screen_20_del, &guider_ui.screen_18_del, setup_scr_screen_20, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_18 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_18, screen_18_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_18_btn_2, screen_18_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_18_btn_1, screen_18_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_19_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOAD_START:
    {
        Black_Screen_Init(&guider_ui);
        break;
    }
    default:
        break;
    }
}

static void screen_19_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        uint8_t temp[2] = {0, 0};

        temp[0] = lv_obj_has_state(guider_ui.screen_19_sw_1, LV_STATE_CHECKED);
        temp[1] = lv_spinbox_get_value(guider_ui.screen_19_spinbox_1);

#ifdef USE_HARDWARE

        AT24C02_write(9, temp, 2);
        black_screen_mode = temp[0];
        black_screen_delay = temp[1];

#endif
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_20, guider_ui.screen_20_del, &guider_ui.screen_19_del, setup_scr_screen_20, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_19_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_20, guider_ui.screen_20_del, &guider_ui.screen_19_del, setup_scr_screen_20, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_19 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_19, screen_19_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_19_btn_2, screen_19_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_19_btn_1, screen_19_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void screen_20_imgbtn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_11, guider_ui.screen_11_del, &guider_ui.screen_20_del, setup_scr_screen_11, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_20_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_19, guider_ui.screen_19_del, &guider_ui.screen_20_del, setup_scr_screen_19, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_20_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_18, guider_ui.screen_18_del, &guider_ui.screen_20_del, setup_scr_screen_18, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_20 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_20_imgbtn_1, screen_20_imgbtn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_20_btn_1, screen_20_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_20_btn_2, screen_20_btn_2_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
