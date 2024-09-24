#include <stdlib.h>
#include "camera.h"
#include "graphics/bg_pal_handler.h"
#include "util/util.h"
#include "tonc.h"

#include "game/room_names.h"
#include "graphics/cam_img_map.h"
#include "graphics.h"

#define SHOULD_PAN(n) n != ROOM_CLOSET && n != ROOM_KITCHEN

enum RoomNames CURR_CAM = ROOM_STAGE;

const int CAM_SCROLL_BUFFER = 100;
const int CAM_SCROLL_DISP_RIGHT_CAP = 114;
const int CAM_SCROLL_SPEED = 1;


int internal_cam_scroll = 0;
int disp_cam_scroll = 0;
int cam_scroll_dir = -1;

/**
 * Using this bc for some cam_select_room(0) this has to be called on init or everything breaks
 * TODO investigate later
 * but for now just making this
 * @param cam_num
 * @param cam_is_up
 */
void internal_select_cam(enum RoomNames room) {
    room = continuous_modulo(room, NUM_ROOMS); // puts the value between 0 and 10 inclusive
    Graphics.select_cam(CURR_CAM, room);
    CURR_CAM = room;
}


void set_cam_display_visible() {
    Graphics.game_display_cams();
    internal_select_cam(CURR_CAM);
}

void camera_on_night_start() {
    CURR_CAM = ROOM_STAGE;
}

void cam_select_room(enum RoomNames room) {
    internal_select_cam(room);
}


/**
 *
 */
void update_cam_pan() {
    if (SHOULD_PAN(CURR_CAM)) { // if should scroll
        if (cam_scroll_dir == 1) { // moving right
            if (internal_cam_scroll > CAM_SCROLL_DISP_RIGHT_CAP + CAM_SCROLL_BUFFER) { // turning point
                cam_scroll_dir = -1;
            } else if (disp_cam_scroll < CAM_SCROLL_DISP_RIGHT_CAP) { // move display
                disp_cam_scroll += CAM_SCROLL_SPEED;
            }
        } else { //moving left
            if (internal_cam_scroll < -CAM_SCROLL_BUFFER) { // turning point
                cam_scroll_dir = 1;
            } else if (disp_cam_scroll > 0) {
                disp_cam_scroll -= CAM_SCROLL_SPEED;
            }
        }
        internal_cam_scroll += cam_scroll_dir * CAM_SCROLL_SPEED;
        REG_BG1HOFS = disp_cam_scroll;
    } else { // if should not scroll
        REG_BG1HOFS = 0;
    }
}

void update_camera() {
    update_cam_pan();
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