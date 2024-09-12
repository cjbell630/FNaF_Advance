#ifndef FNAF_ADVANCE_FRAMES_H
#define FNAF_ADVANCE_FRAMES_H

#include "tonc_types.h"

typedef struct Frame{
    u16 length;
    u8 vertical_offset;
    SE *screen_entry;
} Frame;

#define blip_frames_len 10
/**
 * Frames for screen blip IN REVERSE ORDER
 */
extern struct Frame *blip_frames[10];
extern struct Frame empty_screen;

#endif //FNAF_ADVANCE_FRAMES_H
