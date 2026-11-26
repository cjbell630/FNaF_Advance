#include "ctrl/menu.h"
#include "util/random.h"
#include "game_state.h"
#include "components/controls.h"
#include "graphics/background.h"
#include "components/cursor.h"
#include "graphics/display.h"

#include <string.h>
#include <tonc_bios.h>
#include <tonc_input.h>
#include <tonc_memmap.h>
#include "debug.h"

/* CONSTANTS */
const int MAX_FRAMES_FOR_FACE_GLITCH = 10;
const int MIN_FRAMES_FOR_FACE_GLITCH = 2;

/* END CONSTANTS */

/* Menu */

u8 saved_night;

void init_menu() {

    // TODO remove
    //memcpy(&pal_bg_mem[16], officePal, officePalLen);
    Cursor.load();
    Cursor.set_choice(MENU_NEW_GAME);


    saved_night = 5;/* TODO GAMEPAK_RAM[0];*/ /* TODO make 0 (the save location) a const/macro */
    /* TODO load completion data (eg. num stars, whether night 6/7 are unlocked, etc) */

    mgba_printf("loaded ");
    mgba_printf(saved_night == 0 ? "0" : saved_night == 9 ? "9" : "something else");
    mgba_printf("\n");
}

void activate_menu() {
    //switch backgrounds etc
    //int stage = 0;
    //int menu_choice = 0;
    int timer = -1;

    // set up BG0 for a 4bpp 64x32t map, using
    //   using charblock 0 and screenblock 31
    Background.set_main_menu(); // TODO move
    Display.set_main_menu();

    while (GAME_PHASE == MENU_HOME) {

        // TODO is this accurate to the og game? when was this implemented?
        // TODO once that's checked, replace -1 and 0 with const/macros
        if (timer == -1) {
            // maybe change to less than 0
            if (rnd_max(50) == 0) {
                // 2% chance to change screens every frame
                //below line forces it to not choose the top left if it's already there
                //TODO: make it more likely to change multiple times in a row like the original seems to do
                const int force_offset = !((REG_BG0HOFS % 240) && (REG_BG0VOFS % 160)); //0 if on tl, 1 or 2 otherwise
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


        Controls.update_menu();

        /*
        if (key_hit(KEY_B)) {
            int data = 9;
            memcpy((void *) DMA_GAMEPAK, &data, 4);
            set_bg_palbank(!curr_bg_palbank);
        }*/

        //TODO: random flickering
        VBlankIntrWait();
    }

    Cursor.hide();
}
