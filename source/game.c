//
// Created by cb106 on 1/21/2021.
//

#include "game.h"
#include "../include/tonc/toolbox.h"
#include "init.h"
#include "../include/DWedit//debug.h"

void init_game(int night) {
    //vbaprint("loading now");
    //Show loading screen

    oam_init(OBJ_BUFFER, 128);
    int calc_night = night == 0 ? 1 : night; // ensures start positions and audio is loaded in for new game
    if (calc_night == 0) {
        // load newspaper into memory
    }
    //load night intro screen
    //load everything else
    int timer = 0;
    while(timer < 200){
        vid_vsync();
        timer++;
    }
}

void start_game() {
    //vbaprint("starting now");
    if (/*night==0*/1) {
        //show newspaper
        //night++;
    }
    //show night intro screen
}
