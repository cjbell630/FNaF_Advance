#include "frames.h"

unsigned short empty_frame[32 * 20] = {0};

Frame empty_screen = {
    .screen_entry_length = 1280,
    .vertical_offset = 0,
    .screen_entry = empty_frame
};
