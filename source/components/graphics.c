#include <string.h>
#include "tonc.h"
#include "graphics.h"
#include "game/room_names.h"
#include "images/sprites/cam_map/cam_map.h"
#include "images/effects/cam_blip_test.h"
#include "DWedit/debug.h"
#include "images/effects/cam_blip_maps.h"
#include "images/office/office_pal.h"
#include "images/office/office.h"
#include "graphics/cam_img_map.h"

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
const int MAIN_SBB = 20;

/* END CONSTANTS / DEFINITIONS */

void show_static() {
    REG_BG2CNT = BG_PRIO(0) | BG_CBB(3) | BG_SBB(30) | BG_WRAP | BG_AFF_16x16;
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
            ATTR2_PALBANK(0) | ATTR2_PRIO(2)
    ); // palbank 0, tile 0
    memcpy(&tile_mem[4][0], cam_mapTiles, cam_mapTilesLen);
    memcpy(&pal_obj_mem[0], cam_mapPal, cam_mapPalLen);
    /* END FROM cams on night start */

    /* EXTRA STUFF
     * This originally ran on at the end of every loop: oam_copy(oam_mem, OBJ_BUFFER, 128);
     * This originally ran on init: oam_init(OBJ_BUFFER, 128);
     * also, there was a buffer declaration at the top of game.c (see top of this file in buffers)
     * */
}

void init_backgrounds() {
    // TODO might need to reaffirm this in switching functions
    REG_BG0CNT = BG_PRIO(3) | BG_CBB(MAIN_CBB) | BG_SBB(MAIN_SBB) | BG_8BPP | BG_REG_64x32;
    REG_BG1CNT = BG_PRIO(2) | BG_CBB(MAIN_CBB) | BG_SBB(MAIN_SBB) | BG_8BPP | BG_REG_64x64;
}

void graphics_switch_to_cams() {
    cam_map->attr0 = ATTR0_REG | ATTR0_4BPP | ATTR0_SQUARE;
    obj_set_pos(cam_map, 176 /*screen width - map width*/, 96 /*screen height - map height*/);
    //TODO: shouldn't have to do this every time, but setting
    REG_DISPCNT = DCNT_OBJ | /*DCNT_BG0 |*/ DCNT_BG1 | DCNT_OBJ_1D | DCNT_MODE0;
    // TODO select curr cam
}

void graphics_switch_to_office() {
    /* HIDE OBJECTS */
    // TODO can I not just do this by hiding layers?
    cam_map->attr0 = ATTR0_HIDE;
    /* END HIDE OBJECTS */

    // Load tiles into CBB 0
    memcpy(&tile_mem[MAIN_CBB][0], &officeTiles, officeTilesLen);
    // Load map into SBB 30
    memcpy(&se_mem[MAIN_SBB][0], &officeMap, officeMapLen);

    //show office
    //set_bg_palbank(OFFICE_PB);
    vbaprint("office now\n");
    REG_DISPCNT = DCNT_OBJ | DCNT_BG0 /*| DCNT_BG1*/ | DCNT_OBJ_1D | DCNT_MODE0;
    // copy pallette
    // Load palette
    memcpy(&pal_bg_mem[0], &officePal, officePalLen);

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


    CAM_IMG_DATA cid = get_cam_img_data(new_room);

    // TODO previously this was
    // load_bg_pal(cid.cam_pal, cid.cam_pal_len, CAM_STAT ? 0 : CAM_PB);
    // implying calling it when the camera is not up could cause issues
    // so make sure this is ONLY called if the camera is up
    // also TODO wtf even is this 0 supposed to mean anyway
    // maybe it was meant to be used to like preload cams?
    // okay this is called at init with camnum=0
    // and for some reason if palbank is always 0 then the office pal is messed up, and
    // if palbank is always CAM_PB then the cam pals are messed up
    memcpy(&pal_bg_mem[0], cid.cam_pal, cid.cam_pal_len);

    // Load tiles into CBB 0
    memcpy(&tile_mem[MAIN_CBB][0], cid.cam_tiles, cid.cam_tiles_len);

    // Load map into SBB 30
    memcpy(&se_mem[MAIN_SBB][0], cid.cam_map, cid.cam_map_len);
}

void graphics_init_blip_test() {
    // TODO I cannot for the life of me figure out why the cam_blip_testPal becomes pink even tho they have the
    // EXACT SAME VALUES when printed
    unsigned short colors[2] = {0x0000, 0x7FFF,};
    memcpy(&tile_mem[3], &cam_blip_testTiles, cam_blip_testTilesLen);
    memcpy(&pal_bg_mem[0], &colors, 4);
    REG_BG3CNT = BG_CBB(3) | BG_SBB(26) | BG_4BPP | BG_REG_32x32;
    REG_BG3HOFS = 10;
    unsigned short empty_frame[32 * 20];
    for (u16 i = 0; i < 32 * 20; i++) {
        empty_frame[i] = 0x0000;
    }
    const u8 num_frames = 10;
    u16 lengths[] = {
            cam_blip_0_len, cam_blip_1_len, cam_blip_2_len, cam_blip_3_len,
            cam_blip_4_len, cam_blip_5_len, cam_blip_6_len, cam_blip_7_len, cam_blip_8_len, 1280
    };
    u8 offsets[] = {
            cam_blip_0_vert_offset, cam_blip_1_vert_offset, cam_blip_2_vert_offset, cam_blip_3_vert_offset,
            cam_blip_4_vert_offset, cam_blip_5_vert_offset, cam_blip_6_vert_offset, cam_blip_7_vert_offset,
            cam_blip_8_vert_offset, 0
    };
    SE *frames[] = {
            &cam_blip_0, &cam_blip_1, &cam_blip_2, &cam_blip_3,
            &cam_blip_4, &cam_blip_5, &cam_blip_6, &cam_blip_7, &cam_blip_8, &empty_frame
    };
    for (u8 i = 0; i < num_frames; i++) {
        memcpy(&se_mem[26], &empty_frame, 1280);
        memcpy(&se_mem[26], frames[i], lengths[i]);
        REG_BG3VOFS = offsets[i];
        vid_vsync();
    }
    memcpy(&pal_bg_mem[0], &cam_blip_testPal, 4);
}

void graphics_blip_test() {

}

struct GraphicsWrapper Graphics = {
        .show_static = &show_static,
        .init_objects = &init_objects,
        .game_display_cams = &graphics_switch_to_cams,
        .game_display_office = &graphics_switch_to_office,
        .select_cam = &graphics_select_cam,
        .init_blip_test= &graphics_init_blip_test,
        .blip_test = &graphics_blip_test,
        .init_backgrounds = &init_backgrounds
};