//
// https://www.pvv.ntnu.no/~hakonhal/main.cgi/c/classes/
//

#include "ai.h"
#include "DWedit/debug.h"
#include "util/random.h"
#include "util/util.h"
#include "game/control/cameras/room_names.h"
#include <stdio.h>

void change_room(struct Animatronic anim, int new_room) {
    //Animatronics.get_room_occupants(anim.room_num) &= ~(anim.cam_occ); // remove freddy from old room
    //Animatronics.get_room_occupants(new_room) |= (anim.cam_occ); // add freddy to new room
    anim.room_num = new_room;
}

int get_random_unocc(int room_nums[], int room_numc) { //TODO: should this really be an array?
    uint status = GET_N_SET_BITS(room_numc); // 11 bits, one for each room
    int rand_index;
    while (status > 0) { //TODO: could use rnd_exclude if I made it take more nums
        if (Animatronics.get_room_occupants(rand_index = rnd_max(room_numc)) == 0/*TODO use macro ROOM_EMPTY*/) { // if the found room is empty
            return room_nums[rand_index];
        }
        status &= ~(1 << rand_index); // turn off the bit corresponding to the random room num
    }
    return -1;
}

/*  BONNIE  */

void init_bonnie(int level) {
    BONNIE.lvl = level;
    BONNIE.room_num = 0;
}

void move_opp_bonnie(int roll) {
    char str[90] = "";
    sprintf(str, "bonnie move opp, roll %d\n", roll);
    vbaprint(str);

    if (roll <= BONNIE.lvl) {
        vbaprint("bonnie succ\n");
        int room_nums[] = {
                ROOM_STAGE, ROOM_DINING, ROOM_BACKSTAGE, ROOM_WEST, ROOM_WEST_CORNER, ROOM_CLOSET
        };
        for (int i = 0; i < 10; i++) {
            sprintf(str, "rand unocc room: %d\n", get_random_unocc(room_nums, 6));
            vbaprint(str);
        }
        change_room(BONNIE, get_random_unocc(room_nums, 6));
        sprintf(str, "stage occ: %d\n", Animatronics.get_room_occupants(0));
        vbaprint(str);
    } else {
        vbaprint("bonnie fail\n");
    }
}


struct Animatronic BONNIE = {
        .init = &init_bonnie,
        .move_opp = &move_opp_bonnie
};

/*  CHICA  */

struct Animatronic CHICA = {
        .init = &init_bonnie,
        .move_opp = &move_opp_bonnie
};

/*  FREDDY  */

void init_freddy(int level) {
    FREDDY.lvl = level;
    FREDDY.room_num = 0;
}

void move_opp_freddy(int roll) {
    char str[90] = "";
    sprintf(str, "freddy move opp, roll %d\n", roll);
    vbaprint(str);

    if (roll <= FREDDY.lvl) {
        vbaprint("freddy succ\n");
        //change_room(FREDDY, ROOM_EAST);
    } else {
        vbaprint("freddy fail\n");
    }
}

struct Animatronic FREDDY = {
        .init = &init_freddy,
        .move_opp = &move_opp_freddy
};

/*  FOXY  */

struct Animatronic FOXY = {
        .init = &init_freddy,
        .move_opp = &move_opp_freddy
};


/*  COLLECTIVE  */
void set_levels(int b_lvl, int c_lvl, int fr_lvl, int fo_lvl) {
    BONNIE.init(b_lvl);
    FREDDY.init(fr_lvl);
}

void reset_anims() {

}

void update_anims() {

}

// TODO define this in camera.c?
char get_room_occupants(int room_num){
    return  ((BONNIE.room_num == room_num) << 3) | ((CHICA.room_num == room_num) << 2) | ((FREDDY.room_num == room_num) << 1) | (FOXY.room_num == room_num);
}

struct AnimatronicsWrapper Animatronics = {
        .update = update_anims,
        .reset = reset_anims,
        .set_levels = set_levels,
        .get_room_occupants = get_room_occupants
};