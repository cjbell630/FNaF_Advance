#include "components/camera/cam_blip.h"
#include "images/backgrounds/effects/cam_blip.h"
#include "debug.h"
#include "tonc.h"
#include "graphics/frames/frames.h"
#include "sound/sound.h"
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
    REG_BG3CNT = BG_PRIO(LAYER_2) | BG_CBB(BLIP_CBB) | BG_SBB(BLIP_SBB) | BG_4BPP | BG_REG_32x32;
}

void cam_blip_load() {
    memcpy(&tile_mem[BLIP_CBB], &cam_blip_test2Tiles, cam_blip_test2TilesLen);
    memcpy(&pal_bg_bank[BLIP_PALBANK], &cam_blip_test2Pal, cam_blip_test2PalLen);
    dma3_cpy(&se_mem[BLIP_SBB], blip_frames[0]->screen_entry, 1280);
}

void cam_blip_update() {
    if (BLIP_TIMER >= 0) {
        const Frame* frame = blip_frames[BLIP_TIMER];
        //memset(&se_mem[BLIP_SBB], 0, 1280*8);
        //memset((SE *)0x0600CCC0, 0, 1280*8);
        dma3_cpy(&se_mem[BLIP_SBB], frame->screen_entry, 1280);
        REG_BG3VOFS = frame->vertical_offset;
        BLIP_TIMER--;
    }
}

void cam_blip_start() {
    BLIP_TIMER = blip_frames_len;
    Sound.play(SOUND_CAM_BLIP);
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
