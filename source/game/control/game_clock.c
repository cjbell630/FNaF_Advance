//
// Created by cb106 on 1/25/2021.
//

#include "game_clock.h"
#include "../../util/random.h"
#include "../../../include/tonc/input.h"

const int FRAME_MAX = 130881600;

int frame = 0;

void init_clock() {
    frame = 0;
}

void tick() {
    frame %= FRAME_MAX;
    if (frame % 2 == 0) { // every other frame
        scramble_rng(__key_curr);
    }
    frame++;
}
