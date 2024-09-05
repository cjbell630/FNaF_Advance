#ifndef FNAF_ADVANCE_CAM_IMG_MAP_H
#define FNAF_ADVANCE_CAM_IMG_MAP_H

#include "game/control/cameras/room_names.h"

//Points to image data for a camstate
typedef struct {
    unsigned short *cam_tiles;
    unsigned short cam_tiles_len;
    unsigned short *cam_pal;
    unsigned short cam_pal_len;
    unsigned short *cam_map;
    unsigned short cam_map_len;
} CAM_IMG_DATA;

extern const CAM_IMG_DATA CAM_IMG_MAP[12][16][2];

CAM_IMG_DATA get_cam_img_data(enum RoomNames room);

#endif //FNAF_ADVANCE_CAM_IMG_MAP_H
