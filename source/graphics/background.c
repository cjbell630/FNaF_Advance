#include "background.h"
#include "images/backgrounds/menu/menu.h"

#include <string.h>

#include "bg_pal_handler.h"
#include "tonc.h"
#include "images/backgrounds/newspaper/newspaper.h"



const int NEWSPAPER_PB = 1;
const int NEWSPAPER_CBB = 0;
const int NEWSPAPER_SBB = 28;
#define LAYER_0 3
#define LAYER_1 2
#define LAYER_2 1
#define LAYER_3 0

void background_settings_main_menu() {

    // Load palette
    memcpy(pal_bg_mem, menuPal, menuPalLen);

    // Load tiles into CBB 0
    memcpy(&tile_mem[0][0], menuTiles, menuTilesLen);

    // Load map into SBB 30
    memcpy(&se_mem[13][0], menuMap, menuMapLen);
    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;
    REG_BG0CNT = BG_PRIO(3) | BG_CBB(0) | BG_SBB(13) | BG_4BPP | BG_REG_64x64;
}

void background_settings_newspaper() {
    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0; // load newspaper into memory
    // Load palette
    load_bg_pal(newspaperPal, newspaperPalLen, NEWSPAPER_PB);
    set_bg_palbank(NEWSPAPER_PB);

    // Load tiles into CBB 0
    memcpy(&tile_mem[NEWSPAPER_CBB][0], newspaperTiles, newspaperTilesLen);

    // Load map into SBB 30
    memcpy(&se_mem[NEWSPAPER_SBB][0], newspaperMap, newspaperMapLen);
    REG_BG0CNT = BG_CBB(NEWSPAPER_CBB) | BG_SBB(NEWSPAPER_SBB) | BG_4BPP | BG_REG_32x32;
}

void background_settings_office() {
    REG_BG3HOFS = 0;
    // TODO might need to reaffirm this in switching functions
    REG_BG0CNT = BG_PRIO(LAYER_0) | BG_CBB(MAIN_CBB) | BG_SBB(MAIN_SBB) | BG_8BPP | BG_REG_64x32;
}

void background_set_cams() {
    REG_BG3HOFS = 0;
    // TODO might need to reaffirm this in switching functions
    REG_BG1CNT = BG_PRIO(LAYER_1) | BG_CBB(MAIN_CBB) | BG_SBB(MAIN_SBB) | BG_8BPP | BG_REG_64x64;
}

void background_set_menu_frame(int frame_num) {

}


void background_load_frame(const Frame* frame, const u16 cbb, const u16 sbb) {
    dma3_cpy(&pal_bg_mem[0], frame->palette, frame->palette_length);
    dma3_cpy(&tile_mem[cbb][0], frame->tiles, frame->tiles_length);
    dma3_cpy(&se_mem[sbb][0], frame->screen_entry, frame->screen_entry_length);
}



struct BackgroundWrapper Background = {
    .set_main_menu = &background_settings_main_menu,
    .set_newspaper = &background_settings_newspaper,
    .set_office = &background_settings_office,
    .set_cams = &background_set_cams,
    .load_frame = &background_load_frame
};