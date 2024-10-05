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

#define office_flicker() (rnd_max(10)>0)

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
        //u8 light_index = 0;
        //bool occupant_index = false;
        enum EffectNames flicker = room_effects[ROOM_OFFICE];
        bool side = false;
        if (Equipment.is_on(LEFT_LIGHT)) {
            flicker = office_flicker();
        } else if (Equipment.is_on(RIGHT_LIGHT)) {
            flicker = office_flicker();
            side = true;
        }
        if (flicker != room_effects[ROOM_OFFICE]) {
            room_effects[ROOM_OFFICE] = flicker;
            if(flicker){
                bool occupied = side ? Animatronics.get_room_occupants(ROOM_RIGHT_DOOR) >> 2 : Animatronics.get_room_occupants(ROOM_LEFT_DOOR) >> 3;
                Graphics.enable_office_light(side, occupied);
            }else{
                Graphics.clear_office_lights();
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

