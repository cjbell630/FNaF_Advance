#include "tonc_input.h"
#include "controls.h"
#include "equipment.h"
#include "game/cam_nav.h"

/* CONTROL MACROS */

/* Office */
#define CTRL_OFFICE_SCROLL key_tri_shoulder() // L scrolls left, R scrolls right

/* Cams */
#define CTRL_OPEN_CAM key_hit(KEY_SELECT | KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT) //D-Pad or Select
#define CTRL_CLOSE_CAM key_hit(KEY_SELECT | KEY_B | KEY_A) // Face buttons or Select

/* END CONTROL MACROS */

/**
 * Called for every control scheme
 */
void controls_universal() {
    key_poll();
}

void controls_menu() {
    controls_universal();
}


// TODO move this to graphics
const int SPEED_SCALE = 3;
const int ART_WIDTH = 360;
const int GBA_SCREEN_WIDTH = 240;
const int RIGHT_CAP = ART_WIDTH - GBA_SCREEN_WIDTH; // 120
int office_horiz_scroll = RIGHT_CAP / 2, y = 0;

void controls_office() {
    controls_universal();
    if (CTRL_OPEN_CAM) {
        Equipment.toggle(CAMERA);
        return;
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
        //
        //set_bg_palbank(3);
    }
}

void controls_cam() {
    controls_universal();
    if (CTRL_CLOSE_CAM) {
        // TODO this doesn't really need to be toggle tho, esp since there are no side effects of disabling camera
        Equipment.toggle(CAMERA);
        return;
    }
    navigate_cams(
            key_hit(KEY_RIGHT) ? 1 : key_hit(KEY_LEFT) ? -1 : 0,
            key_hit(KEY_UP) ? 1 : key_hit(KEY_DOWN) ? -1 : 0
    );

}

struct ControlsWrapper Controls = {
        .update_office = &controls_office,
        .update_cam = &controls_cam,
        .update_menu = &controls_menu
};