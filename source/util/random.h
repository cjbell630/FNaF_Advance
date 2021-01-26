//
// From https://www.coranac.com/tonc/text/gfx.htm#cd-qran, tweaked to allow modification from key inputs
//

#ifndef FNAF_ADVANCE_RANDOM_H
#define FNAF_ADVANCE_RANDOM_H

#include "../../include/tonc/types.h"

int seed = 42;

INLINE void scramble_rng(int modifier) { // raw key value = 1023
    //1664 * 1000 ~= 1664525
    //1013904 * 1000 ~= 1013904223
    seed = 1664 * modifier * seed + (1013904 * modifier); //magic rng nums
    // return (seed >> 16) & 0x7FFF;
}

INLINE int rnd() {
    seed = 1664525 * seed + 1013904223; //magic rng nums
    return (seed >> 16) & 0x7FFF;
}

INLINE int random_max(int max) {
    return rnd() % max;
}


#endif //FNAF_ADVANCE_RANDOM_H
