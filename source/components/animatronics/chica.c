#include "chica.h"
#include "DWedit/debug.h"
#include "game/room_names.h"
#include "animatronic.h"
#include "util/random.h"
#include "components/equipment.h"
#include "components/graphics.h"

void chica_move(enum RoomNames room, bool cams_are_up, enum RoomNames selected_cam) {
    if (cams_are_up && (selected_cam == room || selected_cam == CHICA.room_num)) {
        Graphics.stun_cams(selected_cam);
    }
    CHICA.close_far = (room == ROOM_DINING || room == ROOM_EAST || room == ROOM_RESTROOMS) ? rnd_max(2) : 0;
    CHICA.room_num = room;
}

/*  CHICA  */

// TODO this and chicas code are so similar, combine them somehow
void update_chica(bool cams_are_up, enum RoomNames selected_cam) {
    if (CHICA.room_num == ROOM_OFFICE) {
        if (CHICA.timer == -1) { // if the cams have not been lifted since chica got in the office
            if (cams_are_up) {
                CHICA.timer = 1800; // TODO magic num; 30s/1800f timer until jumpscare
            }
            return;
        }
        if (CHICA.timer < 1 || !cams_are_up) { // if the timer has been set, and has reached 0 or the cams are down
            trigger_jumpscare(JUMPSCARE_CHICA, cams_are_up);
            return;
        }
        // if the cams are up and the timer is ticking
        CHICA.timer--;

        /*
         * TODO option 1: check if cams are down here, and trigger jumpscare
         * (in this case, the cam down animation will have already been started so it might look funny)
         * option 2: have an "on cams down" function that checks if chica, bonnie, or freddy are in the room
        if(!cams_are_up){
        }*/
        return;
    }
    if (!frame_multiple(CHICA_FRAMECOUNT)) {
        return;
    }
    vbaprint("Chica movement opp\n");
    if (!try_move(&CHICA)) { // TODO debug merge into one if statement
        return;
    }
    vbaprint("chica success\n");

    switch (CHICA.room_num) {
        case ROOM_STAGE:
            chica_move(ROOM_DINING, cams_are_up, selected_cam);
            break;
        case ROOM_DINING:
            chica_move(rnd_max(2) ? ROOM_KITCHEN : ROOM_RESTROOMS, cams_are_up, selected_cam);
            break;
        case ROOM_RESTROOMS:
            chica_move(rnd_max(2) ? ROOM_KITCHEN : ROOM_EAST, cams_are_up, selected_cam);
            break;
        case ROOM_KITCHEN:
            chica_move(rnd_max(2) ? ROOM_RESTROOMS : ROOM_EAST, cams_are_up, selected_cam);
            break;
        case ROOM_EAST:
            chica_move(rnd_max(2) ? ROOM_DINING : ROOM_EAST_CORNER, cams_are_up, selected_cam);
            break;
        case ROOM_EAST_CORNER:
            if (rnd_max(2)) {
                chica_move(ROOM_EAST, cams_are_up, selected_cam);
            } else {
                chica_move(ROOM_RIGHT_DOOR, cams_are_up, selected_cam);
                Equipment.force_light_off(RIGHT_LIGHT);
                // TODO set windowscare to play
                vbaprint("chica at window\n");
            }
            break;
        case ROOM_RIGHT_DOOR:
            if (Equipment.is_on(RIGHT_DOOR)) { // if door is closed
                chica_move(ROOM_DINING, cams_are_up, selected_cam);
                Equipment.force_light_off(RIGHT_LIGHT);
            } else {
                chica_move(ROOM_OFFICE, cams_are_up, selected_cam);
                Equipment.disable(RIGHT_LIGHT);
                Equipment.disable(RIGHT_DOOR);
                // TODO initiate in office phase
                CHICA.timer = -1; // ensure timer is reset
            }
            break;
        default:
            break;
    }
}

void chica_on_night_start() {
    CHICA.room_num = CHICA.starting_room;
    CHICA.close_far = 0;
}

struct Animatronic CHICA = {
    .update = &update_chica,
    .starting_room = ROOM_STAGE,
    .timer = -1,
    .on_night_start = &chica_on_night_start
};