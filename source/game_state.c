#include "game_state.h"
#include "util/util.h"

// kinda dumb but necessary for compilation
enum GamePhases GAME_PHASE;
u8 NIGHT_NUM;
int FRAME_NUM;

// TODO couldn't this be the screen_entry_length of a night 32400 frames which would fit in 2 bytes?
const int FRAME_MAX = 130881600; // the LCM of all frame intervals, to avoid massive nums in memory


bool frame_multiple(int factor) {
    return FRAME_NUM % factor == 0;
}

void increment_frame() {
    FRAME_NUM = (FRAME_NUM + 1) % FRAME_MAX;
}
