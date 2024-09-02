//
// Created by cb106 on 1/26/2021.
//

#include <string.h>
#include "static_handler.h"
#include "bg_pal_handler.h"
#include "util/random.h"
#include "images/backgrounds/static/static.h"
#include "tonc.h"

const int STATIC_OFFSET_MAX = 256;

const int STATIC_COLOR_COUNT = 32; //32 max, lower this number to reduce density

int STATIC_HOFS = 0;
int STATIC_VOFS = 0;


AFF_SRC_EX asx =
        {
                0 << 8, 0 << 8,           // Map coords.
                0, 0,                // Screen coords.
                0x0100, 0x0100, 0       // Scales and angle.
        };

BG_AFFINE bgaff;

void init_static() {
    memcpy(&tile_mem[3][0], staticTiles, staticTilesLen);
    memcpy(&se_mem[30][0], staticMap, staticMapLen);
    memcpy(&pal_bg_mem[240], &staticPal[240], STATIC_COLOR_COUNT);
    //load_bg_pal(staticPal, staticPalLen, 0);
}

void display_static() {

}

void update_static() {
    STATIC_HOFS = rnd_exclude(STATIC_OFFSET_MAX, STATIC_HOFS);
    STATIC_VOFS = rnd_exclude(STATIC_OFFSET_MAX, STATIC_VOFS);
    asx.scr_x = STATIC_HOFS;
    asx.scr_y = STATIC_VOFS;
    bg_rotscale_ex(&bgaff, &asx);
    REG_BG_AFFINE[2] = bgaff;
}