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

#endif //FNAF_ADVANCE_GAME_STATE_H
