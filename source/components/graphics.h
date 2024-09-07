#ifndef FNAF_ADVANCE_GRAPHICS_H
#define FNAF_ADVANCE_GRAPHICS_H

#include "game/room_names.h"


struct GraphicsWrapper {
    void (*show_static)();

    void (*load_office)();

    void (*init_objects)();

    void (*show_cams)();

    void (*hide_cams)();

    void (*select_cam)(enum RoomNames prev_room, enum RoomNames new_room);
};

extern struct GraphicsWrapper Graphics;

#endif //FNAF_ADVANCE_GRAPHICS_H
