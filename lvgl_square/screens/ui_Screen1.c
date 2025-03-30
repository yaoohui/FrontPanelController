// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: FC-ITX

#include "../ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Image2 = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_Image2, &ui_img_power_005_png);
    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image2, 0);
    lv_obj_set_y(ui_Image2, -20);
    lv_obj_set_align(ui_Image2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label1 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label1, 0);
    lv_obj_set_y(ui_Label1, 80);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "Power");
    lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0x808080), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label1, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Label1, lv_color_hex(0x0017FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_Label1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_Label1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_Label1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ImgButton1 = lv_imgbtn_create(ui_Screen1);
    lv_imgbtn_set_src(ui_ImgButton1, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_right_003_png, NULL);
    lv_imgbtn_set_src(ui_ImgButton1, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_right_003_png, NULL);
    lv_obj_set_width(ui_ImgButton1, 32);
    lv_obj_set_height(ui_ImgButton1, 32);
    lv_obj_set_x(ui_ImgButton1, 100);
    lv_obj_set_y(ui_ImgButton1, 0);
    lv_obj_set_align(ui_ImgButton1, LV_ALIGN_CENTER);

    lv_obj_add_event_cb(ui_ImgButton1, ui_event_ImgButton1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Screen1, ui_event_Screen1, LV_EVENT_ALL, NULL);

}
