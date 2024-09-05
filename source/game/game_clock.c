#include "game_clock.h"
#include "util/random.h"
#include "util/util.h"
#include "components/camera.h"
#include "graphics/static_handler.h"
#include "components/animatronics.h"
#include "components/power.h"
#include "components/equipment.h"
#include "components/spooky_effects.h"

// TODO couldn't this be the length of a night 32400 frames which would fit in 2 bytes?
const int FRAME_MAX = 130881600; // the LCM of all frame intervals, to avoid massive nums in memory


//TODO: could be smaller num if necessary
int frame = 0;
bool cam_is_up;
enum RoomNames selected_cam;

void init_clock() {
    frame = 0;
}

void tick() {
    frame %= FRAME_MAX;
    cam_is_up = Equipment.is_on(CAMERA);
    selected_cam = Cameras.get_selected_room();
    if (cam_is_up) {
        Cameras.update(frame);
    }

    update_static();
    Animatronics.update(frame, cam_is_up, selected_cam);
    Power.update(frame, Equipment.get_usage());
    SpookyEffects.update(frame);
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

    if (is_multiple(frame, 360)) { // every 360 frames
        //TODO: game_time_in_mins += 4
    }

    //TODO: could add 5 separate comparisons to be run every night instead
    // because all except night 1 are multiples or equal to existing intervals
    // also call this the fan power drain
    if (is_multiple(frame, 130881601/*current night power decrease interval*/)) { // every 360 frames
        //TODO: decrease power by 1%
    }

    // TODO call hour increase

    //TODO oh nowww I see why I wanted to keep everything in here, to reduce comparisons for times when the multiple is the same

    frame++;
}