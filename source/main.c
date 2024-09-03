#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#include "DWedit/debug.h"

#include "images/backgrounds/office/office.h"
#include "images/sprites/buttons/buttons.h"
#include "images/sprites/buttons/buttons_apower.h"

#include "game/menu.h"
#include "init.h"

//OBJ_AFFINE *obj_aff_buffer = (OBJ_AFFINE *) obj_buffer;


int scroll_test() {

    //BACKGROUND
    //office screen is 45 tiles wide (360px)
    //so it should start right around 1/3 (120px)
    /*
    const int SPEED_SCALE = 3;
    const int ART_WIDTH = 360;
    const int GBA_SCREEN_WIDTH = 240;
    const int RIGHT_CAP = ART_WIDTH - GBA_SCREEN_WIDTH; //120
    int x = RIGHT_CAP / 2, y = 0;


    //SPRITES
    u32 tid = 0, pb = 0;        // tile id, pal-bank

    OBJ_ATTR *l_button = &OBJ_BUFFER[0];
    obj_set_attr(l_button,
                 ATTR0_TALL | ATTR0_4BPP,
                 ATTR1_SIZE_32x64,                    // 16x16p,
                 ATTR2_PALBANK(pb) | tid);        // palbank 0, tile 0

    // position sprite (redundant here; the _real_ position
    // is set further down
    const int BUTTON_HORIZ_OFFSET = 2;
    const int BUTTON_VERT_OFFSET = 62;
    obj_set_pos(l_button, BUTTON_HORIZ_OFFSET - x, y + BUTTON_VERT_OFFSET);

    while (1) {
        vid_vsync();
        key_poll();

        //BACKGROUND
        x += SPEED_SCALE * key_tri_shoulder(); //move
        x = (x > RIGHT_CAP) ? RIGHT_CAP : // if too far right, fix
            (x < 0) ? 0 : // if too far left, fix
            x; // otherwise, don't change
        //y += key_tri_vert();

        REG_BG0HOFS = x;
        //REG_BG0VOFS = y;


        //SPRITES
        if (key_is_down(KEY_A)) {
            pb = 1;
        } else {
            pb = 0;
        }

        obj_set_pos(l_button, BUTTON_HORIZ_OFFSET - x, y + BUTTON_VERT_OFFSET);
        l_button->attr2 = ATTR2_BUILD(tid, pb, 0);
        oam_copy(oam_mem, OBJ_BUFFER, 128);
    }*/

    return 0;
}

int main() {
    /**
    // Places the glyphs of a 8bpp boxed santa sprite
    //   into LOW obj memory (cbb == 4)
    memcpy(&tile_mem[4][0], santaTiles, santaTilesLen);
    memcpy(&pal_obj_mem[0], santaPal, santaPalLen);

    // Places the glyphs of a 8bpp boxed platform sprite
    //   into LOW obj memory (cbb == 4)
    memcpy(&tile_mem[4][NUM_TILES_IN_SANTA], platformTiles, platformTilesLen);
    memcpy(&pal_obj_mem[16], platformPal, platformPalLen);

    // inits the oam with 128 objects [from me]
    oam_init(obj_buffer, 128);
    REG_DISPCNT = DCNT_OBJ | DCNT_OBJ_1D; //sets display info

    obj_test();
     **/

    /*memcpy(&tile_mem[4][0], buttonsTiles, fnaf_button_abTilesLen);
    memcpy(&pal_obj_mem[0], buttonsPal, fnaf_button_abPalLen);
    memcpy(&pal_obj_mem[16], buttons_apowerPal, fnaf_button_ab_apowerPalLen);
    oam_init(obj_buffer, 128);
    //REG_DISPCNT = DCNT_OBJ | DCNT_OBJ_1D; //sets display info

    // Load palette
    memcpy(pal_bg_mem, officePal, officePalLen);
    // Load tiles into CBB 0
    memcpy(&tile_mem[0][0], officeTiles, officeTilesLen);
    // Load map into SBB 30
    memcpy(&se_mem[30][0], officeMap, officeMapLen);

    // set up BG0 for a 4bpp 64x32t map, using
    //   using charblock 0 and screenblock 31
    REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_64x32;
    REG_DISPCNT = DCNT_OBJ | DCNT_BG0 | DCNT_OBJ_1D |
                  DCNT_MODE0; //IMPORTANT: MUST BE IN ORDER OF BITS FROM LEFT TO RIGHT (this order)
                  */

    //scroll_test();
    vbaprint("entry");
    init_menu();
    vbaprint("initialized menu");
    activate_menu();
    vbaprint("activate menu exited");
    while (1);

    return 0;
}
