#ifndef FNAF_ADVANCE_CONTROLS_H
#define FNAF_ADVANCE_CONTROLS_H

#include "../../../include/tonclib/tonc.h"


/* Controls Macros*/
/* Menu */
#define CTRL_MENU_SELECT key_hit(KEY_UP | KEY_DOWN | KEY_SELECT) // Change selected option
#define CTRL_MENU_START key_hit(KEY_START | KEY_A) // Choose option

/* Office */
#define CTRL_OFFICE_SCROLL key_tri_shoulder() // L scrolls left, R scrolls right

/* Cams */
#define CTRL_OPEN_CAM key_hit(KEY_SELECT | KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT) //D-Pad or Select
#define CTRL_CLOSE_CAM key_hit(KEY_SELECT | KEY_B | KEY_A) // Face buttons or Select

#endif //FNAF_ADVANCE_CONTROLS_H
