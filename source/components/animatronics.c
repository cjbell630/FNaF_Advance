#include "animatronics.h"
#include "DWedit/debug.h"
#include "util/random.h"
#include "util/util.h"
#include "game/room_names.h"
#include "game_state.h"
#include "equipment.h"
#include "graphics.h"
#include "power.h"
#include <stdio.h>

/* PREREQS */
// some functions in this file use the frame_multiple and NIGHT_NUM globals

/* CONSTANTS */

enum FoxyPhases {
    FOXY_CLOSED, FOXY_PEEK, FOXY_STAND, FOXY_GONE, FOXY_RUN, FOXY_ATTACK
};
enum FreddyPhases {
    FREDDY_SLEEPING, FREDDY_WONT_MOVE, FREDDY_MIGHT_MOVE, FREDDY_WILL_MOVE, FREDDY_EAST_CORNER, FREDDY_READY_TO_ATTACK
};

/* END CONSTANTS */

/**
 * The value that Freddy's timer will start at. To be set at the start of each night.
 * Equal to `1000-(lvl*100)`
 */
int FREDDY_TIMER_START;


/**
 * Rolls to see if an animatronic can move.
 * The odds of moving at each opportunity (opportunity frequency differs for each anim) are
 * lvl / MAX_LEVEL
 * Where lvl is the animatronic's level
 * Ex. If the animatronic is set to level 1, there is a 1/20 chance it can move
 *     If the animatronic is set to level 19, there is a 19/20 chance it can move
 * @param anim a pointer to the anim to check for
 * @return true if the anim can move on this opportunity, false if not
 */
bool try_move(struct Animatronic *anim) {
    return anim->lvl >= (rnd_max(MAX_LEVEL) + 1);
}

// TODO make this less cringe
void bonnie_move(enum RoomNames room, bool cams_are_up, enum RoomNames selected_cam) {
    if (cams_are_up && (selected_cam == room || selected_cam == BONNIE.room_num)) {
        Graphics.stun_cams(selected_cam);
    }
    BONNIE.close_far = room == ROOM_DINING ? rnd_max(2) : 0;
    BONNIE.room_num = room;
}

void chica_move(enum RoomNames room, bool cams_are_up, enum RoomNames selected_cam) {
    if (cams_are_up && (selected_cam == room || selected_cam == CHICA.room_num)) {
        Graphics.stun_cams(selected_cam);
    }
    CHICA.close_far = (room == ROOM_DINING || room == ROOM_EAST || room == ROOM_RESTROOMS) ? rnd_max(2) : 0;
    CHICA.room_num = room;
}

void trigger_jumpscare(enum Jumpscares character, bool show_cams_animation) {
    JUMPSCARER = character;
    SHOW_CAM_ANIM_ON_JUMPSCARE = show_cams_animation;
    GAME_PHASE = NIGHT_JUMPSCARE;
}

/*  BONNIE  */

// TODO this and chicas code are so similar, combine them somehow
void update_bonnie(bool cams_are_up, enum RoomNames selected_cam) {
    if (BONNIE.room_num == ROOM_OFFICE) {
        if(BONNIE.timer == -1) { // if the cams have not been lifted since bonnie got in the office
            if(cams_are_up){
                BONNIE.timer = 1800; // TODO magic num; 30s/1800f timer until jumpscare
            }
            return;
        }
        if(BONNIE.timer < 1 || !cams_are_up){ // if the timer has been set, and has reached 0 or the cams are down
            trigger_jumpscare(JUMPSCARE_BONNIE, cams_are_up);
            return;
        }
        // if the cams are up and the timer is ticking
        BONNIE.timer--;

        /*
         * TODO option 1: check if cams are down here, and trigger jumpscare
         * (in this case, the cam down animation will have already been started so it might look funny)
         * option 2: have an "on cams down" function that checks if chica, bonnie, or freddy are in the room
        if(!cams_are_up){
        }*/
        return;
    }
    if (!frame_multiple(BONNIE_FRAMECOUNT)) {
        return;
    }
    vbaprint("Bonnie movement opp\n"); // TODO debug merge into one if statement
    if (!try_move(&BONNIE)) {
        return;
    }
    vbaprint("bonnie success\n");

    switch (BONNIE.room_num) {
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
            bonnie_move(rnd_max(2) ? ROOM_LEFT_DOOR : ROOM_WEST, cams_are_up, selected_cam);
            break;
        case ROOM_WEST_CORNER:
            if (rnd_max(2)) {
                bonnie_move(ROOM_CLOSET, cams_are_up, selected_cam);
            } else {
                bonnie_move(ROOM_LEFT_DOOR, cams_are_up, selected_cam);
                Equipment.force_light_off(LEFT_LIGHT);
                // TODO set windowscare to play
            }
            break;
        case ROOM_LEFT_DOOR:
            if (Equipment.is_on(LEFT_DOOR)) { // if left door is closed
                bonnie_move(ROOM_DINING, cams_are_up, selected_cam);
                Equipment.force_light_off(LEFT_LIGHT);
            } else {
                BONNIE.room_num = ROOM_OFFICE;
                Equipment.disable(LEFT_LIGHT);
                Equipment.disable(LEFT_DOOR);
                // TODO initiate in office phase
                BONNIE.timer = -1;
            }
            break;
        default:
            break;
    }
}

struct Animatronic BONNIE = {
        .update = update_bonnie,
        .starting_room = ROOM_STAGE
};

/*  CHICA  */

// TODO this and chicas code are so similar, combine them somehow
void update_chica(bool cams_are_up, enum RoomNames selected_cam) {
    if (CHICA.room_num == ROOM_OFFICE) {
        if(CHICA.timer == -1) { // if the cams have not been lifted since chica got in the office
            if(cams_are_up){
                CHICA.timer = 1800; // TODO magic num; 30s/1800f timer until jumpscare
            }
            return;
        }
        if(CHICA.timer < 1 || !cams_are_up){ // if the timer has been set, and has reached 0 or the cams are down
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

struct Animatronic CHICA = {
        .update = update_chica,
        .starting_room = ROOM_STAGE,
        .timer = -1
};


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
    } else if (
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

struct Animatronic FREDDY = {
        .update = &update_freddy,
        .starting_room = ROOM_STAGE
};

/*  FOXY  */

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
                FOXY.phase = FOXY_RUN;// TODO external stuff for foxy running
                FOXY.room_num = ROOM_WEST;
                FOXY.timer = 100 /* TODO magic num, can be used to show run animation*/;
            }
            break;
        case FOXY_RUN:
            FOXY.timer--;
            if (FOXY.timer < 1) {
                FOXY.phase = FOXY_ATTACK;// TODO external stuff for jumpscare
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

struct Animatronic FOXY = {
        .update = &update_foxy,
        .starting_room = ROOM_PIRATE
};


/*  COLLECTIVE  */
void set_levels(int fr_lvl, int b_lvl, int c_lvl, int fo_lvl) { // TODO make these orders consistent or something please
    BONNIE.lvl = b_lvl;
    FREDDY.lvl = fr_lvl;
    CHICA.lvl = c_lvl;
    FOXY.lvl = fo_lvl;
}

void on_night_start() {
    // TODO a little cringe, maybe there's a better way to write this
    switch (NIGHT_NUM) {
        case 1:
            set_levels(NIGHT_1_START_LEVELS);
            break;
        case 2:
            set_levels(NIGHT_2_START_LEVELS);
            break;
        case 3:
            set_levels(NIGHT_3_START_LEVELS);
            break;
        case 4:
            set_levels(NIGHT_4_START_LEVELS);
            break;
        case 5:
            set_levels(NIGHT_5_START_LEVELS);
            break;
        case 6:
            set_levels(NIGHT_6_START_LEVELS);
            break;
        default: // custom night
            break;
    }
    BONNIE.room_num = BONNIE.starting_room;
    FOXY.room_num = FOXY.starting_room;
    FREDDY.room_num = FREDDY.starting_room;
    CHICA.room_num = CHICA.starting_room;
    FOXY.phase = FREDDY.phase = 0;
    FOXY.timer = FREDDY.timer = 0;
    BONNIE.close_far = CHICA.close_far = 0;
    FREDDY_TIMER_START = 1000 - (100 * FREDDY.lvl);
}

void update_anims(bool cams_are_up, enum RoomNames selected_cam) {
    // TODO can I put them in a list or something and do for each, and then say if frame mult of internal attribute
    BONNIE.update(cams_are_up, selected_cam);
    FREDDY.update(cams_are_up, selected_cam);
    CHICA.update(cams_are_up, selected_cam);
    FOXY.update(cams_are_up, selected_cam);
}

/**
 * To be called when the hour changes ex. 1->2 3->4
 *
 * @param hour the CURRENT hour
 */
void on_hour(int hour) {
    switch (hour) {
        case 2:
            BONNIE.lvl++;
            vbaprint("bonnie level increased\n");
            break;
        case 3:
        case 4:
            BONNIE.lvl++;
            FOXY.lvl++;
            CHICA.lvl++;
            vbaprint("bonnie, foxy, and chica levels increased\n");
            break;
        default:
            break;
    }
}

// TODO define this in camera.c?
u8 get_room_occupants(enum RoomNames room) {
    return ((FOXY.room_num == room) << 3) | ((CHICA.room_num == room) << 2) |
           ((BONNIE.room_num == room) << 1) | (FREDDY.room_num == room);
}

struct AnimatronicsWrapper Animatronics = {
        .update = update_anims,
        .on_night_start = on_night_start,
        .set_levels = set_levels,
        .get_room_occupants = get_room_occupants,
        .on_hour = on_hour
};