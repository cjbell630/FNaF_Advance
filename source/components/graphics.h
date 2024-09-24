#ifndef FNAF_ADVANCE_GRAPHICS_H
#define FNAF_ADVANCE_GRAPHICS_H

#include "game/room_names.h"
#include "graphics/cam_img_map.h"


struct GraphicsWrapper {
    void (*show_static)();

    void (*init_backgrounds)();

    void (*init_objects)();

    void (*game_display_cams)();

    void (*game_display_office)();

    void (*update_cam)();

    void (*set_office_scroll)(s16 value);

    void (*on_room_visual_change)(Frame *new_frame);

    void (*select_cam)(enum RoomNames prev_room, enum RoomNames new_room);

    void (*load_left_door_frame)(u8 frame_num);
};

extern struct GraphicsWrapper Graphics;

#endif //FNAF_ADVANCE_GRAPHICS_H
