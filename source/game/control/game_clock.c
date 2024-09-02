#include "game_clock.h"
#include "tonc.h"
#include "../../util/random.h"
#include "../../util/util.h"
#include "cameras/camera.h"
#include "../graphics/static_handler.h"
#include "../control/ai/ai.h"

const int FRAME_MAX = 130881600; // the LCM of all frame intervals, to avoid massive nums in memory
/*
 * TODO: doc
 * rolls for a random number
 * can get anything from 1 -> 20
 */
#define RAND_ROLL rnd_max(20) + 1


//TODO: could be smaller num if necessary
int frame = 0;

void init_clock() {
    frame = 0;
}

void tick() {
    frame %= FRAME_MAX;
    scroll_cams();
    update_static();
    //TODO: reduce these to reduce comparisons run every frame

    if (is_multiple(frame, 2)) { // every other frame
        scramble_rng(__key_curr);
    }
    if (is_multiple(frame, 2)) { // every other frame
    }

    /*penalty drain (applied each second starting on night 2)*/
    if (is_multiple(frame, 60)) { // every 60 frames
        //TODO: decrease power by some%
    }

    if (is_multiple(frame, 180)) { // every 180 frames
        FREDDY.move_opp(RAND_ROLL);
    }

    if (is_multiple(frame, 298)) { // every 298 frames
        BONNIE.move_opp(RAND_ROLL);
    }

    if (is_multiple(frame, 300)) { // every 300 frames
        //TODO: chica movement opportunity
    }

    if (is_multiple(frame, 305)) { // every 305 frames
        //TODO: foxy movement opportunity
    }

    if (is_multiple(frame, 360)) { // every 360 frames
        //TODO: game_time_in_mins += 4
    }

    //TODO: could add 5 separate comparisons to be run every night instead
    // because all except night 1 are multiples or equal to existing intervals
    // also call this the fan power drain
    if (is_multiple(frame, 130881601/*current night power decrease interval*/)) { // every 360 frames
        //TODO: decrease power by 1%
    }

    frame++;
}