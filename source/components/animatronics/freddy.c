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
    switch (FREDDY.room_num) {
        case ROOM_STAGE:
            FREDDY.room_num = ROOM_DINING;
            break;
        case ROOM_DINING:
            FREDDY.room_num = ROOM_RESTROOMS;
            break;
        case ROOM_RESTROOMS:
            FREDDY.room_num = ROOM_KITCHEN;
            break;
        case ROOM_KITCHEN:
            FREDDY.room_num = ROOM_EAST;
            break;
        case ROOM_EAST:
            FREDDY.room_num = ROOM_EAST_CORNER;
            FREDDY.phase = FREDDY_EAST_CORNER;
            vbaprint("Freddy in the east corner\n");
            break;
        default:
            break;
    }
}

void update_freddy(bool cams_are_up, enum RoomNames selected_cam) {
    if (FREDDY.room_num == ROOM_OFFICE) {
        if (cams_are_up) {
            FREDDY.timer = 60; // TODO magic number: 1s/60f timer for jumpscares
            // TODO kinda unnecessary to reset every frame but that's how the og game is written
            return;
        }
        if (0 < FREDDY.timer) { // if timer is still ticking down
            FREDDY.timer--;
            return;
        }
        if (rnd_max(5) == 0) {
            trigger_jumpscare(JUMPSCARE_FREDDY_STD, cams_are_up);
            return;
        }
        FREDDY.timer = 60;
        return;
    }
    if (cams_are_up) { // if cams are up and not a movement opportunity
        switch (FREDDY.phase) {
            case FREDDY_MIGHT_MOVE:
                // reset timer if he is being looked at
                if (selected_cam == FREDDY.room_num) {
                    FREDDY.timer = FREDDY_TIMER_START; // TODO same as Foxy this could just be set when cams are closed
                } else {
                    FREDDY.timer--;
                }
                break;
            case FREDDY_READY_TO_ATTACK:
                if (selected_cam != ROOM_EAST_CORNER) {
                    vbaprint("Freddy attacking\n");
                    if (Equipment.is_on(RIGHT_DOOR)) { // if door is closed
                        FREDDY.room_num = ROOM_EAST;
                    } else {
                        FREDDY.room_num = ROOM_OFFICE;
                        FREDDY.timer = 60; // TODO magic number: 1s/60f timer for jumpscares
                    }
                    FREDDY.phase = FREDDY_WONT_MOVE;
                }
                break;
            default:
                break;
        }
        return;
    }
    if (
        !frame_multiple(FREDDY_FRAMECOUNT) ||
        !try_move(&FREDDY)
    ) { // if cams are down and not a successful movement opportunity
        if (FREDDY.phase == FREDDY_MIGHT_MOVE) {
            FREDDY.timer--;
        }
        return;
    }


    // if cams are down and successful movement opportunity
    vbaprint("Freddy success\n");


    switch (FREDDY.phase) {
        case FREDDY_SLEEPING: // TODO confirm this logic
            if (BONNIE.room_num != ROOM_STAGE && CHICA.room_num != ROOM_STAGE) {
                FREDDY.phase = FREDDY_MIGHT_MOVE;
                FREDDY.timer = FREDDY_TIMER_START;
                vbaprint("Freddy is awake\n");
            }
            break;
        case FREDDY_WONT_MOVE:
            FREDDY.phase = FREDDY_MIGHT_MOVE;
            FREDDY.timer = FREDDY_TIMER_START;
            vbaprint("Freddy might move\n");
            break;
        case FREDDY_MIGHT_MOVE:
            FREDDY.timer--;
            if (FREDDY.timer < 1) {
                FREDDY.phase = FREDDY_WILL_MOVE;
                vbaprint("Freddy will move\n");
            }
            break;
        case FREDDY_WILL_MOVE:
            vbaprint("Freddy moved\n");
            FREDDY.phase = FREDDY_WONT_MOVE; // do this before moving bc moving to east corner overwrites his phase
            move_freddy();
            break;
        case FREDDY_EAST_CORNER:
            vbaprint("Freddy ready to attack\n");
            FREDDY.phase = FREDDY_READY_TO_ATTACK;
        default:
            break;
    }
}

void freddy_on_night_start() {
    FREDDY_TIMER_START = 1000 - (100 * FREDDY.lvl);
}

struct Animatronic FREDDY = {
    .update = &update_freddy,
    .starting_room = ROOM_STAGE,
    .on_night_start = &freddy_on_night_start
};