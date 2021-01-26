//
// Created by cb106 on 1/22/2021.
//

#include "camera.h"
#include "../graphics/bg_pal_handler.h"
#include "../../init.h"
#include "../../../include/tonc/toolbox.h"

#include "../../../assets/images/backgrounds/error/error.h"
#include "../../../assets/images/cams/stage_empty.h"
#include "../../../assets/images/cams/stage_bcf_s.h"

const int CAM_PB = 2;
const int CAM_CBB = 2;
const int CAM_SBB = 30;

int CAM_STAT = 0;
int CURR_CAM = 0;

const int CAM_SCROLL_BUFFER = 100;
const int CAM_SCROLL_DISP_RIGHT_CAP = 114;
const int CAM_SCROLL_SPEED = 1;

const int SUPPLY_CLOSET_NUMBER = 5;

int internal_cam_scroll = 0;
int disp_cam_scroll = 0;
int cam_scroll_dir = -1;

CAM_DATA CAMS[16] = {
        {0, 1, 0}
};

void init_cams() {
    REG_BG1CNT = BG_CBB(CAM_CBB) | BG_SBB(CAM_SBB) | BG_4BPP | BG_REG_64x64;
    //CAMS[0]->occupants = 0b1110;
}

CAM_DATA get_cam_data(int cam_num) {
    return CAMS[cam_num];
}

CAM_IMG_DATA get_cam_img_data(int cam_num) {
    CAM_DATA cd = get_cam_data(cam_num);
    return CAM_IMG_MAP[cd.cam_num][cd.occupants][cd.special];
}

const CAM_IMG_DATA CAM_IMG_MAP[12][5][2] = {
        { /* STAGE (0) */
                { // Empty
                        { // Std
                                stage_emptyTiles, stage_emptyTilesLen,
                                stage_emptyPal, stage_emptyPalLen,
                                stage_emptyMap, stage_emptyMapLen
                        },
                        { // Spec
                                errorTiles, errorTilesLen,
                                errorPal, errorPalLen,
                                errorMap, errorMapLen
                        }
                }, { //Foxy

                           { // Std
                                   stage_bcf_sTiles, stage_bcf_sTilesLen,
                                   stage_bcf_sPal, stage_bcf_sPalLen,
                                   stage_bcf_sMap, stage_bcf_sMapLen
                           },

                           { // Spec
                                   stage_bcf_sTiles, stage_bcf_sTilesLen,
                                   stage_bcf_sPal, stage_bcf_sPalLen,
                                   stage_bcf_sMap, stage_bcf_sMapLen
                           }
                   }
        }
};

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

int are_cams_up() {
    return CAM_STAT;
}


void update_cam_scroll_display() {
    REG_BG1HOFS = disp_cam_scroll;
}

void scroll_cams() {
    //TODO: this code looks so cringe
    if (CAM_STAT && CURR_CAM != SUPPLY_CLOSET_NUMBER) {
        if (cam_scroll_dir == 1) { //moving right
            if (internal_cam_scroll > CAM_SCROLL_DISP_RIGHT_CAP + CAM_SCROLL_BUFFER) { // turning point
                cam_scroll_dir = -1;
            } else if (disp_cam_scroll < CAM_SCROLL_DISP_RIGHT_CAP) { // move display
                disp_cam_scroll += CAM_SCROLL_SPEED;
                update_cam_scroll_display();
            }
            internal_cam_scroll += CAM_SCROLL_SPEED;
        } else { //moving left
            if (internal_cam_scroll < -CAM_SCROLL_BUFFER) { // turning point
                cam_scroll_dir = 1;
            } else if (disp_cam_scroll > 0) {
                disp_cam_scroll -= CAM_SCROLL_SPEED;
                update_cam_scroll_display();
            }
            internal_cam_scroll -= CAM_SCROLL_SPEED;
        }
    }
}