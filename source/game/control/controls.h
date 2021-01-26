//
// Created by cb106 on 1/22/2021.
//

#ifndef FNAF_ADVANCE_CONTROLS_H
#define FNAF_ADVANCE_CONTROLS_H

#include "../../../include/tonc/input.h"

#define CTRL_MENU_SELECT key_hit(KEY_UP | KEY_DOWN | KEY_SELECT)
#define CTRL_MENU_START key_hit(KEY_START | KEY_A)
#define CTRL_OFFICE_SCROLL key_tri_shoulder()
#define CTRL_OPEN_CAM key_hit(KEY_SELECT)
#define CTRL_CLOSE_CAM key_hit(KEY_SELECT)

#endif //FNAF_ADVANCE_CONTROLS_H
