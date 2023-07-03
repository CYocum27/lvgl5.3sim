#include "lvgl/lvgl.h"
#include <stdint.h>
#include "lv_conf.h"
#include "lvgl\lv_core\lv_obj.h"
#include "lv_ex_conf.h"
#include "lvgl/lv_draw/lv_draw_img.h"
#include "screens.h"
#include "pagehandler.h"

void pageHandler(int page) {
    switch (page){
        case 0:
        homescreen();
        break;
        case 1:
        autonselector();
        break;
        case 2:
        debugScreen();
        break;
    }
}

