//
// https://www.pvv.ntnu.no/~hakonhal/main.cgi/c/classes/
//

#include "ai.h"
#include "DWedit/debug.h"
#include "util/random.h"
#include "util/util.h"
#include "game/control/cameras/camera.h"
#include <stdio.h>

void change_room(struct Animatronic anim, int new_room) {
    CAMS[anim.room_num].occupants &= ~(anim.cam_occ); // remove freddy from old room
    CAMS[new_room].occupants |= (anim.cam_occ); // add freddy to new room

    anim.room_num = new_room;
}

int get_random_unocc(int room_nums[], int room_numc) { //TODO: should this really be an array?
    uint status = GET_N_SET_BITS(room_numc); // 11 bits, one for each room
    int rand_index;
    while (status > 0) { //TODO: could use rnd_exclude if I made it take more nums
        if (CAMS[rand_index = rnd_max(room_numc)].occupants == CAM_OCC_EMPTY) { // if the found room is empty
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
                CAM_STAGE, CAM_DINING, CAM_BACKSTAGE, CAM_WEST, CAM_WEST_CORNER, CAM_CLOSET
        };
        for (int i = 0; i < 10; i++) {
            sprintf(str, "rand unocc room: %d\n", get_random_unocc(room_nums, 6));
            vbaprint(str);
        }
        change_room(BONNIE, get_random_unocc(room_nums, 6));
        sprintf(str, "stage occ: %d\n", CAMS[0].occupants);
        vbaprint(str);
    } else {
        vbaprint("bonnie fail\n");
    }
}


struct Animatronic BONNIE = {
        .cam_occ = (char) CAM_OCC_BONNIE,
        .init = &init_bonnie,
        .move_opp = &move_opp_bonnie
};

/*  CHICA  */


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
        //change_room(FREDDY, CAM_EAST);
    } else {
        vbaprint("freddy fail\n");
    }
}

struct Animatronic FREDDY = {
        .cam_occ = (char) CAM_OCC_FREDDY,
        .init = &init_freddy,
        .move_opp = &move_opp_freddy
};

/*  FOXY  */




/*  COLLECTIVE  */
void set_levels(int b_lvl, int c_lvl, int fr_lvl, int fo_lvl) {
    BONNIE.init(b_lvl);
    FREDDY.init(fr_lvl);
}

void reset_anims() {

}

void update_anims() {

}

struct AnimatronicsWrapper Animatronics = {
        .update = update_anims,
        .reset = reset_anims,
        .set_levels = set_levels
};