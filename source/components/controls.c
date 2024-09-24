#include "tonc_input.h"
#include "controls.h"
#include "equipment.h"
#include "game/cam_nav.h"
#include "DWedit/debug.h"
#include "graphics.h"

// TODO move this to graphics
const u8 SPEED_SCALE = 3;
const u16 ART_WIDTH = 354;
const u16 GBA_SCREEN_WIDTH = 240;
const u16 RIGHT_CAP = ART_WIDTH - GBA_SCREEN_WIDTH; // 114
const u8 BUTTONS_WIDTH = 16;
const u8 L_BUTTONS_CAP = BUTTONS_WIDTH + 1;
const u16 R_BUTTONS_CAP = ART_WIDTH - BUTTONS_WIDTH - 1;
s16 office_horiz_scroll = 57/*RIGHT_CAP/2*/, y = 0;

/* CONTROL MACROS */

/* Office */
#define CTRL_OFFICE_SCROLL key_tri_shoulder() // L scrolls left, R scrolls right
#define CTRL_DOOR key_hit(KEY_A)
#define CTRL_LIGHT key_hit(KEY_B)
#define can_press_left_buttons office_horiz_scroll < L_BUTTONS_CAP
#define can_press_right_buttons office_horiz_scroll > R_BUTTONS_CAP
#define CTRL_HONK key_hit(KEY_A) && key_hit(KEY_B)

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


void controls_office() {
    controls_universal();
    if (CTRL_OPEN_CAM) {
        Equipment.toggle(CAMERA);
        return;
    }
    int shoulder_input = CTRL_OFFICE_SCROLL;
    if (shoulder_input != 0) {
        s16 new_scroll = office_horiz_scroll + (SPEED_SCALE * shoulder_input);
        new_scroll = (new_scroll > RIGHT_CAP) ? RIGHT_CAP : // if too far right, fix
                     (new_scroll < 0) ? 0 : // if too far left, fix
                     new_scroll; // otherwise, don't change
        if (office_horiz_scroll != new_scroll) {
            office_horiz_scroll = new_scroll;
            Graphics.set_office_scroll(office_horiz_scroll);
        }
    }
    //y += key_tri_vert();

    //REG_BG0VOFS = y;
    if (can_press_left_buttons) {
        if (CTRL_LIGHT) {
            Equipment.toggle(LEFT_LIGHT);
        }
        if (CTRL_DOOR) {
            Equipment.toggle(LEFT_DOOR);
        }
    } else if (can_press_right_buttons) {
        if (CTRL_LIGHT) {
            Equipment.toggle(RIGHT_LIGHT);
        }
        if (CTRL_DOOR) {
            Equipment.toggle(RIGHT_DOOR);
        }
    } else if (CTRL_HONK) {
        // TODO
        vbaprint("nose honked :)\n");
    }
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