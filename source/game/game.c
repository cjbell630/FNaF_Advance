#include "game.h"
#include "tonc.h"
#include "DWedit/debug.h"
#include "images/office/office.h"
#include "images/backgrounds/newspaper/newspaper.h"
#include "images/backgrounds/static/static.h"
#include "images/backgrounds/loading/loading.h"
#include <string.h>
#include <stdlib.h>
#include "graphics/bg_pal_handler.h"
#include "graphics/static_handler.h"
#include "components/camera.h"
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
const int NEWSPAPER_CBB = 0;
const int NEWSPAPER_SBB = 28;

void run_newspaper() {
    vbaprint("newspaper now\n");
    //show newspaper

    vbaprint("done showing newspaper palette\n");
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
        VBlankIntrWait();
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

    vbaprint("starting loop now\n");
    while (GAME_PHASE == NIGHT_POWER_ON) {
        tick(); //TODO: should be at top or bottom?
        VBlankIntrWait();
    }
}

/**
 * Transitions to power outage, then runs the game loop for power out
 */
void run_power_off() {
    vbaprint("power out!!!!!!! :O\n");
    // TODO power off phase
    // TODO bring cams down if they are up, bring doors up and switch lights off
    // TODO change office bg
    // TODO run w/ restricted office controls and minimal checks in bg
    while (GAME_PHASE == NIGHT_POWER_OFF) { // while player has not been kicked back to menu
        tick_power_off(); //TODO: should be at top or bottom?
        VBlankIntrWait();
    }
}

/**
 * Shows a jumpscare
 */
void run_jumpscare() {
    // TODO jumpscare
    switch (JUMPSCARER) {
        case JUMPSCARE_FOXY:
            vbaprint("JUMPSCARE!!!!!! (foxy)\n\n\n\n\n\n\n\n\n\n");
            break;
        case JUMPSCARE_CHICA:
            vbaprint("JUMPSCARE!!!!!! (chica)\n\n\n\n\n\n\n\n\n\n");
            break;
        case JUMPSCARE_BONNIE:
            vbaprint("JUMPSCARE!!!!!! (bonnie)\n\n\n\n\n\n\n\n\n\n");
            break;
        case JUMPSCARE_FREDDY_STD:
            vbaprint("JUMPSCARE!!!!!! (freddy standard)\n\n\n\n\n\n\n\n\n\n");
            break;
        case JUMPSCARE_FREDDY_POWER:
            vbaprint("JUMPSCARE!!!!!! (freddy power)\n\n\n\n\n\n\n\n\n\n");
            break;
        case JUMPSCARE_GOLDEN:
            vbaprint("JUMPSCARE!!!!!! (freddy golden)\n\n\n\n\n\n\n\n\n\n");
            // TODO crash game
            break;

    }
    GAME_PHASE = NIGHT_DEATH;
}

/**
 * Shows the death screen and returns to menu
 */
void run_death() {
    // TODO death
    vbaprint("\n\n\n\n\n\nYOU DIED\n\n\n\n\n");
    GAME_PHASE = MENU_HOME;
}

/**
 * Shows the "5->6am screen", plays audio, then:
 *
 * * Starts the next night, OR
 * * Shows the victory paycheck screen and return to menu
 */
void run_victory() {
    // TODO show 6am screen
    vbaprint("\n\n\n\n\n\n6AM!!!!!!\n\n\n\n\n");
    if (NIGHT_NUM < 5) { // if night is 1,2,3,or4, proceed to next night
        NIGHT_NUM++; // set next night
        GAME_PHASE = NIGHT_INTRO; // set the game to show the intro
        return;
    }

    // if night is 5,6,or7
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
    init_clock();
    if (GAME_PHASE == NIGHT_NEWSPAPER) {
        run_newspaper();
    }
    while (GAME_PHASE > NIGHT_NEWSPAPER) { // while player has not been kicked back to menu
        Graphics.init_backgrounds();
        run_night_intro(); // show "Night #/n12AM" screen (and do loading in background)
        run_power_on(); // run the game loop with the power on
        if (GAME_PHASE == NIGHT_POWER_OFF) { // if the power goes out
            run_power_off(); // run the game loop for when the power is out
        }
        if (GAME_PHASE == NIGHT_JUMPSCARE) { // if the player gets jumpscared
            run_jumpscare();
        }
        if (GAME_PHASE == NIGHT_DEATH) { // I think the player always dies if jumpscare is triggered so can combine
            run_death();
        }
        if (GAME_PHASE == NIGHT_VICTORY) { // at 6am
            run_victory();
        }
    } // return to menu when exit loop
}
