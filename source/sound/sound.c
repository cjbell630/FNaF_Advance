#include "sound.h"
#include "debug.h"

void play_sound_by_enum(enum Sounds sound) {
    mgba_printf("Sound triggered");
    // TODO
}

struct SoundController Sound = {
    .play = &play_sound_by_enum
};
