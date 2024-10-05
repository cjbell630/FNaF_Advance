#include "frames.h"
#include "images/effects/cam_blip_test.h"
#include "images/effects/cam_blip_maps.h"
#include "images/office/office.h"

unsigned short empty_frame[32 * 20] = {0};
Frame blip_frame_0 = {
        .screen_entry_length = cam_blip_0_len,
        .vertical_offset = cam_blip_0_vert_offset,
        .screen_entry = &cam_blip_0
};
Frame blip_frame_1 = {
        .screen_entry_length = cam_blip_1_len,
        .vertical_offset = cam_blip_1_vert_offset,
        .screen_entry = &cam_blip_1
};
Frame blip_frame_2 = {
        .screen_entry_length = cam_blip_2_len,
        .vertical_offset = cam_blip_2_vert_offset,
        .screen_entry = &cam_blip_2
};
Frame blip_frame_3 = {
        .screen_entry_length = cam_blip_3_len,
        .vertical_offset = cam_blip_3_vert_offset,
        .screen_entry = &cam_blip_3
};
Frame blip_frame_4 = {
        .screen_entry_length = cam_blip_4_len,
        .vertical_offset = cam_blip_4_vert_offset,
        .screen_entry = &cam_blip_4
};
Frame blip_frame_5 = {
        .screen_entry_length = cam_blip_5_len,
        .vertical_offset = cam_blip_5_vert_offset,
        .screen_entry = &cam_blip_5
};
Frame blip_frame_6 = {
        .screen_entry_length = cam_blip_6_len,
        .vertical_offset = cam_blip_6_vert_offset,
        .screen_entry = &cam_blip_6
};
Frame blip_frame_7 = {
        .screen_entry_length = cam_blip_7_len,
        .vertical_offset = cam_blip_7_vert_offset,
        .screen_entry = &cam_blip_7
};
Frame blip_frame_8 = {
        .screen_entry_length = cam_blip_8_len,
        .vertical_offset = cam_blip_8_vert_offset,
        .screen_entry = &cam_blip_8
};
Frame empty_screen = {
        .screen_entry_length = 1280,
        .vertical_offset = 0,
        .screen_entry = &empty_frame
};
struct Frame *blip_frames[10] = {
        &empty_screen, &blip_frame_8, &blip_frame_7, &blip_frame_6, &blip_frame_5,
        &blip_frame_4, &blip_frame_3, &blip_frame_2, &blip_frame_1, &blip_frame_0
};

const Frame office_base_frame = {
        &office_tiles, office_tiles_size,
        &office_palette, office_palette_size,
        &office_tilemap, office_tilemap_size
};