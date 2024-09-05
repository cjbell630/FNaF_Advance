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
void update_bonnie(int frame_num) {
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
void update_chica(int frame_num) {
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

void update_freddy(int frame_num) {
    if (!is_multiple(frame_num, FREDDY_FRAMECOUNT)) {
        return;
    }
    vbaprint("Freddy movement opp\n");

    if (try_move(&FREDDY)) {
        vbaprint("freddy succ\n");
        //change_room(FREDDY, ROOM_EAST);
    }
}

struct Animatronic FREDDY = {
        .update = &update_freddy,
        .starting_room = ROOM_STAGE
};

/*  FOXY  */

struct Animatronic FOXY = {
        .update = &update_freddy, // TODO
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
}

void update_anims(int frame_num) {
    // TODO can I put them in a list or something and do for each, and then say if frame mult of internal attribute
    BONNIE.update(frame_num);
    FREDDY.update(frame_num);
    CHICA.update(frame_num);
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