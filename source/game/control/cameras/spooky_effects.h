#ifndef FNAF_ADVANCE_SPOOKY_EFFECTS_H
#define FNAF_ADVANCE_SPOOKY_EFFECTS_H

#include "game/control/cameras/room_names.h"

enum EffectNames {
    NORMAL, ITS_ME, SNAP, STARE
};


struct SpookyEffectsWrapper {
    void (*update)(int frame_num);
    void (*on_night_start)(int night_num);
    enum EffectNames (*get_effects)(enum RoomNames room);
};

extern struct SpookyEffectsWrapper SpookyEffects;

#endif //FNAF_ADVANCE_SPOOKY_EFFECTS_H
