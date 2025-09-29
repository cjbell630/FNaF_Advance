#include "cam_blip.h"
#include "images/effects/cam_blip_test.h"
#include "DWedit/debug.h"
#include "tonc.h"
#include "graphics/frames.h"
#include <string.h>

int BLIP_TIMER;

// TODO move to separate file
#define LAYER_0 3
#define LAYER_1 2
#define LAYER_2 1
#define LAYER_3 0
const int BLIP_CBB = 3;
const int BLIP_SBB = 25;
const u8 BLIP_PALBANK = 15;

void cam_blip_init() {
    REG_BG3CNT = BG_PRIO(LAYER_2) | BG_CBB(BLIP_CBB) | BG_SBB(BLIP_SBB) | BG_8BPP | BG_REG_32x32;
    // TODO 4BPP PB Blip palbank
}

void cam_blip_load() {
    memcpy(&tile_mem[BLIP_CBB], &cam_blip_testTiles, cam_blip_testTilesLen);
    // TODO memcpy(&pal_bg_bank[BLIP_PALBANK], &cam_blip_testPal, cam_blip_testPalLen);
}

void cam_blip_update() {
    if (BLIP_TIMER >= 0) {
        Frame *frame = blip_frames[BLIP_TIMER];
        //memset(&se_mem[BLIP_SBB], 0, 1280*8);
        //memset((SE *)0x0600CCC0, 0, 1280*8);
        dma3_cpy(&se_mem[BLIP_SBB], frame->screen_entry, 1280);
        REG_BG3VOFS = frame->vertical_offset;
        BLIP_TIMER--;
    }
}

void cam_blip_start() {
    BLIP_TIMER = blip_frames_len;
}

void cam_blip_reset() {
    BLIP_TIMER = 0;
}

struct CamBlipWrapper CamBlipEffect = {
    .init = &cam_blip_init,
    .load = &cam_blip_load,
    .update = &cam_blip_update,
    .start = &cam_blip_start,
    .reset = &cam_blip_reset
};