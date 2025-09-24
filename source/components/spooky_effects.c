#include "spooky_effects.h"
#include "game/room_names.h"
#include "graphics.h"
#include "graphics/frames.h"
#include "graphics/cam_img_map.h"
#include "util/random.h"
#include "equipment.h"
#include "animatronics/animatronics_controller.h"
#include "images/office/office.h"
#include "DWedit/debug.h"
#include <stdio.h>
#include "components/animatronics/bonnie.h"
#include "components/animatronics/freddy.h"
#include "components/animatronics/chica.h"
#include "components/animatronics/foxy.h"

static enum EffectNames room_effects[NUM_ROOMS];
bool FLICKER = false;
/**
 * Randomized to 1-100 every time the cams are opened.
 */
u8 general_cam_hallucination_rng = 0;

/* MACROS FOR EFFECT ODDS */
#define office_flicker() (rnd_max(10)>0)
#define roll_stage_freddy (general_cam_hallucination_rng < 10)
#define roll_backstage_bonnie (general_cam_hallucination_rng < 10)
#define roll_backstage_empty (general_cam_hallucination_rng < 5)
#define roll_pirate_empty (general_cam_hallucination_rng < 10)
#define roll_east_empty (general_cam_hallucination_rng == 99 ? 2 : general_cam_hallucination_rng == 98)
#define roll_east_corner_empty (general_cam_hallucination_rng > 95 ? general_cam_hallucination_rng-95 : 0)
// TODO west hall corner freddy poster


void spooky_effects_on_night_start() {
    for (int i = 0; i < NUM_ROOMS; i++) {
        room_effects[i] = NORMAL; // TODO is there a more efficient way to do this
    }
}

void spooky_effects_on_cam_up() {
    general_cam_hallucination_rng = rnd_max(100);
}

void spooky_effects_on_select_cam(enum RoomNames room_name) {
    u8 occupants; // why can't you declare a variable in the first line of a switch statement ugh
    // TODO is setting to 0 redundant?
    switch (room_name) {
        case ROOM_STAGE:
            room_effects[room_name] = Animatronics.get_room_occupants(room_name) == OCCUPANTS_ONLY_FREDDY ?
                                      roll_stage_freddy : 0;
            break;
        case ROOM_DINING:
            room_effects[room_name] = AnimatronicChica.room_num == room_name ? AnimatronicChica.close_far :
                                      AnimatronicBonnie.room_num == room_name ? AnimatronicBonnie.close_far :
                                      0;// TODO remove direct call to BONNIE and CHICA
            break;
        case ROOM_PIRATE:
            room_effects[room_name] = AnimatronicFoxy.room_num == room_name ? AnimatronicFoxy.phase :
                                      roll_pirate_empty; // TODO remove direct call to FOXY
            break;
        case ROOM_WEST:
            break;
        case ROOM_WEST_CORNER:
            break;
        case ROOM_CLOSET:
            break;
        case ROOM_EAST:
            occupants = Animatronics.get_room_occupants(room_name);
            room_effects[room_name] = occupants == OCCUPANTS_EMPTY ? roll_east_empty :
                                      AnimatronicChica.room_num == room_name ? AnimatronicChica.close_far :
                                      0;
            break;
        case ROOM_EAST_CORNER:
            break;
        case ROOM_BACKSTAGE:
            occupants = Animatronics.get_room_occupants(room_name);
            room_effects[room_name] = occupants == OCCUPANTS_EMPTY ? roll_backstage_empty :
                                      occupants == OCCUPANTS_ONLY_BONNIE ? roll_backstage_bonnie :
                                      0;
            break;
        case ROOM_KITCHEN:
            break;
        case ROOM_RESTROOMS:
            room_effects[room_name] = AnimatronicChica.room_num == room_name ? AnimatronicChica.close_far :
                                      0;// TODO remove direct call to CHICA
            break;
        case ROOM_OFFICE:
            break;
        case ROOM_LEFT_DOOR:
            break;
        case ROOM_RIGHT_DOOR:
            break;
    }
}

// TODO am I going to use this?
void spooky_effects_on_room_change() {

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
            if (flicker) {
                bool occupied = side ? Animatronics.get_room_occupants(ROOM_RIGHT_DOOR) >> 2 :
                                Animatronics.get_room_occupants(ROOM_LEFT_DOOR) >> 1;
                Graphics.enable_office_light(side, occupied);
            } else {
                Graphics.clear_office_lights();
            }
        }
    }
}

enum EffectNames get_effects(enum RoomNames room) {
    return room_effects[room];
}

struct SpookyEffectsWrapper SpookyEffects = {
        .update = &update_spooky_effects,
        .on_night_start = &spooky_effects_on_night_start,
        .get_effects = &get_effects,
        .on_cam_up = &spooky_effects_on_cam_up,
        .on_select_cam = &spooky_effects_on_select_cam
};

