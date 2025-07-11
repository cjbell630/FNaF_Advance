#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "tonc.h"
#include "images/backgrounds/menu/menu.h"
#include "DWedit/debug.h"
#include "graphics/bg_pal_handler.h"
#include "util/random.h"
#include "game_state.h"
#include "components/controls.h"

/* CONSTANTS */
const int MAX_FRAMES_FOR_FACE_GLITCH = 10;
const int MIN_FRAMES_FOR_FACE_GLITCH = 2;
enum MenuChoices {
    CHOICE_NEW_GAME, CHOICE_CONTINUE, CHOICE_NIGHT_6, CHOICE_CUSTOM_NIGHT, CHOICE_OPTIONS
};
/* END CONSTANTS */

/* Menu */
#define CTRL_MENU_SELECT key_hit(KEY_UP | KEY_DOWN | KEY_SELECT) // Change selected option
#define CTRL_MENU_START key_hit(KEY_START | KEY_A) // Choose option

enum MenuChoices menu_choice = CHOICE_NEW_GAME;
u8 saved_night;

void init_menu() {
    // Load palette
    memcpy(pal_bg_mem, menuPal, menuPalLen);

    // Load tiles into CBB 0
    memcpy(&tile_mem[0][0], menuTiles, menuTilesLen);

    // Load map into SBB 30
    memcpy(&se_mem[13][0], menuMap, menuMapLen);

    // TODO remove
    //memcpy(&pal_bg_mem[16], officePal, officePalLen);


    saved_night = 5;/* TODO GAMEPAK_RAM[0];*/ /* TODO make 0 (the save location) a const/macro */
    /* TODO load completion data (eg. num stars, whether night 6/7 are unlocked, etc) */

    vbaprint("loaded ");
    vbaprint(saved_night == 0 ? "0" : saved_night == 9 ? "9" : "something else");
    vbaprint("\n");
}

void activate_menu() {
    //switch backgrounds etc
    //int stage = 0;
    //int menu_choice = 0;
    int timer = -1;

    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;

    // set up BG0 for a 4bpp 64x32t map, using
    //   using charblock 0 and screenblock 31
    REG_BG0CNT = BG_CBB(0) | BG_SBB(13) | BG_4BPP | BG_REG_64x64;
    REG_DISPCNT = DCNT_BG0 | DCNT_MODE0; //IMPORTANT: MUST BE IN ORDER OF BITS FROM LEFT TO RIGHT (this order)


    while (GAME_PHASE == MENU_HOME) {
        Controls.update_menu();

        // TODO is this accurate to the og game? when was this implemented?
        // TODO once that's checked, replace -1 and 0 with const/macros
        if (timer == -1) { // maybe change to less than 0
            if (rnd_max(50) == 0) { // 2% chance to change screens every frame
                //below line forces it to not choose the top left if it's already there
                //TODO: make it more likely to change multiple times in a row like the original seems to do
                int force_offset = !((REG_BG0HOFS % 240) && (REG_BG0VOFS % 160)); //0 if on tl, 1 or 2 otherwise
                REG_BG0HOFS = (rnd_max(2) + force_offset) * 240; //
                REG_BG0VOFS = (rnd_max(2) + force_offset) * 160;
                timer = rnd_max(MAX_FRAMES_FOR_FACE_GLITCH - MIN_FRAMES_FOR_FACE_GLITCH) + MIN_FRAMES_FOR_FACE_GLITCH;
            }
        } else if (timer == 0) {
            REG_BG0HOFS = 0;
            REG_BG0VOFS = 0;
            timer = -1;
        } else {
            timer--;
        }



        // TODO names are kind of confusing, they imply start button and select button; change this
        // TODO also only supports 2 menu choices
        // Selection Keys
        if (CTRL_MENU_SELECT) {
            // swap palette color for cursors
            COLOR temp = pal_bg_mem[15];
            pal_bg_mem[15] = pal_bg_mem[14];
            pal_bg_mem[14] = temp;

            // update menu choice
            menu_choice = !menu_choice; // TODO
        }

        // Start keys
        if (CTRL_MENU_START) {
            switch (menu_choice) {
                case CHOICE_NEW_GAME:
                    GAME_PHASE = NIGHT_NEWSPAPER;
                    NIGHT_NUM = 1;
                    break;
                case CHOICE_CONTINUE:
                    GAME_PHASE = NIGHT_INTRO;
                    NIGHT_NUM = saved_night;
                    break;
                case CHOICE_NIGHT_6:
                    GAME_PHASE = NIGHT_INTRO;
                    NIGHT_NUM = 6;
                    break;
                case CHOICE_OPTIONS:
                case CHOICE_CUSTOM_NIGHT:
                    // TODO implement options menu
                    // TODO implement custom night menu
                    break;
                default:
                    break;
            }
            //return;
        }

        /*
        if (key_hit(KEY_B)) {
            int data = 9;
            memcpy((void *) DMA_GAMEPAK, &data, 4);
            set_bg_palbank(!curr_bg_palbank);
        }*/

        //TODO: random flickering
        VBlankIntrWait();
    }
}