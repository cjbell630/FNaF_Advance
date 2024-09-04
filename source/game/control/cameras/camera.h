#ifndef FNAF_ADVANCE_CAMERA_H
#define FNAF_ADVANCE_CAMERA_H

#include "game/graphics/bg_pal_handler.h"
#include "game/control/cameras/room_names.h"


/*other macros*/
#define SHOULD_PAN(n) n != ROOM_CLOSET && n != ROOM_KITCHEN

void init_cams();

void select_cam(enum RoomNames room);

void set_cam_display(bool on);

void update_cam_pan();

#endif //FNAF_ADVANCE_CAMERA_H
