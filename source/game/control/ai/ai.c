//
// https://www.pvv.ntnu.no/~hakonhal/main.cgi/c/classes/
//

#include "ai.h"
#include "DWedit/debug.h"
#include "util/random.h"
#include "util/util.h"
#include "game/control/cameras/room_names.h"
#include <stdio.h>

/**
 * Gets a random empty room from the provided list and returns it
 * @param rooms the list of rooms to choose from
 * @param num_rooms the length of said list
 * @return a randomly selected empty room from the list, or -1 if they are all full
 */

bool try_move_to_empty_room_from(struct Animatronic *anim, const enum RoomNames rooms[], int num_rooms) { //TODO: should this really be an array?
    uint status = GET_N_SET_BITS(num_rooms); // 11 bits, one for each room
    int rand_index;
    while (status > 0) { //TODO: could use rnd_exclude if I made it take more nums
        rand_index = rnd_max(num_rooms);
        if (Animatronics.get_room_occupants(rooms[rand_index]) == 0/*TODO use macro ROOM_EMPTY*/) { // if the found room is empty
            anim->room_num = rooms[rand_index]; // TODO if bonnie or chica stun camera
            return true;
        }
        status &= ~(1 << rand_index); // turn off the bit corresponding to the random room num
    }
    return false;
}

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
    vbaprint("Bonnie movement opp\n");
    if (!try_move(&BONNIE)) {
        vbaprint("bonnie fail\n"); // TODO debug, remove
        return;
    }
    vbaprint("bonnie success\n");
    bool waiting = true;
    enum RoomNames rooms[2];

    switch (BONNIE.room_num) {
        case ROOM_STAGE:
            rooms[0] = ROOM_BACKSTAGE;
            rooms[1] = ROOM_DINING;
            break;
        case ROOM_DINING:
            rooms[0] = ROOM_BACKSTAGE;
            rooms[1] = ROOM_WEST;
            break;
        case ROOM_BACKSTAGE:
            rooms[0] = ROOM_DINING;
            rooms[1] = ROOM_WEST;
            break;
        case ROOM_WEST:
            rooms[0] = ROOM_CLOSET;
            rooms[1] = ROOM_WEST_CORNER;
            break;
        case ROOM_CLOSET:
            rooms[0] = ROOM_LEFT_DOOR;
            rooms[1] = ROOM_WEST;
            break;
        case ROOM_WEST_CORNER:
            rooms[0] = ROOM_CLOSET;
            rooms[1] = ROOM_LEFT_DOOR;
            break;
        case ROOM_LEFT_DOOR:
            BONNIE.room_num = /* TODO DOOR IS UP */true ? ROOM_OFFICE : ROOM_DINING;
            // TODO stun camera
            waiting = false;
            break;
        default:
            waiting = false;
            break;
    }
    if (waiting) {
        try_move_to_empty_room_from(&BONNIE, rooms, 2);
    }
}

struct Animatronic BONNIE = {
        .update = &update_bonnie,
        .starting_room = ROOM_STAGE
};

/*  CHICA  */

struct Animatronic CHICA = {
        .update = &update_bonnie, //TODO
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
    } else {
        vbaprint("freddy fail\n");// TODO debug, remove
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