#include "lvgl/lvgl.h"
#include <stdint.h>
#include "lv_conf.h"
#include "lvgl\lv_core\lv_obj.h"
#include "lv_ex_conf.h"
#include "lvgl/lv_draw/lv_draw_img.h"
#include "images/init.c"
#include "images/background.c"
#include "screens.h"

void clearScreen() {
    lv_obj_clean(lv_scr_act());
}

void initscreen() {
    lv_obj_t* image = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(image, &init);
}

void button_action_callback(lv_obj_t* btnm, const char* btn_text)
{
    printf(btn_text);
    printf("\n");
}

void autonselector() {
    clearScreen(); //remove previous items on screen
    //add bg
    lv_obj_t* bg = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(bg, &background);
    //add title
    lv_obj_t* title = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(title, "Autonomous Selector");
    lv_obj_align(title, NULL, LV_ALIGN_CENTER, 0, -105);
    lv_label_set_style(title, &lv_style_plain_color);
    //add toggles
    // Step 1: Create a button matrix object
    lv_obj_t* btnm = lv_btnm_create(lv_scr_act(), NULL);

    // Step 2: Set button labels
    static const char* btnm_map[] = { "1", "2","\n", "3","4", ""};
    lv_btnm_set_map(btnm, btnm_map);
    lv_btnm_set_toggle(btnm, true, 0);
    // Step 3: Set button matrix styles
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BG, &lv_style_plain_color);
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_REL, &lv_style_btn_rel);
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_PR, &lv_style_btn_pr);

    // Step 4: Set event callback
    lv_btnm_set_action(btnm, button_action_callback);

    // Step 5: Position the button matrix
    lv_obj_align(btnm, NULL, LV_ALIGN_CENTER, 0, 0);


}