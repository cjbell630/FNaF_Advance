#include "display.h"

#include <tonc_memdef.h>
#include <tonc_memmap.h>

void display_settings_main_menu() {
    REG_DISPCNT = DCNT_OBJ | DCNT_BG0 | DCNT_OBJ_1D | DCNT_MODE0;
}

void display_settings_still_cinematic() {
    REG_DISPCNT = DCNT_BG0 | DCNT_BG3 | DCNT_MODE0;
}

void display_settings_office() {
    REG_DISPCNT = DCNT_OBJ | DCNT_BG0 /*| DCNT_BG1*/ | DCNT_OBJ_1D | DCNT_MODE0;
}

void display_set_cams(bool stunned) {
    REG_DISPCNT = stunned
                      ? (DCNT_OBJ | /*DCNT_BG0 | DCNT_BG1 |*/ DCNT_BG3 | DCNT_OBJ_1D | DCNT_MODE0)
                      : (DCNT_OBJ | /*DCNT_BG0 |*/ DCNT_BG1 | DCNT_BG3 | DCNT_OBJ_1D | DCNT_MODE0);
}


struct DisplayWrapper Display = {
    .set_main_menu = &display_settings_main_menu,
    .set_still_cinematic = &display_settings_still_cinematic,
    .set_office = &display_settings_office,
    .set_cams = &display_set_cams
};
