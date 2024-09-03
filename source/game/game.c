#include "game.h"
#include "tonc.h"
#include "init.h"
#include "DWedit/debug.h"
#include "images/backgrounds/office/office.h"
#include "images/backgrounds/newspaper/newspaper.h"
#include "images/backgrounds/static/static.h"
#include "images/backgrounds/loading/loading.h"
#include <string.h>
#include <stdlib.h>
#include "graphics/bg_pal_handler.h"
#include "graphics/static_handler.h"
#include "control/cameras/camera.h"
#include "control/controls.h"
#include "control/ai/ai.h"
#include "util/random.h"
#include "control/game_clock.h"
#include "images/sprites/cam_map/cam_map.h"
#include "control/cameras/cam_nav.h"

const int NEWSPAPER_PB = 1;
const int NEWSPAPER_CBB = 3;
const int NEWSPAPER_SBB = 10;

int curr_night;

void init_game(int night) {
    init_clock();
    curr_night = night;

    init_static();
    //vbaprint("loading now\n");

    //TODO: write to save on new game

    //TODO: should load this into a buffer so it doesn't mess up
    /*
    // Load palette

    // Load tiles into CBB 0
    memcpy(&tile_mem[0][0], loadingTiles, loadingTilesLen);

    // Load map into SBB 30
    memcpy(&se_mem[13][0], loadingMap, loadingMapLen);
    load_bg_pal(loadingPal, loadingPalLen, 0);

    vid_vsync();
    int timer = 0;
    while (timer < 60) {
        vid_vsync();
        timer++;
    }


    //TODO: should load this into a buffer so it doesn't mess up
     */
    // Load palette
    load_bg_pal(officePal, officePalLen, OFFICE_PB);

    // Load tiles into CBB 0
    memcpy(&tile_mem[OFFICE_CBB][0], officeTiles, officeTilesLen);


    // Load map into SBB 30
    memcpy(&se_mem[OFFICE_SBB][0], officeMap, officeMapLen);

    memcpy(&tile_mem[4][0], cam_mapTiles, cam_mapTilesLen);
    memcpy(&pal_obj_mem[0], cam_mapPal, cam_mapPalLen);

    oam_init(OBJ_BUFFER, 128);


    int calc_night = night == 0 ? 1 : night; // ensures start positions and audio is loaded in for new game
    if (night == 0) {

    }

    //load night intro screen

    //load everything else
    /*
    int timer = 0;
    while (timer < 60) {
        vid_vsync();
        timer++;
    }*/

    //vbaprint("start cams\n");

    //vbaprint("done set cam display\n");

    //vbaprint("done loading\n");
}

void start_game() {
    //vbaprint("starting now\n");
    if (curr_night == 0) {
        //vbaprint("newspaper now\n");
        //show newspaper

        //vbaprint("done showing newspaper pallette\n");
        REG_BG0HOFS = 0;
        REG_BG0VOFS = 0;        // load newspaper into memory
        // Load palette
        load_bg_pal(newspaperPal, newspaperPalLen, NEWSPAPER_PB);
        set_bg_palbank(NEWSPAPER_PB);

        // Load tiles into CBB 0
        memcpy(&tile_mem[NEWSPAPER_CBB][0], newspaperTiles, newspaperTilesLen);

        // Load map into SBB 30
        memcpy(&se_mem[NEWSPAPER_SBB][0], newspaperMap, newspaperMapLen);
        REG_BG0CNT = BG_CBB(NEWSPAPER_CBB) | BG_SBB(NEWSPAPER_SBB) | BG_4BPP | BG_REG_32x32;
        REG_DISPCNT = DCNT_BG0 | DCNT_MODE0;
        int timer = 120;
        while (timer >= 0) {
            vid_vsync();
            timer--;
        }
        curr_night++;
    }

    //show night intro screen
    //TODO
    //init_ai();
    Animatronics.set_levels(3, 1, 10, 1);

    init_cams();
    //vbaprint("done init cams\n");
    select_cam(0);
    //vbaprint("done select cam\n");
    set_cam_display(0);

    //show office
    set_bg_palbank(OFFICE_PB);
    //vbaprint("office now\n");
    REG_BG0CNT = BG_PRIO(2) | BG_CBB(OFFICE_CBB) | BG_SBB(OFFICE_SBB) | BG_4BPP | BG_REG_64x32;
    //REG_BLDCNT = BLD_BUILD(BLD_BG0, BLD_BG1, BLD_OFF);
    //REG_BLDALPHA = BLDA_BUILD(0b01000, 0b01000);
    REG_DISPCNT = DCNT_BG0 | DCNT_MODE0;
    REG_BG0VOFS = 0;


    const int SPEED_SCALE = 3;
    const int ART_WIDTH = 360;
    const int GBA_SCREEN_WIDTH = 240;
    const int RIGHT_CAP = ART_WIDTH - GBA_SCREEN_WIDTH; // 120
    int x = RIGHT_CAP / 2, y = 0;

    while (1) {
        vid_vsync();
        key_poll();
        tick(); //TODO: should be at top or bottom?

        //TODO: make a cool gate for this
        if (are_cams_up()) { // cams up
            if (CTRL_CLOSE_CAM) {
                toggle_cam_display();
            }
            if (key_hit(KEY_A)) {
                select_next_cam();
            } else if (key_hit(KEY_B)) {
                select_prev_cam();
            }
            navigate_cams(
                    key_hit(KEY_RIGHT)? 1 : key_hit(KEY_LEFT)? -1 : 0,
                    key_hit(KEY_UP)? 1 : key_hit(KEY_DOWN)? -1 : 0
            );
        } else {
            if (CTRL_OPEN_CAM) {
                toggle_cam_display();
            }
            x += SPEED_SCALE * CTRL_OFFICE_SCROLL; //move
            x = (x > RIGHT_CAP) ? RIGHT_CAP : // if too far right, fix
                (x < 0) ? 0 : // if too far left, fix
                x; // otherwise, don't change
            //y += key_tri_vert();

            REG_BG0HOFS = x;
            //REG_BG0VOFS = y;

            //TODO: remove
            if (key_hit(KEY_START)) {
                //TODO: make this be the norm for the whole game
                REG_BG2CNT = BG_PRIO(0) | BG_CBB(3) | BG_SBB(30) | BG_WRAP | BG_AFF_16x16;
                REG_DISPCNT = DCNT_BG0 | DCNT_BG2 | DCNT_MODE1;
                //
                //set_bg_palbank(3);
            }
        }

        oam_copy(oam_mem, OBJ_BUFFER, 128);
    }
}
