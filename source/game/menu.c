//
// Created by cb106 on 1/21/2021.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "../../include/tonc/toolbox.h"
#include "../../assets/images/backgrounds/menu/menu.h"
#include "../../assets/images/backgrounds/office/office.h"
#include "../init.h"
#include "game.h"
#include "../../include/DWedit/debug.h"
#include "graphics/bg_pal_handler.h"
#include "control/controls.h"
#include "../util/random.h"

const int MAX_FRAMES_FOR_FACE_GLITCH = 10;
const int MIN_FRAMES_FOR_FACE_GLITCH = 2;

void init_menu() {
    // Load palette
    memcpy(pal_bg_mem, menuPal, menuPalLen);

    // Load tiles into CBB 0
    memcpy(&tile_mem[0][0], menuTiles, menuTilesLen);

    // Load map into SBB 30
    memcpy(&se_mem[13][0], menuMap, menuMapLen);

    // TODO remove
    memcpy(&pal_bg_mem[16], officePal, officePalLen);
}

void activate_menu() {
    //switch backgrounds etc
    int stage = 0;
    int menu_choice = 0;
    int timer = -1;

    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;

    // set up BG0 for a 4bpp 64x32t map, using
    //   using charblock 0 and screenblock 31
    REG_BG0CNT = BG_CBB(0) | BG_SBB(13) | BG_4BPP | BG_REG_64x64;
    REG_DISPCNT = DCNT_BG0 | DCNT_MODE0; //IMPORTANT: MUST BE IN ORDER OF BITS FROM LEFT TO RIGHT (this order)
    while (stage != -1) { // -1 means exit menu, start game
        vid_vsync();
        key_poll();

        // Selection Keys
        //if (key_hit(KEY_UP) || key_hit(KEY_DOWN) || key_hit(KEY_SELECT)) {
        if (CTRL_MENU_SELECT) {
            // swap palette color for cursors
            COLOR temp = pal_bg_mem[15];
            pal_bg_mem[15] = pal_bg_mem[14];
            pal_bg_mem[14] = temp;

            // update menu choice
            menu_choice = !menu_choice;
        }

        // Start keys
        if (CTRL_MENU_START) {
            if (menu_choice == 0) { // New Game
                init_game(0); //Night 0 shows the newspaper
            } else if (menu_choice == 1) { //Continue
                //TODO: can remove comparison if a controls screen isn't added
                int saved_night = GAMEPAK_RAM[0];

                /*
                vbaprint("loaded ");
                vbaprint(saved_night == 0 ? "0" : saved_night == 9 ? "9" : "something else");
                vbaprint("\n");
                */

                // for verification on real hardware
                //TODO: remove
                switch (saved_night) {
                    case 0:
                        pal_bg_mem[15] = CLR_RED;
                        break;
                    case 9:
                        pal_bg_mem[15] = CLR_BLUE;
                        break;
                    default:
                        pal_bg_mem[15] = CLR_LIME;
                        break;
                }

                init_game(saved_night == 0 ? 1 : saved_night);
            }
            //TODO: prevent starting if init fails
            start_game();
        }

        //TODO: remove
        if (key_hit(KEY_B)) {
            GAMEPAK_RAM[0] = 9;
            set_bg_palbank(!curr_bg_palbank);
        }

        if (timer == -1) { // maybe change to less than 0
            //TODO: util function for rand
            if (random_max(50) == 0) { // 2% chance to change screens every frame
                //below line forces it to not choose the top left if it's already there
                //TODO: make it more likely to change multiple times in a row like the original seems to do
                int force_offset = !((REG_BG0HOFS % 240) && (REG_BG0VOFS % 160)); //0 if on tl, 1 or 2 otherwise
                REG_BG0HOFS = (random_max(2) + force_offset) * 240; //
                REG_BG0VOFS = (random_max(2) + force_offset) * 160;
                timer = random_max(MAX_FRAMES_FOR_FACE_GLITCH - MIN_FRAMES_FOR_FACE_GLITCH) + MIN_FRAMES_FOR_FACE_GLITCH;
            }
        } else if (timer == 0) {
            REG_BG0HOFS = 0;
            REG_BG0VOFS = 0;
            timer = -1;
        } else {
            timer--;
        }

        //TODO: random flickering
    }
}