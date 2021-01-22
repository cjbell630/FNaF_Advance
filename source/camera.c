//
// Created by cb106 on 1/22/2021.
//

#include "camera.h"
#include "screen_handler.h"
#include "init.h"
#include "../include/tonc/toolbox.h"

const int CAM_PB = 3;
const int CAM_CBB = 2;
const int CAM_SBB = 22;

int CAM_STAT = 0;

CAM_DATA *CAMS[16];

void init_cams() {
    REG_BG1CNT = BG_CBB(CAM_CBB) | BG_SBB(CAM_SBB) | BG_4BPP | BG_REG_64x64;
    CAMS[0]->occupants = 0;
    //CAMS[0]->occupants = 0b1110;
}

CAM_DATA get_cam_data(int cam_num) {
    return *CAMS[cam_num];
}

CAM_IMG_DATA get_cam_img_data(int cam_num) {
    CAM_DATA cd = get_cam_data(cam_num);
    return CAM_IMG_MAP[cd.cam_num][cd.occupants][cd.special];
}

void select_cam(int cam_num) {
    CAM_IMG_DATA cid = get_cam_img_data(cam_num);

    load_bg_pal(cid.cam_pal, cid.cam_pal_len, CAM_PB);

    // Load tiles into CBB 0
    memcpy(&tile_mem[CAM_CBB][0], cid.cam_tiles, cid.cam_tiles_len);

    // Load map into SBB 30
    memcpy(&se_mem[CAM_SBB][0], cid.cam_map, cid.cam_map_len);

    /*display funcs using:
    cid.cam_tiles;
    cid.cam_tiles_len;
    cid.cam_map;
    cid.cam_map_len;
    cid.cam_pal;
    cid.cam_pal_len;*/
}

//TODO: could be macro
void set_cam_display(int on) {
    CAM_STAT = on;
    if (on) {
        set_bg_palbank(CAM_PB);
        REG_DISPCNT = DCNT_BG1 | DCNT_MODE0; //IMPORTANT: MUST BE IN ORDER OF BITS FROM LEFT TO RIGHT (this order)
    } else {
        set_bg_palbank(OFFICE_PB);
        REG_DISPCNT = DCNT_BG0 | DCNT_MODE0; //IMPORTANT: MUST BE IN ORDER OF BITS FROM LEFT TO RIGHT (this order)
    }
}

void toggle_cam_display() {
    set_cam_display(!CAM_STAT);
}

int get_cam_status() {
    return CAM_STAT;
}