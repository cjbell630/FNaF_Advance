//
// Created by cb106 on 1/21/2021.
//

#include "game.h"
#include "../include/tonc/toolbox.h"
#include "init.h"
#include "../include/DWedit/debug.h"
#include "../assets/images/backgrounds/office/office.h"
#include "../assets/images/backgrounds/newspaper/newspaper.h"
#include <string.h>

void init_game(int night) {
    vbaprint("loading now\n");

    //TODO: should load this into a buffer so it doesn't mess up

    // Load palette
    memcpy(pal_bg_mem, officePal, officePalLen);

    // Load tiles into CBB 0
    memcpy(&tile_mem[0][0], officeTiles, officeTilesLen);

    // Load map into SBB 30
    memcpy(&se_mem[24][0], officeMap, officeMapLen);

    //Show loading screen
    //TODO
    REG_BG0HOFS = 0;
    REG_BG0VOFS = 160;

    oam_init(OBJ_BUFFER, 128);
    int calc_night = night == 0 ? 1 : night; // ensures start positions and audio is loaded in for new game
    if (night == 0) {
        // load newspaper into memory
        // Load palette
        memcpy(&pal_bg_mem[16], newspaperPal, newspaperPalLen);

        // Load tiles into CBB 0
        memcpy(&tile_mem[3][0], newspaperTiles, newspaperTilesLen);

        // Load map into SBB 30
        memcpy(&se_mem[4][0], newspaperMap, newspaperMapLen);
    }

    //load night intro screen

    //load everything else
    int timer = 0;
    while (timer < 60) {
        vid_vsync();
        timer++;
    }
    vbaprint("done loading\n");
}

void start_game() {
    vbaprint("starting now\n");
    if (/*night==0*/1) {
        vbaprint("newspaper now\n");
        vid_vsync();
        //show newspaper
        REG_BG1HOFS = 0;
        REG_BG1VOFS = 0;
        REG_BG1CNT = BG_CBB(3) | BG_SBB(4) | BG_4BPP | BG_REG_32x32;
        REG_DISPCNT = DCNT_BG1 | DCNT_MODE0;
        int timer = 120;
        while(timer >=0) {
            vid_vsync();
            timer--;
        }
        //night++;
    }
    //show night intro screen
    //TODO

    //show office
    vbaprint("office now\n");
    REG_BG0CNT = BG_CBB(0) | BG_SBB(24) | BG_4BPP | BG_REG_32x32;
    REG_DISPCNT = DCNT_BG0 | DCNT_MODE0;
    REG_BG0VOFS = 0;


    const int SPEED_SCALE = 3;
    const int ART_WIDTH = 360;
    const int GBA_SCREEN_WIDTH = 240;
    const int RIGHT_CAP = ART_WIDTH - GBA_SCREEN_WIDTH; // 120
    int x = RIGHT_CAP / 2, y = 0;

    while (1) {
        vid_vsync();
        key_poll();

        //BACKGROUND
        x += SPEED_SCALE * key_tri_shoulder(); //move
        x = (x > RIGHT_CAP) ? RIGHT_CAP : // if too far right, fix
            (x < 0) ? 0 : // if too far left, fix
            x; // otherwise, don't change
        //y += key_tri_vert();

        REG_BG0HOFS = x;
        //REG_BG0VOFS = y;
    }
}
