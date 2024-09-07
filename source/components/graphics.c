#include "tonc.h"
#include "graphics.h"
#include "game/room_names.h"
#include "images/sprites/cam_map/cam_map.h"

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

/* END CONSTANTS / DEFINITIONS */


void show_office();

void show_static() {
    REG_BG2CNT = BG_PRIO(0) | BG_CBB(3) | BG_SBB(30) | BG_WRAP | BG_AFF_16x16;
    REG_DISPCNT = DCNT_BG0 | DCNT_BG2 | DCNT_MODE1;
}

void init_objects() {
    /* FROM cams on night start */
    // TODO cam_map = &OBJ_BUFFER[0];
    cam_map = &oam_mem[0];
    obj_set_attr(
            cam_map,
            ATTR0_HIDE,
            ATTR1_SIZE_64x64,                    // 16x16p,
            ATTR2_PALBANK(0) | 0
    ); // palbank 0, tile 0
    /* END FROM cams on night start */

    /* EXTRA STUFF
     * This originally ran on at the end of every loop: oam_copy(oam_mem, OBJ_BUFFER, 128);
     * This originally ran on init: oam_init(OBJ_BUFFER, 128);
     * also, there was a buffer declaration at the top of game.c (see top of this file in buffers)
     * */
}

void show_cams_graphics() {
    cam_map->attr0 = CAM_MAP_ATTR0_VISIBLE;
    obj_set_pos(cam_map, 176 /*screen width - map width*/, 96 /*screen height - map height*/);
    //TODO: shouldn't have to do this every time, but setting
}

void hide_cams_graphics() {
    // TODO can I not just do this by hiding layers?
    cam_map->attr0 |= ATTR0_HIDE;
}

void graphics_select_cam(enum RoomNames prev_room, enum RoomNames new_room) {
    //Swap pal of curr cam with new cam (green marker)
    /*
    COLOR temp = pal_obj_mem[prev_room + 3];
    pal_obj_mem[prev_room + 3] = pal_obj_mem[new_room + 3];
    pal_obj_mem[new_room + 3] = temp;*/
    pal_obj_mem[prev_room + 3] = CAM_MAP_UNSELECTED;
    pal_obj_mem[new_room + 3] = CAM_MAP_SELECTED;

}

struct GraphicsWrapper Graphics = {
        .show_static = &show_static,
        .init_objects = &init_objects,
        .show_cams = &show_cams_graphics,
        .hide_cams = &hide_cams_graphics,
        .select_cam = &graphics_select_cam
};