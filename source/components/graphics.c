#include <string.h>
#include "tonc.h"
#include "graphics.h"
#include "game/room_names.h"
#include "images/sprites/cam_map/cam_map.h"
#include "DWedit/debug.h"
#include "graphics/cam_img_map.h"
#include "graphics/frames.h"
#include "images/office/door/l_door.h"
#include "images/office/door/r_door.h"
#include "images/office/office.h"
#include "graphics/effects/cam_blip.h"


/* BUFFERS */
// OBJ_ATTR OBJ_BUFFER[128];
/* END BUFFERS */

/* OBJECTS */
OBJ_ATTR *cam_map;
OBJ_ATTR *l_door0;
OBJ_ATTR *l_door1;
OBJ_ATTR *l_door2;
OBJ_ATTR *r_door0;
OBJ_ATTR *r_door1;
OBJ_ATTR *r_door2;

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
const int MAP_TILE_START = 50;
const u16 LDOOR_TILE_START = 128;
const u16 RDOOR_TILE_START = LDOOR_TILE_START + 160;
const u8 L_DOOR_PALBANK = 1;
const u8 R_DOOR_PALBANK = 2; // TODO make them use the same pallette
#define DOOR_ATTR0 ATTR0_REG | ATTR0_4BPP | ATTR0_SQUARE
#define DOOR2_ATTR0 ATTR0_REG | ATTR0_4BPP | ATTR0_WIDE
#define LAYER_0 3
#define LAYER_1 2
#define LAYER_2 1
#define LAYER_3 0
#define CAM_STUN_AMOUNT 300
#define cams_dispcnt (DCNT_OBJ | /*DCNT_BG0 |*/ DCNT_BG1 | DCNT_BG3 | DCNT_OBJ_1D | DCNT_MODE0)
#define cams_stun_dispcnt (DCNT_OBJ | /*DCNT_BG0 | DCNT_BG1 |*/ DCNT_BG3 | DCNT_OBJ_1D | DCNT_MODE0)

/* END CONSTANTS / DEFINITIONS */

u16 cam_stun_timer = 0; // TODO set this to 0 on night start

void show_static() {
    REG_BG2CNT = BG_PRIO(LAYER_3) | BG_CBB(3) | BG_SBB(30) | BG_WRAP | BG_AFF_16x16;
    REG_DISPCNT = DCNT_BG0 | DCNT_BG2 | DCNT_MODE1;
}

void graphics_set_office_scroll(s16 value) {
    REG_BG0HOFS = value;
    s16 l_door_x = 16 - value;
    obj_set_pos(l_door0, l_door_x, 0);
    obj_set_pos(l_door1, l_door_x, 64);
    obj_set_pos(l_door2, l_door_x, 128);
    s16 r_door_x = 280 - value;
    obj_set_pos(r_door0, r_door_x, 0);
    obj_set_pos(r_door1, r_door_x, 64);
    obj_set_pos(r_door2, r_door_x, 128);
}

void load_door_frame(u8 frame_num, u16 tile_start, u16 *tiles) {
    u16 offset = frame_num * 2560;//(1024+1024+512)
    memcpy(&tile_mem[4][tile_start], &tiles[offset], 2048/*32 * 64*/);
    memcpy(&tile_mem[4][tile_start + 64], &tiles[offset + 1024], 2048/*32 * 64*/);
    memcpy(&tile_mem[4][tile_start + 128/*64*2*/], &tiles[offset + 2048/*1024*2*/], 1024/*32 * 32*/);
}

void load_left_door_frame(u8 frame_num) {
    load_door_frame(frame_num, LDOOR_TILE_START, &l_doorTiles);
}

void load_right_door_frame(u8 frame_num) {
    load_door_frame(frame_num, RDOOR_TILE_START, &r_doorTiles);
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
    memcpy(&tile_mem[4][MAP_TILE_START], &cam_mapTiles, cam_mapTilesLen);
    memcpy(&pal_obj_bank[0], &cam_mapPal, cam_mapPalLen);
    obj_set_pos(cam_map, 176 /*screen width - map width*/, 96 /*screen height - map height*/);

    /* DOOR CODE */
    // TODO clean
    l_door0 = &oam_mem[1];
    obj_set_attr(
            l_door0,
            ATTR0_HIDE,
            ATTR1_SIZE_64x64,
            ATTR2_PALBANK(L_DOOR_PALBANK) | ATTR2_ID(LDOOR_TILE_START) | ATTR2_PRIO(LAYER_0)
    ); // palbank 0, tile 0
    //obj_set_pos(l_door0, 16, 0);
    l_door1 = &oam_mem[2];
    obj_set_attr(
            l_door1,
            ATTR0_HIDE,
            ATTR1_SIZE_64x64,
            ATTR2_PALBANK(L_DOOR_PALBANK) | ATTR2_ID(LDOOR_TILE_START + 64) | ATTR2_PRIO(LAYER_0)
    ); // palbank 0, tile 0
    //obj_set_pos(l_door1, 16, 64);
    l_door2 = &oam_mem[3];
    obj_set_attr(
            l_door2,
            ATTR0_HIDE,
            ATTR1_SIZE_64x32,
            ATTR2_PALBANK(L_DOOR_PALBANK) | ATTR2_ID(LDOOR_TILE_START + 128) | ATTR2_PRIO(LAYER_0)
    ); // palbank 0, tile 0
    r_door0 = &oam_mem[4];
    obj_set_attr(
            r_door0,
            ATTR0_HIDE,
            ATTR1_SIZE_64x64,
            ATTR2_PALBANK(R_DOOR_PALBANK) | ATTR2_ID(RDOOR_TILE_START) | ATTR2_PRIO(LAYER_0)
    ); // palbank 0, tile 0
    //obj_set_pos(l_door0, 16, 0);
    r_door1 = &oam_mem[5];
    obj_set_attr(
            r_door1,
            ATTR0_HIDE,
            ATTR1_SIZE_64x64,
            ATTR2_PALBANK(R_DOOR_PALBANK) | ATTR2_ID(RDOOR_TILE_START + 64) | ATTR2_PRIO(LAYER_0)
    ); // palbank 0, tile 0
    r_door2 = &oam_mem[6];
    obj_set_attr(
            r_door2,
            ATTR0_HIDE,
            ATTR1_SIZE_64x32,
            ATTR2_PALBANK(R_DOOR_PALBANK) | ATTR2_ID(RDOOR_TILE_START + 128) | ATTR2_PRIO(LAYER_0)
    ); // palbank 0, tile 0
    load_left_door_frame(0);
    load_right_door_frame(0);
    // TODO load right door frame

    // TODO make use same pal
    memcpy(&pal_obj_bank[L_DOOR_PALBANK], &l_doorPal, l_doorPalLen);
    memcpy(&pal_obj_bank[R_DOOR_PALBANK], &r_doorPal, r_doorPalLen);
    /* END DOOR CODE */

    // TODO magic number also used in controls.c as the default value for office_horiz_scroll
    // TODO also should this even be here
    graphics_set_office_scroll(57);


    /* END FROM cams on night start */

    /* EXTRA STUFF
     * This originally ran on at the end of every loop: oam_copy(oam_mem, OBJ_BUFFER, 128);
     * This originally ran on init: oam_init(OBJ_BUFFER, 128);
     * also, there was a buffer declaration at the top of game.c (see top of this file in buffers)
     * */
}

void init_backgrounds() {
    //unsigned short colors[2] = {0x0000, 0x7FFF,};
    //memcpy(&pal_bg_mem[0], &colors, 4);
    CamBlipEffect.init();
    REG_BG3HOFS = 0;

    // TODO might need to reaffirm this in switching functions
    REG_BG0CNT = BG_PRIO(LAYER_0) | BG_CBB(MAIN_CBB) | BG_SBB(MAIN_SBB) | BG_8BPP | BG_REG_64x32;
    REG_BG1CNT = BG_PRIO(LAYER_1) | BG_CBB(MAIN_CBB) | BG_SBB(MAIN_SBB) | BG_8BPP | BG_REG_64x64;
}

void load_frame(Frame *frame, u16 cbb, u16 sbb) {
    dma3_cpy(&pal_bg_mem[0], frame->palette, frame->palette_length);
    dma3_cpy(&tile_mem[cbb][0], frame->tiles, frame->tiles_length);
    dma3_cpy(&se_mem[sbb][0], frame->screen_entry, frame->screen_entry_length);
}

void graphics_switch_to_cams() {
    obj_unhide(cam_map, ATTR0_REG);
    // TODO clean
    obj_hide(l_door0);
    obj_hide(l_door1);
    obj_hide(l_door2);
    obj_hide(r_door0);
    obj_hide(r_door1);
    obj_hide(r_door2);
    CamBlipEffect.load();
    //TODO: shouldn't have to do this every time, but setting
    REG_DISPCNT = cam_stun_timer ? cams_stun_dispcnt : cams_dispcnt;
    // TODO set static opacity based on cam stun level
    CamBlipEffect.reset();
}

void graphics_switch_to_office() {
    /* HIDE OBJECTS */
    //l_door0->attr0 = l_door1->attr0 = DOOR_ATTR0; // TODO set individual bits to hide and show
    //l_door2->attr0 =  DOOR2_ATTR0;
    // TODO clean
    obj_unhide(l_door0, ATTR0_REG);
    obj_unhide(l_door1, ATTR0_REG);
    obj_unhide(l_door2, ATTR0_REG);
    obj_unhide(r_door0, ATTR0_REG);
    obj_unhide(r_door1, ATTR0_REG);
    obj_unhide(r_door2, ATTR0_REG);
    obj_hide(cam_map);
    //cam_map->attr0 = ATTR0_HIDE;
    /* END HIDE OBJECTS */

    //show office
    //set_bg_palbank(OFFICE_PB);
    vbaprint("office now\n");
    load_frame(&office_base_frame, MAIN_CBB, MAIN_SBB);
    REG_DISPCNT = DCNT_OBJ | DCNT_BG0 /*| DCNT_BG1*/ | DCNT_OBJ_1D | DCNT_MODE0;


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

    load_frame(&cid, MAIN_CBB, MAIN_SBB);
    CamBlipEffect.start();
}


void (*office_funcs[8])() = {
        &undo_office_llight_empty, &do_office_llight_empty, // l empty
        &undo_office_llight_bonnie, &do_office_llight_bonnie, // l bonnie
        &undo_office_rlight_empty, &do_office_rlight_empty, // r empty
        &undo_office_rlight_chica, &do_office_rlight_chica // r chica
};

void do_nothing() {
    return;
}

void (*undo_office)() = &do_nothing;

void graphics_enable_office_light(bool right_side, bool occupied) {
    u8 offset = (4 * right_side) + (2 * occupied);
    undo_office = office_funcs[offset];
    office_funcs[offset + 1]();
    /*
    } else {
        undo_office = &do_nothing;
        office_funcs[offset]();
    }*/
}

void graphics_clear_office_lights() {
    undo_office();
}

void graphics_on_room_visual_change(Frame *new_frame) {
    load_frame(new_frame, MAIN_CBB, MAIN_SBB);
}

void graphics_update_cam() {
    CamBlipEffect.update();

    if (cam_stun_timer) {
        cam_stun_timer--;
        if (cam_stun_timer == 0) {
            vbaprint("stun over\n");
            REG_DISPCNT = cams_dispcnt;
            // TODO decrease static opacity
        }
    }
}

void graphcis_update_office() {
    if (cam_stun_timer) {
        cam_stun_timer--;
    }
}

void graphics_stun_cams(enum RoomNames room) {
    if (cam_stun_timer == 0) {
        // TOOD assuming this is called when the cams are up
        REG_DISPCNT = cams_stun_dispcnt;
        graphics_select_cam(room, room);
        // TODO increase static opacity
    }
    cam_stun_timer = CAM_STUN_AMOUNT;
}

struct GraphicsWrapper Graphics = {
        .show_static = &show_static,
        .init_objects = &init_objects,
        .game_display_cams = &graphics_switch_to_cams,
        .game_display_office = &graphics_switch_to_office,
        .select_cam = &graphics_select_cam,
        .update_cam= &graphics_update_cam,
        .init_backgrounds = &init_backgrounds,
        .on_room_visual_change = &graphics_on_room_visual_change,
        .set_office_scroll = &graphics_set_office_scroll,
        .load_left_door_frame = &load_left_door_frame,
        .load_right_door_frame = &load_right_door_frame,
        .enable_office_light = &graphics_enable_office_light,
        .clear_office_lights = &graphics_clear_office_lights,
        .stun_cams = &graphics_stun_cams,
        .update_office = &graphcis_update_office
};