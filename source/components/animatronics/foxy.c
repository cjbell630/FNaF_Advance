#include "foxy.h"
#include "DWedit/debug.h"
#include "game/room_names.h"
#include "animatronic.h"
#include "util/random.h"
#include "components/equipment.h"
#include "components/power.h"

enum FoxyPhases {
    FOXY_CLOSED, FOXY_PEEK, FOXY_STAND, FOXY_GONE, FOXY_RUN, FOXY_ATTACK
};

bool foxy_at_cove(bool cams_are_up) {
    /* HANDLE STUN TIMER */
    if (cams_are_up) {
        if (frame_multiple(6/*TODO magic num*/)) {
            FOXY.timer = rnd_max(1000) + 50; // TODO this could just be called when the camera is closed
        }
    } else {
        FOXY.timer--; // TODO theoretically could overflow but shouldn't
    }
    /* END HANDLE STUN TIMER */
    if (FOXY.timer < 1 && frame_multiple(FOXY_FRAMECOUNT) && try_move(&FOXY)) {
        vbaprint("foxy success\n");
        FOXY.phase++;
        return true;
    }
    return false;
}

void update_foxy(bool cams_are_up, enum RoomNames selected_cam) {
    // TODO do the later phases really not need a move check?
    switch (FOXY.phase) {
        case FOXY_CLOSED:
        case FOXY_PEEK:
            foxy_at_cove(cams_are_up);
            break;
        case FOXY_STAND:
            if (foxy_at_cove(cams_are_up)) {
                // TODO external stuff for transitioning to GONE
                FOXY.timer = 1500/* TODO magic num*/;
            }
            break;
        case FOXY_GONE:
            FOXY.timer--;
            if (FOXY.timer < 1) {
                FOXY.phase = FOXY_ATTACK;
                FOXY.room_num = ROOM_LEFT_DOOR;
                break; // TODO external stuff for jumpscare
            }
            if (selected_cam == ROOM_WEST) {
                FOXY.phase = FOXY_RUN; // TODO external stuff for foxy running
                FOXY.room_num = ROOM_WEST;
                FOXY.timer = 100 /* TODO magic num, can be used to show run animation*/;
            }
            break;
        case FOXY_RUN:
            FOXY.timer--;
            if (FOXY.timer < 1) {
                FOXY.phase = FOXY_ATTACK; // TODO external stuff for jumpscare
                FOXY.room_num = ROOM_LEFT_DOOR;
            }
            break;
        case FOXY_ATTACK:
            vbaprint("foxy is attacking\n");
            if (Equipment.is_on(LEFT_DOOR)) { // if door is closed
                Power.on_foxy_attack();
                FOXY.phase = rnd_max(2) ? FOXY_PEEK : FOXY_STAND; // TODO is this correct?
            } else {
                trigger_jumpscare(JUMPSCARE_FOXY, cams_are_up);
            }
            break;
        default:
            break;
    }
}

void foxy_on_night_start() {
    FOXY.room_num = FOXY.starting_room;
    FOXY.phase = 0;
    FOXY.timer = 0;
}

struct Animatronic FOXY = {
    .update = &update_foxy,
    .starting_room = ROOM_PIRATE,
    .on_night_start = &foxy_on_night_start
};
