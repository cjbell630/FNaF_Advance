#include "bonnie.h"
#include "DWedit/debug.h"
#include "game/room_names.h"
#include "animatronic.h"
#include "util/random.h"
#include "components/equipment.h"
#include "components/graphics.h"

// TODO make this less cringe
void bonnie_move(enum RoomNames room, bool cams_are_up, enum RoomNames selected_cam) {
    if (cams_are_up && (selected_cam == room || selected_cam == AnimatronicBonnie.room_num)) {
        Graphics.stun_cams(selected_cam);
    }
    AnimatronicBonnie.close_far = room == ROOM_DINING ? rnd_max(2) : 0;
    AnimatronicBonnie.room_num = room;
}

/*  BONNIE  */

// TODO this and chicas code are so similar, combine them somehow
void update_bonnie(bool cams_are_up, enum RoomNames selected_cam) {
    if (AnimatronicBonnie.room_num == ROOM_OFFICE) {
        if (AnimatronicBonnie.timer == -1) { // if the cams have not been lifted since bonnie got in the office
            if (cams_are_up) {
                AnimatronicBonnie.timer = 1800; // TODO magic num; 30s/1800f timer until jumpscare
            }
            return;
        }
        if (AnimatronicBonnie.timer < 1 || !cams_are_up) { // if the timer has been set, and has reached 0 or the cams are down
            trigger_jumpscare(JUMPSCARE_BONNIE, cams_are_up);
            return;
        }
        // if the cams are up and the timer is ticking
        AnimatronicBonnie.timer--;

        /*
         * TODO option 1: check if cams are down here, and trigger jumpscare
         * (in this case, the cam down animation will have already been started so it might look funny)
         * option 2: have an "on cams down" function that checks if chica, bonnie, or freddy are in the room
        if(!cams_are_up){
        }*/
        return;
    }
    if (!frame_multiple(AnimatronicBonnie.movement_framecount)) {
        return;
    }
    vbaprint("Bonnie movement opp\n"); // TODO debug merge into one if statement
    if (!try_move(&AnimatronicBonnie)) {
        return;
    }
    vbaprint("bonnie success\n");

    switch (AnimatronicBonnie.room_num) {
        case ROOM_STAGE:
            bonnie_move(rnd_max(2) ? ROOM_BACKSTAGE : ROOM_DINING, cams_are_up, selected_cam);
            break;
        case ROOM_DINING:
            bonnie_move(rnd_max(2) ? ROOM_BACKSTAGE : ROOM_WEST, cams_are_up, selected_cam);
            break;
        case ROOM_BACKSTAGE:
            bonnie_move(rnd_max(2) ? ROOM_DINING : ROOM_WEST, cams_are_up, selected_cam);
            break;
        case ROOM_WEST:
            bonnie_move(rnd_max(2) ? ROOM_CLOSET : ROOM_WEST_CORNER, cams_are_up, selected_cam);
            break;
        case ROOM_CLOSET:
            if (rnd_max(2)) {
                bonnie_move(ROOM_WEST, cams_are_up, selected_cam);
            } else {
                bonnie_move(ROOM_LEFT_DOOR, cams_are_up, selected_cam);
                Equipment.force_light_off(LEFT_LIGHT);
                vbaprint("bonnie at window\n");
                // TODO set windowscare to play
            }
            break;
        case ROOM_WEST_CORNER:
            if (rnd_max(2)) {
                bonnie_move(ROOM_CLOSET, cams_are_up, selected_cam);
            } else {
                bonnie_move(ROOM_LEFT_DOOR, cams_are_up, selected_cam);
                Equipment.force_light_off(LEFT_LIGHT);
                vbaprint("bonnie at window\n");
                // TODO set windowscare to play
            }
            break;
        case ROOM_LEFT_DOOR:
            if (Equipment.is_on(LEFT_DOOR)) { // if left door is closed
                bonnie_move(ROOM_DINING, cams_are_up, selected_cam);
                Equipment.force_light_off(LEFT_LIGHT);
            } else {
                AnimatronicBonnie.room_num = ROOM_OFFICE;
                Equipment.disable(LEFT_LIGHT);
                Equipment.disable(LEFT_DOOR);
                // TODO initiate in office phase
                vbaprint("bonnie in office!!\n");
                AnimatronicBonnie.timer = -1;
            }
            break;
        default:
            break;
    }
}


void bonnie_on_night_start() {
    AnimatronicBonnie.room_num = AnimatronicBonnie.starting_room;
    AnimatronicBonnie.close_far = 0;
}

struct Animatronic AnimatronicBonnie = {
    .update = &update_bonnie,
    .starting_room = ROOM_STAGE,
    .movement_framecount = 298,
    .on_night_start = &bonnie_on_night_start
};