//
// From https://www.coranac.com/tonc/text/gfx.htm#cd-qran, tweaked to allow modification from key inputs
//

#include <stdlib.h>
#include "../../include/tonc/types.h"

int rng_seed = 42;

void scramble_rng(int modifier) { // raw key value = 1023
    //1664 * 1000 ~= 1664525
    //1013904 * 1000 ~= 1013904223
    rng_seed = 1664 */* modifier */ rng_seed + (1013904 + rand()*modifier); //magic rng nums
    // return (seed >> 16) & 0x7FFF;
}

int rnd() {
    rng_seed = 1664525 * rng_seed + 1013904223; //magic rng nums
    return (rng_seed >> 16) & 0x7FFF;
}

int rnd_max(int max) {
    return rnd() % max;
}