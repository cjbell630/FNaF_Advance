#include "animatronics.h"
#include "DWedit/debug.h"
#include "util/random.h"
#include "util/util.h"
#include "game/room_names.h"
#include <stdio.h>

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

/*  BONNIE  */

// TODO this and chicas code are so similar, combine them somehow
void update_bonnie(int frame_num, bool cams_are_up, enum RoomNames selected_cam) {
    if (!is_multiple(frame_num, BONNIE_FRAMECOUNT)) {
        return;
    }
    vbaprint("Bonnie movement opp\n"); // TODO debug merge into one if statement
    if (!try_move(&BONNIE)) {
        return;
    }
    vbaprint("bonnie success\n");

    switch (BONNIE.room_num) {
        case ROOM_STAGE:
            BONNIE.room_num = rnd_max(2) ? ROOM_BACKSTAGE : ROOM_DINING;
            break;
        case ROOM_DINING:
            BONNIE.room_num = rnd_max(2) ? ROOM_BACKSTAGE : ROOM_WEST;
            break;
        case ROOM_BACKSTAGE:
            BONNIE.room_num = rnd_max(2) ? ROOM_DINING : ROOM_WEST;
            break;
        case ROOM_WEST:
            BONNIE.room_num = rnd_max(2) ? ROOM_CLOSET : ROOM_WEST_CORNER;
            break;
        case ROOM_CLOSET:
            BONNIE.room_num = rnd_max(2) ? ROOM_LEFT_DOOR : ROOM_WEST;
            break;
        case ROOM_WEST_CORNER:
            BONNIE.room_num = rnd_max(2) ? ROOM_CLOSET : ROOM_LEFT_DOOR;
            break;
        case ROOM_LEFT_DOOR:
            BONNIE.room_num = /* TODO DOOR IS UP */true ? ROOM_OFFICE : ROOM_DINING;
            break;
        default:
            break;
    }
    // TODO stun camera
}

struct Animatronic BONNIE = {
        .update = update_bonnie,
        .starting_room = ROOM_STAGE
};

/*  CHICA  */

// TODO this and chicas code are so similar, combine them somehow
void update_chica(int frame_num, bool cams_are_up, enum RoomNames selected_cam) {
    if (!is_multiple(frame_num, CHICA_FRAMECOUNT)) {
        return;
    }
    vbaprint("Chica movement opp\n");
    if (!try_move(&CHICA)) { // TODO debug merge into one if statement
        return;
    }
    vbaprint("chica success\n");

    switch (CHICA.room_num) {
        case ROOM_STAGE:
            CHICA.room_num = ROOM_DINING;
            break;
        case ROOM_DINING:
            CHICA.room_num = rnd_max(2) ? ROOM_KITCHEN : ROOM_RESTROOMS;
            break;
        case ROOM_RESTROOMS:
            CHICA.room_num = rnd_max(2) ? ROOM_KITCHEN : ROOM_EAST;
            break;
        case ROOM_KITCHEN:
            CHICA.room_num = rnd_max(2) ? ROOM_RESTROOMS : ROOM_EAST;
            break;
        case ROOM_EAST:
            CHICA.room_num = rnd_max(2) ? ROOM_DINING : ROOM_EAST_CORNER;
            break;
        case ROOM_EAST_CORNER:
            CHICA.room_num = rnd_max(2) ? ROOM_EAST : ROOM_RIGHT_DOOR;
            break;
        case ROOM_RIGHT_DOOR:
            CHICA.room_num = /* TODO DOOR IS UP */true ? ROOM_OFFICE : ROOM_DINING;
            break;
        default:
            break;
    }
    // TODO stun camera
}

struct Animatronic CHICA = {
        .update = update_chica,
        .starting_room = ROOM_STAGE
};


/*  FREDDY  */

void update_freddy(int frame_num, bool cams_are_up, enum RoomNames selected_cam) {
    if (!is_multiple(frame_num, FREDDY_FRAMECOUNT)) {
        return;
    }
    vbaprint("Freddy movement opp\n");

    if (try_move(&FREDDY)) {
        vbaprint("freddy success\n");
        //change_room(FREDDY, ROOM_EAST);
    }
}

struct Animatronic FREDDY = {
        .update = &update_freddy,
        .starting_room = ROOM_STAGE
};

/*  FOXY  */

bool foxy_at_cove(int frame_num, bool cams_are_up) {
    /* HANDLE STUN TIMER */
    if (cams_are_up) {
        if (is_multiple(frame_num, 6/*TODO magic num*/)) {
            FOXY.timer = rnd_max(1000) + 50; // TODO this could just be called when the camera is closed
        }
    } else {
        FOXY.timer--; // TODO theoretically could overflow but shouldn't
    }
    /* END HANDLE STUN TIMER */
    if (FOXY.timer < 1 && is_multiple(frame_num, FOXY_FRAMECOUNT)) {
        vbaprint("foxy success\n");
        FOXY.phase++;
        return true;
    }
    return false;
}

void update_foxy(int frame_num, bool cams_are_up, enum RoomNames selected_cam) {
    switch (FOXY.phase) {
        case FOXY_CLOSED:
        case FOXY_PEEK:
            foxy_at_cove(frame_num, cams_are_up);
            break;
        case FOXY_STAND:
            if (foxy_at_cove(frame_num, cams_are_up)) {
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
            vbaprint("foxy is attacking\n");// TODO steal power or jumpscare
            if (/* TODO game does not end */true) {
                FOXY.phase = rnd_max(2) ? FOXY_PEEK : FOXY_STAND; // TODO is this correct?
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

void on_night_start(int night_num) {
    // TODO a little cringe, maybe there's a better way to write this
    switch (night_num) {
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
}

void update_anims(int frame_num, bool cams_are_up, enum RoomNames selected_cam) {
    // TODO can I put them in a list or something and do for each, and then say if frame mult of internal attribute
    BONNIE.update(frame_num, cams_are_up, selected_cam);
    FREDDY.update(frame_num, cams_are_up, selected_cam);
    CHICA.update(frame_num, cams_are_up, selected_cam);
    FOXY.update(frame_num, cams_are_up, selected_cam);
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
            break;
        case 3:
        case 4:
            BONNIE.lvl++;
            FOXY.lvl++;
            CHICA.lvl++;
            break;
        default:
            break;
    }
}

// TODO define this in camera.c?
char get_room_occupants(enum RoomNames room) {
    return ((BONNIE.room_num == room) << 3) | ((CHICA.room_num == room) << 2) |
           ((FREDDY.room_num == room) << 1) | (FOXY.room_num == room);
}

struct AnimatronicsWrapper Animatronics = {
        .update = update_anims,
        .on_night_start = on_night_start,
        .set_levels = set_levels,
        .get_room_occupants = get_room_occupants,
        .on_hour = on_hour
};