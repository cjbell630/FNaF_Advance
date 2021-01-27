//
// Created by cb106 on 1/25/2021.
//

#include "game_clock.h"
#include "../../../include/tonclib/tonc.h"
#include "../../util/random.h"
#include "camera.h"
#include "../graphics/static_handler.h"

const int FRAME_MAX = 130881600;

int frame = 0;

void init_clock() {
    frame = 0;
}

void tick() {
    frame %= FRAME_MAX;
    scroll_cams();
    update_static();
    if (frame % 2 == 0) { // every other frame
        scramble_rng(__key_curr);
    }
    frame++;
}
