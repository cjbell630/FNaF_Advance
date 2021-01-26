//
// Created by cb106 on 1/22/2021.
//

#ifndef FNAF_ADVANCE_BG_PAL_HANDLER_H
#define FNAF_ADVANCE_BG_PAL_HANDLER_H

#include "../../../include/tonc/toolbox.h"
#include "../../../include/DWedit/debug.h"
#include <string.h>


extern int curr_bg_palbank;

void load_bg_pal(COLOR *pal, int palLen, int palbank);

void swap_bg_pal(int pb0, int pb1);

void set_bg_palbank(int palbank);

#endif //FNAF_ADVANCE_BG_PAL_HANDLER_H
