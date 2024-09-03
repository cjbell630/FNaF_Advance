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
int get_random_empty_room_from(int rooms[], int num_rooms) { //TODO: should this really be an array?
    uint status = GET_N_SET_BITS(num_rooms); // 11 bits, one for each room
    int rand_index;
    while (status > 0) { //TODO: could use rnd_exclude if I made it take more nums
        if (Animatronics.get_room_occupants(rand_index = rnd_max(num_rooms)) ==
            0/*TODO use macro ROOM_EMPTY*/) { // if the found room is empty
            return rooms[rand_index];
        }
        status &= ~(1 << rand_index); // turn off the bit corresponding to the random room num
    }
    return -1;
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

void init_bonnie(int level) {
    BONNIE.lvl = level;
    BONNIE.room_num = 0;
}

void update_bonnie(int frame_num) {
    if (!is_multiple(frame_num, BONNIE_FRAMECOUNT)) {
        return;
    }
    vbaprint("Bonnie movement opp\n");

    if (try_move(&BONNIE)) {
        vbaprint("bonnie success\n");
        int room_nums[] = {
                // TODO macro or something
                ROOM_STAGE, ROOM_DINING, ROOM_BACKSTAGE, ROOM_WEST, ROOM_WEST_CORNER, ROOM_CLOSET
        };
        BONNIE.room_num = get_random_empty_room_from(room_nums, 6);
    } else {
        vbaprint("bonnie fail\n"); // TODO debug, remove
    }
}

struct Animatronic BONNIE = {
        .init = &init_bonnie,
        .update = &update_bonnie
};

/*  CHICA  */

struct Animatronic CHICA = {
        .init = &init_bonnie,
        .update = &update_bonnie //TODO
};

/*  FREDDY  */

void init_freddy(int level) {
    FREDDY.lvl = level;
    FREDDY.room_num = 0;
}

void update_freddy(int frame_num) {
    if (!is_multiple(frame_num, BONNIE_FRAMECOUNT)) {
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
        .init = &init_freddy,
        .update = &update_freddy
};

/*  FOXY  */

struct Animatronic FOXY = {
        .init = &init_freddy,
        .update = &update_freddy // TODO
};


/*  COLLECTIVE  */
void set_levels(int b_lvl, int c_lvl, int fr_lvl, int fo_lvl) {
    BONNIE.init(b_lvl);
    FREDDY.init(fr_lvl);
}

void reset_anims() {

}

void update_anims(int frame_num) {
    // TODO can I put them in a list or something and do for each, and then say if frame mult of internal attribute
    BONNIE.update(frame_num);
    FREDDY.update(frame_num);
}

// TODO define this in camera.c?
char get_room_occupants(int room_num) {
    return ((BONNIE.room_num == room_num) << 3) | ((CHICA.room_num == room_num) << 2) |
           ((FREDDY.room_num == room_num) << 1) | (FOXY.room_num == room_num);
}

struct AnimatronicsWrapper Animatronics = {
        .update = update_anims,
        .reset = reset_anims,
        .set_levels = set_levels,
        .get_room_occupants = get_room_occupants
};