#include <stdlib.h>
#include "camera.h"
#include "game/graphics/bg_pal_handler.h"
#include "init.h"
#include "util/util.h"
#include "tonc.h"

#include "game/control/ai/ai.h"
#include "game/control/cameras/room_names.h"
#include "game/graphics/cam_img_map.h"

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
        {CAM_OCC_BONNIE | CAM_OCC_CHICA | CAM_OCC_FREDDY, CAM_SPEC_STD}, //stage
        {CAM_OCC_EMPTY, CAM_SPEC_STD}, //dining area
        {CAM_OCC_FOXY,  CAM_SPEC_STD}, //pirate's cove
        {CAM_OCC_EMPTY, CAM_SPEC_STD}, //west hall A
        {CAM_OCC_EMPTY, CAM_SPEC_STD}, //west Hall B (Corner)
        {CAM_OCC_EMPTY, CAM_SPEC_STD}, //supply closet
        {CAM_OCC_EMPTY, CAM_SPEC_STD}, //east hall A
        {CAM_OCC_EMPTY, CAM_SPEC_STD}, //east Hall B (Corner)
        {CAM_OCC_EMPTY, CAM_SPEC_STD}, //backstage
        {CAM_OCC_EMPTY, CAM_SPEC_STD}, //kitchen
        {CAM_OCC_EMPTY, CAM_SPEC_STD}, //restrooms
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

void select_cam(int cam_num) {
    cam_num = continuous_modulo(cam_num, 11); // puts the value between 0 and 10 inclusive
    CAM_DATA cd = get_cam_data(cam_num);
    CAM_IMG_DATA cid = get_cam_img_data(cam_num, Animatronics.get_room_occupants(cam_num), cd.special);

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

//TODO: remove
void select_next_cam() {
    //TODO: won't work with map
    select_cam(CURR_CAM + 1);
}

//TODO: remove
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
        if (SHOULD_PAN(CURR_CAM)) { // if should scroll
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
        } else { // if should not scroll
            REG_BG1HOFS = 0;
        }
    }
}