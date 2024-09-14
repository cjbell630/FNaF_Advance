#include "spooky_effects.h"
#include "game/room_names.h"
#include "graphics.h"
#include "graphics/frames.h"
#include "graphics/cam_img_map.h"
#include "util/random.h"
#include "equipment.h"
#include "animatronics.h"

static enum EffectNames room_effects[NUM_ROOMS];
bool FLICKER = false;

bool office_flicker() {
    return rnd_max(10); // 9/10 chance it's on TODO find original value
}

void spooky_effects_on_night_start() {
    for (int i = 0; i < NUM_ROOMS; i++) {
        room_effects[i] = NORMAL; // TODO is there a more efficient way to do this
    }
}

void update_spooky_effects(bool cams_are_up, enum RoomNames selected_cam) {
    // TODO add cam blip here instead
    if (cams_are_up) {

    } else {
        /* OFFICE */
        u8 light_index = 0;
        bool occupant_index = false;
        if (Equipment.is_on(LEFT_LIGHT)) {
            if (office_flicker()) {
                light_index = 1;
                occupant_index = Animatronics.get_room_occupants(ROOM_RIGHT_DOOR) >> 3;
            }
        } else if (Equipment.is_on(RIGHT_LIGHT)) {
            if (office_flicker()) {
                light_index = 2;
                occupant_index = Animatronics.get_room_occupants(ROOM_RIGHT_DOOR) >> 2;
            }
        }
        enum EffectNames new_office_effect = (light_index * 2) + occupant_index;
        if (new_office_effect != room_effects[ROOM_OFFICE]) {
            room_effects[ROOM_OFFICE] = new_office_effect;
            Graphics.on_room_visual_change(&office_frames[light_index][occupant_index]);
        }
    }
}

enum EffectNames get_effects(enum RoomNames room) {
    return room_effects[room];
}

struct SpookyEffectsWrapper SpookyEffects = {
        .update = update_spooky_effects,
        .on_night_start = spooky_effects_on_night_start,
        .get_effects = get_effects
};

