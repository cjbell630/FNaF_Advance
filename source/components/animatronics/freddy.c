#include "freddy.h"
#include "bonnie.h"
#include "chica.h"
#include "DWedit/debug.h"
#include "game/room_names.h"
#include "animatronic.h"
#include "util/random.h"
#include "components/equipment.h"

enum FreddyPhases {
    FREDDY_SLEEPING, FREDDY_WONT_MOVE, FREDDY_MIGHT_MOVE, FREDDY_WILL_MOVE, FREDDY_EAST_CORNER, FREDDY_READY_TO_ATTACK
};

/**
 * The value that Freddy's timer will start at. To be set at the start of each night.
 * Equal to `1000-(lvl*100)`
 */
int FREDDY_TIMER_START;

/*  FREDDY  */

void move_freddy() {
    switch (AnimatronicFreddy.room_num) {
        case ROOM_STAGE:
            AnimatronicFreddy.room_num = ROOM_DINING;
            break;
        case ROOM_DINING:
            AnimatronicFreddy.room_num = ROOM_RESTROOMS;
            break;
        case ROOM_RESTROOMS:
            AnimatronicFreddy.room_num = ROOM_KITCHEN;
            break;
        case ROOM_KITCHEN:
            AnimatronicFreddy.room_num = ROOM_EAST;
            break;
        case ROOM_EAST:
            AnimatronicFreddy.room_num = ROOM_EAST_CORNER;
            AnimatronicFreddy.phase = FREDDY_EAST_CORNER;
            vbaprint("Freddy in the east corner\n");
            break;
        default:
            break;
    }
}

void update_freddy(bool cams_are_up, enum RoomNames selected_cam) {
    if (AnimatronicFreddy.room_num == ROOM_OFFICE) {
        if (cams_are_up) {
            AnimatronicFreddy.timer = 60; // TODO magic number: 1s/60f timer for jumpscares
            // TODO kinda unnecessary to reset every frame but that's how the og game is written
            return;
        }
        if (0 < AnimatronicFreddy.timer) { // if timer is still ticking down
            AnimatronicFreddy.timer--;
            return;
        }
        if (rnd_max(5) == 0) {
            trigger_jumpscare(JUMPSCARE_FREDDY_STD, cams_are_up);
            return;
        }
        AnimatronicFreddy.timer = 60;
        return;
    }
    if (cams_are_up) { // if cams are up and not a movement opportunity
        switch (AnimatronicFreddy.phase) {
            case FREDDY_MIGHT_MOVE:
                // reset timer if he is being looked at
                if (selected_cam == AnimatronicFreddy.room_num) {
                    AnimatronicFreddy.timer = FREDDY_TIMER_START; // TODO same as Foxy this could just be set when cams are closed
                } else {
                    AnimatronicFreddy.timer--;
                }
                break;
            case FREDDY_READY_TO_ATTACK:
                if (selected_cam != ROOM_EAST_CORNER) {
                    vbaprint("Freddy attacking\n");
                    if (Equipment.is_on(RIGHT_DOOR)) { // if door is closed
                        AnimatronicFreddy.room_num = ROOM_EAST;
                    } else {
                        AnimatronicFreddy.room_num = ROOM_OFFICE;
                        AnimatronicFreddy.timer = 60; // TODO magic number: 1s/60f timer for jumpscares
                    }
                    AnimatronicFreddy.phase = FREDDY_WONT_MOVE;
                }
                break;
            default:
                break;
        }
        return;
    }
    if (
        !frame_multiple(AnimatronicFreddy.movement_framecount) ||
        !try_move(&AnimatronicFreddy)
    ) { // if cams are down and not a successful movement opportunity
        if (AnimatronicFreddy.phase == FREDDY_MIGHT_MOVE) {
            AnimatronicFreddy.timer--;
        }
        return;
    }


    // if cams are down and successful movement opportunity
    vbaprint("Freddy success\n");


    switch (AnimatronicFreddy.phase) {
        case FREDDY_SLEEPING: // TODO confirm this logic
            if (AnimatronicBonnie.room_num != ROOM_STAGE && AnimatronicChica.room_num != ROOM_STAGE) {
                AnimatronicFreddy.phase = FREDDY_MIGHT_MOVE;
                AnimatronicFreddy.timer = FREDDY_TIMER_START;
                vbaprint("Freddy is awake\n");
            }
            break;
        case FREDDY_WONT_MOVE:
            AnimatronicFreddy.phase = FREDDY_MIGHT_MOVE;
            AnimatronicFreddy.timer = FREDDY_TIMER_START;
            vbaprint("Freddy might move\n");
            break;
        case FREDDY_MIGHT_MOVE:
            AnimatronicFreddy.timer--;
            if (AnimatronicFreddy.timer < 1) {
                AnimatronicFreddy.phase = FREDDY_WILL_MOVE;
                vbaprint("Freddy will move\n");
            }
            break;
        case FREDDY_WILL_MOVE:
            vbaprint("Freddy moved\n");
            AnimatronicFreddy.phase = FREDDY_WONT_MOVE; // do this before moving bc moving to east corner overwrites his phase
            move_freddy();
            break;
        case FREDDY_EAST_CORNER:
            vbaprint("Freddy ready to attack\n");
            AnimatronicFreddy.phase = FREDDY_READY_TO_ATTACK;
        default:
            break;
    }
}

void freddy_on_night_start() {
    FREDDY_TIMER_START = 1000 - (100 * AnimatronicFreddy.lvl);
    AnimatronicFreddy.phase = 0;
    AnimatronicFreddy.timer = 0;
    AnimatronicFreddy.room_num = AnimatronicFreddy.starting_room;
}

struct Animatronic AnimatronicFreddy = {
    .update = &update_freddy,
    .starting_room = ROOM_STAGE,
    .movement_framecount = 181,
    .on_night_start = &freddy_on_night_start
};