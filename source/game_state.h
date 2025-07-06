#ifndef FNAF_ADVANCE_GAME_STATE_H
#define FNAF_ADVANCE_GAME_STATE_H

#include "tonc_types.h"

enum GamePhases {
    MENU_HOME, MENU_OPTIONS,
    NIGHT_NEWSPAPER,
    NIGHT_INTRO, NIGHT_POWER_ON, NIGHT_POWER_OFF, NIGHT_JUMPSCARE, NIGHT_DEATH, NIGHT_VICTORY
};

extern enum GamePhases GAME_PHASE;

enum Jumpscares { // TODO maybe need to fix order
    JUMPSCARE_NONE, JUMPSCARE_BONNIE, JUMPSCARE_CHICA, JUMPSCARE_FOXY, JUMPSCARE_FREDDY_STD, JUMPSCARE_FREDDY_POWER, JUMPSCARE_GOLDEN
};

extern enum Jumpscares JUMPSCARER;

extern bool SHOW_CAM_ANIM_ON_JUMPSCARE;

extern u8 NIGHT_NUM;

//TODO: could be smaller num if necessary
extern int FRAME_NUM;

bool frame_multiple(int factor);
void increment_frame();

#endif //FNAF_ADVANCE_GAME_STATE_H
