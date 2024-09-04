#include <stdlib.h>
#include "camera.h"
#include "game/graphics/bg_pal_handler.h"
#include "init.h"
#include "util/util.h"
#include "tonc.h"

#include "game/control/ai/ai.h"
#include "game/control/cameras/room_names.h"
#include "game/graphics/cam_img_map.h"
#include "spooky_effects.h"

const int CAM_PB = 2;
const int CAM_CBB = 1;
const int CAM_SBB = 22;

enum RoomNames CURR_CAM = ROOM_STAGE;

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

/**
 * Using this bc for some select_cam(0) this has to be called on init or everything breaks
 * TODO investigate later
 * but for now just making this
 * @param cam_num
 * @param cam_is_up
 */
void internal_select_cam(enum RoomNames room, bool cam_is_up) {

    room = continuous_modulo(room, NUM_ROOMS); // puts the value between 0 and 10 inclusive
    CAM_IMG_DATA cid = get_cam_img_data(room);

    // TODO previously this was
    // load_bg_pal(cid.cam_pal, cid.cam_pal_len, CAM_STAT ? 0 : CAM_PB);
    // implying calling it when the camera is not up could cause issues
    // so make sure this is ONLY called if the camera is up
    // also TODO wtf even is this 0 supposed to mean anyway
    // maybe it was meant to be used to like preload cams?
    // okay this is called at init with camnum=0
    // and for some reason if palbank is always 0 then the office pal is messed up, and
    // if palbank is always CAM_PB then the cam pals are messed up
    load_bg_pal(cid.cam_pal, cid.cam_pal_len, cam_is_up ? 0 : CAM_PB);

    // Load tiles into CBB 0
    memcpy(&tile_mem[CAM_CBB][0], cid.cam_tiles, cid.cam_tiles_len);

    // Load map into SBB 30
    memcpy(&se_mem[CAM_SBB][0], cid.cam_map, cid.cam_map_len);

    //Swap pal of curr cam with new cam (green marker)
    COLOR temp = pal_obj_mem[CURR_CAM + 3];
    pal_obj_mem[CURR_CAM + 3] = pal_obj_mem[room + 3];
    pal_obj_mem[room + 3] = temp;

    CURR_CAM = room;

    /*display funcs using:
    cid.cam_tiles;
    cid.cam_tiles_len;
    cid.cam_map;
    cid.cam_map_len;
    cid.cam_pal;
    cid.cam_pal_len;*/
}


void init_cams() {
    REG_BG1CNT = BG_PRIO(1) | BG_CBB(CAM_CBB) | BG_SBB(CAM_SBB) | BG_4BPP | BG_REG_64x64;
    cam_map = &OBJ_BUFFER[0];
    obj_set_attr(cam_map,
                 ATTR0_HIDE,
                 ATTR1_SIZE_64x64,                    // 16x16p,
                 ATTR2_PALBANK(0) | 0);        // palbank 0, tile 0
    //CAMS[0]->occupants = 0b1110;
    internal_select_cam(ROOM_STAGE, false); // TODO remove (see internalselectcam)
    set_cam_display(false);
}

void select_cam(enum RoomNames room) {
    internal_select_cam(room, true);
}


//TODO: could be macro
void set_cam_display(bool on) {
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

/**
 *
 */
void update_cam_pan() {
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
        REG_BG1HOFS = disp_cam_scroll;
    } else { // if should not scroll
        REG_BG1HOFS = 0;
    }
}