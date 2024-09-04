#include "spooky_effects.h"
#include "game/control/cameras/room_names.h"

static enum EffectNames room_effects[NUM_ROOMS];

void spooky_effects_on_night_start(int night_num) {
    for(int i=0; i<NUM_ROOMS; i++){
        room_effects[i] = NORMAL; // TODO is there a more efficient way to do this
    }
}

void update_spooky_effects(int frame_num) {

}

enum EffectNames get_effects(enum RoomNames room) {
    return room_effects[room];
}

struct SpookyEffectsWrapper SpookyEffects = {
        .update = update_spooky_effects,
        .on_night_start = spooky_effects_on_night_start,
        .get_effects = get_effects
};

