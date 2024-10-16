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
#include "components/controls.h"
#include "components/graphics.h"

bool cam_is_up;
enum RoomNames selected_cam;

void init_clock() {
    FRAME_NUM = 1; // start at 1 so animatronics don't get a movement opportunity on the first frame
}

void tick() {
    // Apply controls based on state of previous frame
    if (cam_is_up) {
        Controls.update_cam();
    } else if (!Equipment.is_animating_cam()) {
        Controls.update_office();
        Equipment.update();
    }

    // cam_is_up could have changed based on controller input

    cam_is_up = Equipment.is_on(CAMERA);
    selected_cam = Cameras.get_selected_room();
    SpookyEffects.update(cam_is_up, selected_cam);
    if (cam_is_up) {
        Cameras.update();
    } else {
        Graphics.update_office();
    }

    Animatronics.update(cam_is_up, selected_cam);
    Power.update(Equipment.get_usage());
    //TODO: reduce these to reduce comparisons run every frame

    if (frame_multiple(2)) { // every other frame
        scramble_rng(__key_curr);
    }

    // TODO call hour increase

    //TODO oh nowww I see why I wanted to keep everything in here, to reduce comparisons for times when the multiple is the same

    increment_frame();
}