#include "spooky_effects.h"
#include "game/room_names.h"
#include "graphics.h"
#include "graphics/frames.h"
#include "graphics/cam_img_map.h"
#include "util/random.h"
#include "equipment.h"
#include "animatronics.h"
#include "images/office/office.h"
#include "DWedit/debug.h"
#include <stdio.h>

static enum EffectNames room_effects[NUM_ROOMS];
bool FLICKER = false;

bool office_flicker() {
    return rnd_max(10)>0; // 9/10 chance it's on TODO find original value
}

void spooky_effects_on_night_start() {
    for (int i = 0; i < NUM_ROOMS; i++) {
        room_effects[i] = NORMAL; // TODO is there a more efficient way to do this
    }
}

void (*office_funcs[8])() = {
        &undo_office_llight_empty, &do_office_llight_empty, // l empty
        &undo_office_llight_bonnie, &do_office_llight_bonnie, // l bonnie
        &undo_office_rlight_empty, &do_office_rlight_empty, // r empty
        &undo_office_rlight_chica, &do_office_rlight_chica // r chica
};

void update_spooky_effects(bool cams_are_up, enum RoomNames selected_cam) {
    // TODO add cam blip here instead
    if (cams_are_up) {

    } else {
        /* OFFICE */
        //u8 light_index = 0;
        //bool occupant_index = false;
        enum EffectNames flicker = room_effects[ROOM_OFFICE];
        bool side = false;
        // TODO add windowscare
        // TODO when light disabled, if flicker was on previously, unload
        if (Equipment.is_on(LEFT_LIGHT)) {
            flicker = office_flicker();
        } else if (Equipment.is_on(RIGHT_LIGHT)) {
            flicker = office_flicker();
            side = true;
        }
        if (flicker != room_effects[ROOM_OFFICE]) {
            room_effects[ROOM_OFFICE] = flicker;
            if (side) {
                office_funcs[flicker + 4 + 2 * (Animatronics.get_room_occupants(ROOM_RIGHT_DOOR) >> 2)]();
            } else {
                office_funcs[flicker + 2 * (Animatronics.get_room_occupants(ROOM_LEFT_DOOR) >> 3)]();
            }
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

