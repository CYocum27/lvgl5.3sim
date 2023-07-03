#include "lvgl/lvgl.h"
#include <stdint.h>
#include "lv_conf.h"
#include "lvgl\lv_core\lv_obj.h"
#include "lv_ex_conf.h"
#include "lvgl/lv_draw/lv_draw_img.h"
#include "images/init.c"
#include "images/background.c"
#include "screens.h"
#include "pagehandler.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
Page ID:
0 = Home
1 = Auton Selector
2 = Debug
*/

char currentauton[10] = "1";
int autonnumber = 1;

void clearScreen() {
    lv_obj_clean(lv_scr_act());
}
static lv_res_t backButtonAction(lv_obj_t* btn) {
    printf("Back button pressed\n");
    uint8_t id = lv_obj_get_free_num(btn);
    switch (id) {
    case 1:
        printf("Going to homepage\n");
        pageHandler(0);
        break;
    case 2:
        pageHandler(0);
        break;
    }

}
void addbackBtn(int currentpage) {
    //set style
    static lv_style_t style;
    lv_style_copy(&style, &lv_style_btn_rel);
    style.body.padding.hor = 10;
    style.body.padding.ver = 10;
    style.body.main_color = LV_COLOR_GRAY;
    style.body.grad_color = LV_COLOR_GRAY;
    //style2
    static lv_style_t style2;
    lv_style_copy(&style2, &lv_style_btn_rel);
    style2.body.padding.hor = 10;
    style2.body.padding.ver = 10;
    style2.body.main_color = LV_COLOR_SILVER;
    style2.body.grad_color = LV_COLOR_GRAY;
    lv_obj_t* back = lv_btn_create(lv_scr_act(), NULL);
    lv_cont_set_fit(back, true, true); /*Enable resizing h
    orizontally and vertically*/
    lv_obj_set_free_num(back, currentpage);   /*Set a unique number for the button*/
    lv_btn_set_action(back, LV_BTN_ACTION_CLICK, backButtonAction);
    lv_obj_t*label = lv_label_create(back, NULL);
    lv_label_set_text(label, "<-");
    lv_btn_set_style(back, LV_BTN_STYLE_REL ,&style);
    lv_btn_set_style(back, LV_BTN_STYLE_PR, &style2);
    lv_obj_set_style(label, &style);
    lv_obj_align(back, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
}
void initscreen() {
    lv_obj_t* image = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(image, &init);
}

void button_action_callback(lv_obj_t* btnm, const char* btn_text)
{
    strncpy(currentauton, btn_text, 10 - 1);
    currentauton[10 - 1] = '\0';  // Ensure null-termination
    autonnumber = atoi(currentauton);
    printf("\n");
}

void autonselector() {
    clearScreen(); //remove previous items on screen
    //add bg
    lv_obj_t* bg = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(bg, &background);
    //add back button
    addbackBtn(1);
    //add title
    lv_obj_t* title = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(title, "Autonomous Selector");
    lv_obj_align(title, NULL, LV_ALIGN_CENTER, 0, -105);
    lv_label_set_style(title, &lv_style_plain_color);
    //add toggles
    static lv_style_t style_bg;
    lv_style_copy(&style_bg, &lv_style_plain);
    style_bg.body.main_color = LV_COLOR_BLACK;
    style_bg.body.grad_color = LV_COLOR_BLACK;
    // Step 1: Create a button matrix object
    lv_obj_t* btnm = lv_btnm_create(lv_scr_act(), NULL);

    // Step 2: Set button labels
    static const char* btnm_map[] = { "1", "2","\n", "3","4", ""};
    lv_btnm_set_map(btnm, btnm_map);
    lv_btnm_set_toggle(btnm, true, autonnumber-1);
    // Step 3: Set button matrix styles
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BG, &lv_style_transp);
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_REL, &lv_style_btn_rel);
    lv_btnm_set_style(btnm, LV_BTNM_STYLE_BTN_PR, &lv_style_btn_pr);
    lv_obj_set_size(btnm, 250, 150);
    uint16_t btn_count = 4;

    // Set the map width to automatically resize the buttons based on the text length
    //for (uint16_t i = 0; i < btn_count; i++)
    {
        //const char* btn_text = lv_btnm_get_btn_text(btnm, i);
        //int16_t text_width = lv_obj_get_width(btn_text);
        //lv_btnm_set_map_width(btnm, i, text_width + 2 * LV_DPI / 10);  // Adjust the padding as needed
    }

    // Step 4: Set event callback
    lv_btnm_set_action(btnm, button_action_callback);

    // Step 5: Position the button matrix
    lv_obj_align(btnm, title, LV_ALIGN_CENTER, 0, 115);


}

void homescreenSelector(lv_obj_t* btn)
{
    uint8_t id = lv_obj_get_free_num(btn);
    switch (id) {
    case 1:
        pageHandler(1);
        break;
    case 2:
        pageHandler(2);
        break;
    }
}

void homescreen() {
    clearScreen(); //remove previous items on screen
    //add bg
    lv_obj_t* bg = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(bg, &background);
    //add title
    lv_obj_t* title = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(title, "Page Selector");
    lv_obj_align(title, NULL, LV_ALIGN_CENTER, 0, -105);
    lv_label_set_style(title, &lv_style_plain_color);
    //add page buttons
    lv_obj_t * autonpage = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_free_num(autonpage, 1);
    lv_cont_set_fit(autonpage, true, true);
    lv_obj_t* label = lv_label_create(autonpage, NULL);
    char label_text[100];
    sprintf(label_text, "Autonomous Selector: %s", currentauton);
    lv_label_set_text(label, label_text);
    lv_btn_set_action(autonpage,LV_BTN_ACTION_PR ,homescreenSelector);
    lv_obj_align(autonpage, NULL, LV_ALIGN_CENTER, 0, -lv_obj_get_height(autonpage)/2);
    //page2
    lv_obj_t* debugpage = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_free_num(debugpage, 2);
    lv_cont_set_fit(debugpage, true, true);
    lv_obj_t* debuglabel = lv_label_create(debugpage, NULL);
    lv_label_set_text(debuglabel, "Debug Screen");
    lv_btn_set_action(debugpage, LV_BTN_ACTION_PR, homescreenSelector);
    lv_obj_align(debugpage, NULL, LV_ALIGN_CENTER, 0, 5+lv_obj_get_height(autonpage) / 2);
}

void debugScreen() {
    clearScreen(); //remove previous items on screen
    //add bg
    lv_obj_t* bg = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(bg, &background);
    //add back button
    addbackBtn(2);
    //add title
    lv_obj_t* title = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(title, "Debug Screen");
    lv_obj_align(title, NULL, LV_ALIGN_CENTER, 0, -105);
    lv_label_set_style(title, &lv_style_plain_color);
}