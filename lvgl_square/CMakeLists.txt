SET(SOURCES screens/ui_Screen1.c
    screens/ui_Screen2.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_power_005_png.c
    images/ui_img_right_003_png.c
    images/ui_img_fingerprint_006_png.c
    images/ui_img_left_003_png.c)

add_library(ui ${SOURCES})
