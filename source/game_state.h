#ifndef FNAF_ADVANCE_GAME_STATE_H
#define FNAF_ADVANCE_GAME_STATE_H

#include "tonc_types.h"

enum GamePhases {
    MENU_HOME, MENU_OPTIONS,
    NIGHT_NEWSPAPER,
    NIGHT_INTRO, NIGHT_POWER_ON, NIGHT_POWER_OFF, NIGHT_JUMPSCARE, NIGHT_DEATH, NIGHT_VICTORY
};

extern enum GamePhases GAME_PHASE;

extern u8 NIGHT_NUM;

//TODO: could be smaller num if necessary
extern int FRAME_NUM;

bool frame_multiple(int factor);
void increment_frame();

#endif //FNAF_ADVANCE_GAME_STATE_H
