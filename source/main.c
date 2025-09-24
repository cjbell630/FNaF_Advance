#include <tonc_irq.h>
#include "DWedit/debug.h"
#include "menu.h"
#include "game_state.h"
#include "game/game_loop.h"

//OBJ_AFFINE *obj_aff_buffer = (OBJ_AFFINE *) obj_buffer;

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
    vbaprint("entry\n");
    irq_init(NULL);
    irq_add(II_VBLANK, NULL);
    GAME_PHASE = MENU_HOME;
    NIGHT_NUM = 0;
    while (1) {
        init_menu();
        vbaprint("initialized menu\n");
        activate_menu();
        vbaprint("activate menu exited\n");
        run_game_loop();
    }
    return 0;
}
