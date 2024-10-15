#include <stdlib.h>
#include "camera.h"
#include "graphics/bg_pal_handler.h"
#include "util/util.h"
#include "tonc.h"

#include "game/room_names.h"
#include "graphics/cam_img_map.h"
#include "graphics.h"
#include "game_state.h"
#include "spooky_effects.h"

#define SHOULD_PAN(n) (n != ROOM_CLOSET && n != ROOM_KITCHEN)

enum RoomNames CURR_CAM = ROOM_STAGE;

const u8 TURNAROUND_TIMER_LENGTH = 60;
const u8 CAM_SCROLL_DISP_RIGHT_CAP = 114;
const u8 CAM_SCROLL_FRAME_INTERVAL = 2;
const s8 CAM_SCROLL_POS_INC = 1;
const s8 CAM_SCROLL_NEG_INC = 0 - CAM_SCROLL_POS_INC;
// NOTE real scroll speed is 300 frames to 114 pixels = 38px/100f = 19px/50f ~=~ 2px/5f
// and the pause is 120 frames
// but that scroll speed looks choppy bc of the pixel density, so I had to play around with it.
// Also, the aspect ratio in the original is wider so more of the image is shown at once.
// It still doesn't really look like the original, but it fits better I think.

// TODO init on night start
s16 cam_scroll = 0;
u8 turnaround_timer = 0; // TODO set to max when cam opened
s8 cam_scroll_dir = 1;


void cam_select_room(enum RoomNames room) {
    room = continuous_modulo(room, NUM_ROOMS); // puts the value between 0 and 10 inclusive
    if (!SHOULD_PAN(room)) {
        REG_BG1HOFS = 0; // TODO move this to graphics?
    }
    SpookyEffects.on_select_cam(room);
    Graphics.select_cam(CURR_CAM, room);
    CURR_CAM = room;
}

void set_cam_display_visible() {
    SpookyEffects.on_cam_up();
    Graphics.game_display_cams();
    cam_select_room(CURR_CAM);
}

void camera_on_night_start() {
    CURR_CAM = ROOM_STAGE;
}


/**
 *
 */
void pan_cam() {
    if (turnaround_timer) {
        turnaround_timer--;
        if (turnaround_timer == 0) {
            cam_scroll_dir = cam_scroll_dir == CAM_SCROLL_POS_INC ? CAM_SCROLL_NEG_INC : CAM_SCROLL_POS_INC;
        }
        return;
    }
    cam_scroll += cam_scroll_dir;
    if (cam_scroll <= 0) {
        cam_scroll = 0;
        turnaround_timer = TURNAROUND_TIMER_LENGTH;
    } else if (cam_scroll >= CAM_SCROLL_DISP_RIGHT_CAP) {
        cam_scroll = CAM_SCROLL_DISP_RIGHT_CAP;
        turnaround_timer = TURNAROUND_TIMER_LENGTH;
    }
    REG_BG1HOFS = cam_scroll;
}

void update_camera() {
    if (SHOULD_PAN(CURR_CAM) && frame_multiple(CAM_SCROLL_FRAME_INTERVAL)) { // TODO move to graphics?
        pan_cam();
    }
    Graphics.update_cam();
}

enum RoomNames get_selected_room() {
    return CURR_CAM;
}


struct CameraWrapper Cameras = {
        .update = update_camera,
        .on_night_start = camera_on_night_start,
        .set_visible = set_cam_display_visible,
        .select_room = cam_select_room,
        .get_selected_room = get_selected_room
};