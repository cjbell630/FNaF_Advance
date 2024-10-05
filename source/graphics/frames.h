#ifndef FNAF_ADVANCE_FRAMES_H
#define FNAF_ADVANCE_FRAMES_H

#include "tonc_types.h"

typedef struct Frame{
    TILE *tiles;
    u16 tiles_length;
    COLOR *palette;
    u16 palette_length;
    SE *screen_entry;
    u16 screen_entry_length;
    u8 vertical_offset;
} Frame;

#define blip_frames_len 10
/**
 * Frames for screen blip IN REVERSE ORDER
 */
extern struct Frame *blip_frames[10];
extern const Frame office_base_frame;
extern struct Frame empty_screen;

#endif //FNAF_ADVANCE_FRAMES_H
