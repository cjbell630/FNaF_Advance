#ifndef FNAF_ADVANCE_SPOOKY_EFFECTS_H
#define FNAF_ADVANCE_SPOOKY_EFFECTS_H

#include "tonc_types.h"
#include "game/room_names.h"

enum EffectNames {
    NORMAL=0, LIGHTS_OFF=1, SNAP1, SNAP2, STARE, ITS_ME
};

// far (normal) -> close (look) / normal -> look
// far (normal) -> close
// normal -> snap1 -> snap2 / normal -> newspaper0->3
// far (normal) -> close / normal -> crying -> its me
// normal -> its me / foxy0->2 (nomral, look, approach?)
// far (normal) -> close
// normal -> stare
// normal -> snap1 -> snap2 / normal -> snap -> its me
// lights on (normal) -> off / foxy0->99

// close = look
// far = normal
// newspapers? crying?

// office: normal, llight, rlight, power off


struct SpookyEffectsWrapper {
    void (*update)(bool cams_are_up, enum RoomNames selected_cam);

    void (*on_night_start)();

    enum EffectNames (*get_effects)(enum RoomNames room);
};

extern struct SpookyEffectsWrapper SpookyEffects;

#endif //FNAF_ADVANCE_SPOOKY_EFFECTS_H
