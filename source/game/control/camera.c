//
// Created by cb106 on 1/22/2021.
//

#include <stdlib.h>
#include "camera.h"
#include "../graphics/bg_pal_handler.h"
#include "../../init.h"
#include "../../util/util.h"
#include "../../../include/tonclib/tonc.h"

#include "../../../assets/images/backgrounds/error/error.h"
#include "../../../assets/images/cams/stage_empty.h"
#include "../../../assets/images/cams/stage_bcf_s.h"

#include "../../../assets/images/cams/placeholder/b_placeholder.h"
#include "../../../assets/images/cams/placeholder/bcf_placeholder.h"
#include "../../../assets/images/cams/placeholder/bcff_placeholder.h"
#include "../../../assets/images/cams/placeholder/bf_placeholder.h"
#include "../../../assets/images/cams/placeholder/c_placeholder.h"
#include "../../../assets/images/cams/placeholder/cf_placeholder.h"
#include "../../../assets/images/cams/placeholder/fo_placeholder.h"
#include "../../../assets/images/cams/placeholder/fr_placeholder.h"
#include "../../../assets/images/cams/placeholder/empty_placeholder.h"

const int CAM_PB = 2;
const int CAM_CBB = 1;
const int CAM_SBB = 22;

int CAM_STAT = 0;
int CURR_CAM = 0;

const int CAM_SCROLL_BUFFER = 100;
const int CAM_SCROLL_DISP_RIGHT_CAP = 114;
const int CAM_SCROLL_SPEED = 1;

const int SUPPLY_CLOSET_NUMBER = 5;
const int KITCHEN_NUMBER = 9;

int CAM_MAP_ATTR0_VISIBLE = ATTR0_SQUARE | ATTR0_4BPP;

int internal_cam_scroll = 0;
int disp_cam_scroll = 0;
int cam_scroll_dir = -1;
OBJ_ATTR *cam_map;

CAM_DATA CAMS[11] = {
        {0b1110, 1}, //stage
        {0,      0}, //dining area
        {0,      0}, //pirate's cove
        {0,      0}, //west hall A
        {0,      0}, //west Hall B (Corner)
        {0,      0}, //supply closet
        {0,      0}, //east hall A
        {0,      0}, //east Hall B (Corner)
        {0,      0}, //backstage
        {0,      0}, //kitchen
        {0,      0}, //restrooms
};

void init_cams() {
    REG_BG1CNT = BG_PRIO(1) | BG_CBB(CAM_CBB) | BG_SBB(CAM_SBB) | BG_4BPP | BG_REG_64x64;
    cam_map = &OBJ_BUFFER[0];
    obj_set_attr(cam_map,
                 ATTR0_HIDE,
                 ATTR1_SIZE_64x64,                    // 16x16p,
                 ATTR2_PALBANK(0) | 0);        // palbank 0, tile 0
    //CAMS[0]->occupants = 0b1110;
}

CAM_DATA get_cam_data(int cam_num) {
    return CAMS[cam_num];
}

CAM_IMG_DATA get_cam_img_data(int cam_num) {
    CAM_DATA cd = get_cam_data(cam_num);
    return CAM_IMG_MAP[cam_num][cd.occupants][cd.special];
}

const CAM_IMG_DATA CAM_IMG_MAP[12][16][2] = {
        { /* STAGE (0) */
                { // Empty
                        { // Std
                                &stage_emptyTiles,      stage_emptyTilesLen,
                                &stage_emptyPal,       stage_emptyPalLen,
                                &stage_emptyMap,      stage_emptyMapLen
                        }
                },
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy Foxy*/},
                { /*Chica*/},
                { /*Chica Foxy*/},
                { //Chica Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &cf_placeholderPal, cf_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Chica Freddy Foxy*/},
                { /*Bonnie*/},
                { /*Bonnie Foxy*/},
                { // Bonnie Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &bf_placeholderPal, bf_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { // Bonnie Chica Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &bcf_placeholderPal, bcf_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        },
                        { // Spec
                                &stage_bcf_sTiles, stage_bcf_sTilesLen,
                                &stage_bcf_sPal, stage_bcf_sPalLen,
                                &stage_bcf_sMap, stage_bcf_sMapLen
                        },
                }
        },
        {/*Dining Area (1)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy Foxy*/},
                { //Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { //Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*Pirate's Cove (2)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { //Foxy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fo_placeholderPal, fo_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy*/ },
                { /*Freddy Foxy*/},
                { /*Chica*/},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { /*Bonnie*/},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*West Hall A (3)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { //Foxy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fo_placeholderPal, fo_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy*/ },
                { /*Freddy Foxy*/},
                { /*Chica*/},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { //Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*West Hall B (Corner) (4)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { /*Freddy*/ },
                { /*Freddy Foxy*/},
                { /*Chica*/},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { //Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*Supply Closet (5)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { /*Freddy*/ },
                { /*Freddy Foxy*/},
                { /*Chica*/},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { //Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*East Hall A (6)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy Foxy*/},
                { //Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { /*Bonnie*/},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*East Hall B (Corner) (7)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy Foxy*/},
                { //Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { /*Bonnie*/},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*Backstage (8)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { /*Freddy*/ },
                { /*Freddy Foxy*/},
                { /*Chica*/},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { //Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*Kitchen (9)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy Foxy*/},
                { //Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { /*Bonnie*/},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*Restrooms (10)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy Foxy*/},
                { //Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { /*Bonnie*/},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        }
};

void select_cam(int cam_num) {
    cam_num = logically_correct_modulus(cam_num, 11); // puts the value between 0 and 10 inclusive
    CAM_IMG_DATA cid = get_cam_img_data(cam_num);

    load_bg_pal(cid.cam_pal, cid.cam_pal_len, CAM_STAT ? 0 : CAM_PB);

    // Load tiles into CBB 0
    memcpy(&tile_mem[CAM_CBB][0], cid.cam_tiles, cid.cam_tiles_len);

    // Load map into SBB 30
    memcpy(&se_mem[CAM_SBB][0], cid.cam_map, cid.cam_map_len);

    //Swap pal of curr cam with new cam (green marker)
    COLOR temp = pal_obj_mem[CURR_CAM + 3];
    pal_obj_mem[CURR_CAM + 3] = pal_obj_mem[cam_num + 3];
    pal_obj_mem[cam_num + 3] = temp;

    CURR_CAM = cam_num;

    /*display funcs using:
    cid.cam_tiles;
    cid.cam_tiles_len;
    cid.cam_map;
    cid.cam_map_len;
    cid.cam_pal;
    cid.cam_pal_len;*/
}

void select_next_cam() {
    //TODO: won't work with map
    select_cam(CURR_CAM + 1);
}

void select_prev_cam() {
    //TODO: won't work with map
    select_cam(CURR_CAM - 1);
}

//TODO: could be macro
void set_cam_display(int on) {
    CAM_STAT = on;
    if (on) {
        set_bg_palbank(CAM_PB);
        REG_DISPCNT = DCNT_OBJ | DCNT_BG1 | DCNT_OBJ_1D |
                      DCNT_MODE0; //IMPORTANT: MUST BE IN ORDER OF BITS FROM LEFT TO RIGHT (this order)
        cam_map->attr0 = CAM_MAP_ATTR0_VISIBLE;
        obj_set_pos(cam_map, 176 /*screen width - map width*/, 96 /*screen height - map height*/);
        //TODO: shouldn't have to do this every time, but setting
    } else {
        set_bg_palbank(OFFICE_PB);
        REG_DISPCNT = DCNT_OBJ | DCNT_BG0 | DCNT_OBJ_1D |
                      DCNT_MODE0; //IMPORTANT: MUST BE IN ORDER OF BITS FROM LEFT TO RIGHT (this order)
        cam_map->attr0 |= ATTR0_HIDE;
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
    if (CAM_STAT) { // if cams are up
        if (CURR_CAM == SUPPLY_CLOSET_NUMBER || CURR_CAM == KITCHEN_NUMBER) { // if should not scroll
            REG_BG1HOFS = 0;
        } else { // if should scroll
            if (cam_scroll_dir == 1) { // moving right
                if (internal_cam_scroll > CAM_SCROLL_DISP_RIGHT_CAP + CAM_SCROLL_BUFFER) { // turning point
                    cam_scroll_dir = -1;
                } else if (disp_cam_scroll < CAM_SCROLL_DISP_RIGHT_CAP) { // move display
                    disp_cam_scroll += CAM_SCROLL_SPEED;
                }
            } else { //moving left
                if (internal_cam_scroll < -CAM_SCROLL_BUFFER) { // turning point
                    cam_scroll_dir = 1;
                } else if (disp_cam_scroll > 0) {
                    disp_cam_scroll -= CAM_SCROLL_SPEED;
                }
            }
            internal_cam_scroll += cam_scroll_dir * CAM_SCROLL_SPEED;
            update_cam_scroll_display();
        }
    }
}