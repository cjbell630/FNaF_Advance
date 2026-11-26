#ifndef FNAF_ADVANCE_FRAMES_H
#define FNAF_ADVANCE_FRAMES_H

#include "tonc_types.h"

typedef struct Frame {
    u16* tiles;
    u16 tiles_length;
    COLOR* palette;
    u16 palette_length;
    SE* screen_entry;
    u16 screen_entry_length;
    u8 vertical_offset;
} Frame;


extern const Frame office_base_frame;
extern Frame empty_screen;

#endif //FNAF_ADVANCE_FRAMES_H
