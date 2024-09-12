#ifndef FNAF_ADVANCE_GRAPHICS_H
#define FNAF_ADVANCE_GRAPHICS_H

#include "game/room_names.h"


struct GraphicsWrapper {
    void (*show_static)();

    void (*init_backgrounds)();

    void (*init_objects)();

    void (*game_display_cams)();

    void (*game_display_office)();

    void (*update_cam_blip)();

    void (*select_cam)(enum RoomNames prev_room, enum RoomNames new_room);
};

extern struct GraphicsWrapper Graphics;

#endif //FNAF_ADVANCE_GRAPHICS_H
