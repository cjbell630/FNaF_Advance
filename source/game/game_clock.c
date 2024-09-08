#include "game_clock.h"
#include "util/random.h"
#include "util/util.h"
#include "components/camera.h"
#include "graphics/static_handler.h"
#include "components/animatronics.h"
#include "components/power.h"
#include "components/equipment.h"
#include "components/spooky_effects.h"
#include "game_state.h"

bool cam_is_up;
enum RoomNames selected_cam;

void init_clock() {
    FRAME_NUM = 0;
}

void tick() {
    cam_is_up = Equipment.is_on(CAMERA);
    selected_cam = Cameras.get_selected_room();
    if (cam_is_up) {
        Cameras.update();
    }

    update_static();
    Animatronics.update(cam_is_up, selected_cam);
    Power.update(Equipment.get_usage());
    SpookyEffects.update();
    //TODO: reduce these to reduce comparisons run every frame

    if (frame_multiple(2)) { // every other frame
        scramble_rng(__key_curr);
    }

    /*penalty drain (applied each second starting on night 2)*/
    if (frame_multiple(60)) { // every 60 frames
        //TODO: decrease power by some%
    }

    if (frame_multiple(360)) { // every 360 frames
        //TODO: game_time_in_mins += 4
    }

    //TODO: could add 5 separate comparisons to be run every night instead
    // because all except night 1 are multiples or equal to existing intervals
    // also call this the fan power drain
    if (frame_multiple(130881601/*current night power decrease interval*/)) { // every 360 frames
        //TODO: decrease power by 1%
    }

    // TODO call hour increase

    //TODO oh nowww I see why I wanted to keep everything in here, to reduce comparisons for times when the multiple is the same

    increment_frame();
}