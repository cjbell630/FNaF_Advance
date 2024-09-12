#include "game.h"
#include "tonc.h"
#include "DWedit/debug.h"
#include "images/office/office.h"
#include "images/office/office_pal.h"
#include "images/backgrounds/newspaper/newspaper.h"
#include "images/backgrounds/static/static.h"
#include "images/backgrounds/loading/loading.h"
#include <string.h>
#include <stdlib.h>
#include "graphics/bg_pal_handler.h"
#include "graphics/static_handler.h"
#include "components/camera.h"
#include "controls.h"
#include "components/animatronics.h"
#include "util/random.h"
#include "game_clock.h"
#include "images/sprites/cam_map/cam_map.h"
#include "cam_nav.h"
#include "components/equipment.h"
#include "components/power.h"
#include "components/spooky_effects.h"
#include "game_state.h"
#include "components/graphics.h"

const int NEWSPAPER_PB = 1;
const int NEWSPAPER_CBB = 3;
const int NEWSPAPER_SBB = 10;


void init_game() {
    init_clock();

    //init_static();
    //vbaprint("loading now\n");

    //TODO: write to save on new game
    /*
    // Load palette

    // Load tiles into CBB 0
    memcpy(&tile_mem[0][0], loadingTiles, loadingTilesLen);

    // Load map into SBB 30
    memcpy(&se_mem[13][0], loadingMap, loadingMapLen);
    load_bg_pal(loadingPal, loadingPalLen, 0);
    //TODO: should load this into a buffer so it doesn't mess up
     */
    Graphics.init_backgrounds();
    //load night intro screen
}

void run_newspaper() {
    vbaprint("newspaper now\n");
    //show newspaper

    vbaprint("done showing newspaper pallette\n");
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
    GAME_PHASE = NIGHT_INTRO;
}

/**
 * Shows the "Night #\n12AM" screen while loading and initializing the night
 */
void run_night_intro() {
    vbaprint("starting now\n");

    //TODO show night intro screen

    /* INIT COMPONENTS */
    Animatronics.on_night_start();
    Power.on_night_start();
    Equipment.on_night_start();
    SpookyEffects.on_night_start();
    Cameras.on_night_start();
    /* END INIT COMPONENTS */

    Graphics.init_objects(); // TODO where should this go?


    GAME_PHASE = NIGHT_POWER_ON;
}

/**
 * Runs the gameplay loop for when the power is on
 */
void run_power_on() {
    //REG_DISPCNT = DCNT_BG0 | DCNT_MODE0;
    //REG_DISPCNT = DCNT_BG0 | DCNT_BG3 | DCNT_MODE0;
    Graphics.game_display_office();
    REG_BG0VOFS = 0;
    const int SPEED_SCALE = 3;
    const int ART_WIDTH = 360;
    const int GBA_SCREEN_WIDTH = 240;
    const int RIGHT_CAP = ART_WIDTH - GBA_SCREEN_WIDTH; // 120
    int office_horiz_scroll = RIGHT_CAP / 2, y = 0;

    vbaprint("starting loop now\n");
    while (GAME_PHASE == NIGHT_POWER_ON) {
        vid_vsync();
        key_poll();
        tick(); //TODO: should be at top or bottom?

        //TODO: make a cool gate for this
        if (Equipment.is_on(CAMERA)) { // cams up
            if (CTRL_CLOSE_CAM) {
                // TODO this doesn't really need to be toggle tho, esp since there are no side effects of disabling camera
                Equipment.toggle(CAMERA);
            }
            navigate_cams(
                    key_hit(KEY_RIGHT) ? 1 : key_hit(KEY_LEFT) ? -1 : 0,
                    key_hit(KEY_UP) ? 1 : key_hit(KEY_DOWN) ? -1 : 0
            );
        } else {
            if (CTRL_OPEN_CAM) {
                Equipment.toggle(CAMERA);
            }
            office_horiz_scroll += SPEED_SCALE * CTRL_OFFICE_SCROLL; //move
            office_horiz_scroll = (office_horiz_scroll > RIGHT_CAP) ? RIGHT_CAP : // if too far right, fix
                                  (office_horiz_scroll < 0) ? 0 : // if too far left, fix
                                  office_horiz_scroll; // otherwise, don't change
            //y += key_tri_vert();

            REG_BG0HOFS = office_horiz_scroll;
            //REG_BG0VOFS = y;

            //TODO: remove
            if (key_hit(KEY_START)) {
                //TODO: make this be the norm for the whole game
                //REG_BG2CNT = BG_PRIO(0) | BG_CBB(3) | BG_SBB(30) | BG_WRAP | BG_AFF_16x16;
                //REG_DISPCNT = DCNT_BG0 | DCNT_BG2 | DCNT_MODE1;
                Graphics.init_blip_test();
                //
                //set_bg_palbank(3);
            }
        }
    }
}

/**
 * Transitions to power outage, then runs the game loop for power out
 */
void run_power_off() {

}

/**
 * Shows a jumpscare
 */
void run_jumpscare() {

}

/**
 * Shows the death screen and returns to menu
 */
void run_death() {

}

/**
 * Shows the "5->6am screen", plays audio, then:
 *
 * * Starts the next night, OR
 * * Shows the victory paycheck screen and return to menu
 */
void run_victory() {
    // TODO show 6am screen
    if (NIGHT_NUM < 5) {
        NIGHT_NUM++; // set next night
        GAME_PHASE = NIGHT_INTRO; // set the game to show the intro
        return;
    }

    switch (NIGHT_NUM) {
        // TODO show paycheck screens
    }
    GAME_PHASE = MENU_HOME;
}

/**
 * Shows the newspaper if necessary, then runs the game loop like this:
 *
 * While intro; -> power on
 * While power on; -> power off, jumpscare, survived
 * While power off; -> jumpscare, survived
 * While jumpscare; -> death // will this work with cam moving down
 * While death; -> menu
 * While survived;
 */
void run_game_loop() {
    if (GAME_PHASE == NIGHT_NEWSPAPER) {
        run_newspaper();
    }
    while (GAME_PHASE > NIGHT_NEWSPAPER) { // while player has not been kicked back to menu
        run_night_intro(); // show "Night #/n12AM" screen (and do loading in background)
        run_power_on(); // run the game loop with the power on
        if (GAME_PHASE == NIGHT_POWER_OFF) { // if the power goes out
            run_power_off(); // run the game loop for when the power is out
        }
        if (GAME_PHASE == NIGHT_JUMPSCARE) { // if the player gets jumpscared
            run_jumpscare();
        }
        if (GAME_PHASE == NIGHT_DEATH) { // I think Death iff Jumpscare so can combine
            run_death();
        }
        if (GAME_PHASE == NIGHT_VICTORY) { // at 6am
            run_victory();
        }
    } // return to menu when exit loop
}
