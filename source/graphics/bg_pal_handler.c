//#include "screen_handler.h"
#include "tonc.h"
#include "DWedit/debug.h"
#include <string.h>

int curr_bg_palbank = 0;

//cell 0-5 inclusive
/*void load_screen_tiles(unsigned short *tiles, int tilesLen, int charblock, int cell) {
    memcpy(&tile_mem[charblock][cell * 600], tiles, tilesLen);
}*/

// TODO remove
void load_bg_pal(const COLOR* pal, const int palLen, const int palbank) {
    memcpy(&pal_bg_mem[16 * palbank], pal, palLen);
}

void swap_bg_pal(const int pb0, const int pb1) {
    COLOR temp[32];

    const int color_index0 = 16 * pb0;
    const int color_index1 = 16 * pb1;
    //TODO: elarn how to do this better

    //mgba_printf("storing 0\n");

    //store first pallete
    memcpy(&temp, &pal_bg_mem[color_index0], 32);

    //mgba_printf("done storing 0\n");


    //mgba_printf("coping 0 to 1\n");
    //copy second to first location
    memcpy(&pal_bg_mem[color_index0], &pal_bg_mem[color_index1], 32);
    //mgba_printf("done coping 0 to 1\n");


    //mgba_printf("coping 1 to 0\n");
    //copy first to second location
    memcpy(&pal_bg_mem[color_index1], &temp[0], 32);

    //mgba_printf("done coping 1 to 0\n");

    //mgba_printf("-----------done swapping once------------\n");
}

void set_bg_palbank(const int palbank) {
    //mgba_printf(curr_bg_palbank == 0 ? "curr palbank is 0\n" : "not 0\n");

    //swap 0 and curr
    swap_bg_pal(0, curr_bg_palbank);

    //swap 0 and new
    swap_bg_pal(0, palbank);

    curr_bg_palbank = palbank;
}
