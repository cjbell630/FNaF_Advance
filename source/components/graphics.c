#include <string.h>
#include "tonc.h"
#include "graphics.h"
#include "game/room_names.h"
#include "images/sprites/cam_map/cam_map.h"
#include "DWedit/debug.h"
#include "images/office/office_pal.h"
#include "images/office/office.h"
#include "graphics/cam_img_map.h"
#include "images/effects/cam_blip_test.h"
#include "graphics/frames.h"

int BLIP_TIMER;

/* BUFFERS */
// OBJ_ATTR OBJ_BUFFER[128];
/* END BUFFERS */

/* OBJECTS */
OBJ_ATTR *cam_map;

/* END OBJECTS */

/* CONSTANTS / DEFINITIONS */
// TODO make these better
#define CAM_MAP_SELECTED cam_mapPal[3];
#define CAM_MAP_UNSELECTED cam_mapPal[4];
const u16 CAM_MAP_ATTR0_VISIBLE = ATTR0_SQUARE | ATTR0_4BPP;

/*
const int OFFICE_PB = 0;
const int OFFICE_CBB = 0;
const int OFFICE_SBB = 20;

const int CAM_PB = 2;
const int CAM_CBB = 1;
const int CAM_SBB = 22;*/
const int MAIN_CBB = 0;
const int MAIN_SBB = 30;
const int BLIP_CBB = 3;
const int BLIP_SBB = 25;
const int MAP_TILE_START = 50;
#define LAYER_0 3
#define LAYER_1 2
#define LAYER_2 1
#define LAYER_3 0

/* END CONSTANTS / DEFINITIONS */

void show_static() {
    REG_BG2CNT = BG_PRIO(LAYER_3) | BG_CBB(3) | BG_SBB(30) | BG_WRAP | BG_AFF_16x16;
    REG_DISPCNT = DCNT_BG0 | DCNT_BG2 | DCNT_MODE1;
}

void init_objects() {
    /* FROM cams on night start */
    // TODO cam_map = &OBJ_BUFFER[0];
    //oam_init(oam_mem, 128);
    cam_map = &oam_mem[0];
    obj_set_attr(
            cam_map,
            ATTR0_HIDE,
            ATTR1_SIZE_64x64,                    // 16x16p,
            ATTR2_PALBANK(0) | ATTR2_ID(MAP_TILE_START) | ATTR2_PRIO(LAYER_1)
    ); // palbank 0, tile 0
    memcpy(&tile_mem[4][MAP_TILE_START], cam_mapTiles, cam_mapTilesLen);
    memcpy(&pal_obj_mem[0], cam_mapPal, cam_mapPalLen);
    /* END FROM cams on night start */

    /* EXTRA STUFF
     * This originally ran on at the end of every loop: oam_copy(oam_mem, OBJ_BUFFER, 128);
     * This originally ran on init: oam_init(OBJ_BUFFER, 128);
     * also, there was a buffer declaration at the top of game.c (see top of this file in buffers)
     * */
}

void init_backgrounds() {
    //unsigned short colors[2] = {0x0000, 0x7FFF,};
    memcpy(&tile_mem[BLIP_CBB], &cam_blip_testTiles, cam_blip_testTilesLen);
    //memcpy(&pal_bg_mem[0], &colors, 4);
    REG_BG3CNT = BG_PRIO(LAYER_2) | BG_CBB(BLIP_CBB) | BG_SBB(BLIP_SBB) | BG_8BPP | BG_REG_32x32;
    REG_BG3HOFS = 0;

    // TODO might need to reaffirm this in switching functions
    REG_BG0CNT = BG_PRIO(LAYER_0) | BG_CBB(MAIN_CBB) | BG_SBB(MAIN_SBB) | BG_8BPP | BG_REG_64x32;
    REG_BG1CNT = BG_PRIO(LAYER_1) | BG_CBB(MAIN_CBB) | BG_SBB(MAIN_SBB) | BG_8BPP | BG_REG_64x64;
}

void load_frame(Frame *frame, u16 cbb, u16 sbb) {
    dma3_cpy(&pal_bg_mem[0], frame->palette, frame->palette_length);

    // Load tiles into CBB 0
    dma3_cpy(&tile_mem[cbb][0], frame->tiles, frame->tiles_length);


    // Load map into SBB 30
    dma3_cpy(&se_mem[sbb][0], frame->screen_entry, frame->screen_entry_length);
}

void graphics_switch_to_cams() {
    cam_map->attr0 = ATTR0_REG | ATTR0_4BPP | ATTR0_SQUARE;
    obj_set_pos(cam_map, 176 /*screen width - map width*/, 96 /*screen height - map height*/);
    //TODO: shouldn't have to do this every time, but setting
    REG_DISPCNT = DCNT_OBJ | /*DCNT_BG0 |*/ DCNT_BG1 | DCNT_BG3 | DCNT_OBJ_1D | DCNT_MODE0;
    BLIP_TIMER = 0;
}

void graphics_switch_to_office() {
    /* HIDE OBJECTS */
    // TODO can I not just do this by hiding layers?
    cam_map->attr0 = ATTR0_HIDE;
    /* END HIDE OBJECTS */

    //show office
    //set_bg_palbank(OFFICE_PB);
    vbaprint("office now\n");
    load_frame(&office_frames[0][0], MAIN_CBB, MAIN_SBB);
    REG_DISPCNT = DCNT_OBJ | DCNT_BG0 /*| DCNT_BG1*/ | DCNT_BG3 | DCNT_OBJ_1D | DCNT_MODE0;


    //REG_BLDCNT = BLD_BUILD(BLD_BG0, BLD_BG1, BLD_OFF);
    //REG_BLDALPHA = BLDA_BUILD(0b01000, 0b01000);
}

void graphics_select_cam(enum RoomNames prev_room, enum RoomNames new_room) {
    //Swap pal of curr cam with new cam (green marker)
    /*
    COLOR temp = pal_obj_mem[prev_room + 3];
    pal_obj_mem[prev_room + 3] = pal_obj_mem[new_room + 3];
    pal_obj_mem[new_room + 3] = temp;*/
    pal_obj_mem[prev_room + 3] = CAM_MAP_UNSELECTED;
    pal_obj_mem[new_room + 3] = CAM_MAP_SELECTED;


    Frame cid = get_cam_img_data(new_room);

    // TODO previously this was
    // load_bg_pal(cid.cam_pal, cid.cam_pal_len, CAM_STAT ? 0 : CAM_PB);
    // implying calling it when the camera is not up could cause issues
    // so make sure this is ONLY called if the camera is up
    // also TODO wtf even is this 0 supposed to mean anyway
    // maybe it was meant to be used to like preload cams?
    // okay this is called at init with camnum=0
    // and for some reason if palbank is always 0 then the office pal is messed up, and
    // if palbank is always CAM_PB then the cam pals are messed up
    load_frame(&cid, MAIN_CBB, MAIN_SBB);
    BLIP_TIMER = blip_frames_len;
}

void graphics_on_room_visual_change(Frame *new_frame) {
    load_frame(new_frame, MAIN_CBB, MAIN_SBB);
}

void graphics_update_cam() {
    if (BLIP_TIMER >= 0) {
        Frame *frame = blip_frames[BLIP_TIMER];
        //memcpy(&se_mem[BLIP_SBB], empty_screen.screen_entry, 1280);
        memcpy(&se_mem[BLIP_SBB], frame->screen_entry, 1280);
        REG_BG3VOFS = frame->vertical_offset;
        BLIP_TIMER--;
    }
}

struct GraphicsWrapper Graphics = {
        .show_static = &show_static,
        .init_objects = &init_objects,
        .game_display_cams = &graphics_switch_to_cams,
        .game_display_office = &graphics_switch_to_office,
        .select_cam = &graphics_select_cam,
        .update_cam= &graphics_update_cam,
        .init_backgrounds = &init_backgrounds,
        .on_room_visual_change = &graphics_on_room_visual_change
};