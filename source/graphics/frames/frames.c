#include "frames.h"
#include "images/backgrounds/office/office.h"

unsigned short empty_frame[32 * 20] = {0};

Frame empty_screen = {
    .screen_entry_length = 1280,
    .vertical_offset = 0,
    .screen_entry = empty_frame
};

const Frame office_base_frame = {
    office_tiles, office_tiles_size,
    office_palette, office_palette_size,
    office_tilemap, office_tilemap_size
};
