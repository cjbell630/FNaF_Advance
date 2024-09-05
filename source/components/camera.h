#ifndef FNAF_ADVANCE_CAMERA_H
#define FNAF_ADVANCE_CAMERA_H

#include "graphics/bg_pal_handler.h"
#include "game/room_names.h"

struct CameraWrapper {
    void (*update)(int frame_num);

    void (*on_night_start)(int night_num);

    void (*set_visible)(bool on);

    void (*select_room)(enum RoomNames room);
};

extern struct CameraWrapper Cameras;

#endif //FNAF_ADVANCE_CAMERA_H
