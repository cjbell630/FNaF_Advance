#ifndef FNAF_ADVANCE_CAMERA_H
#define FNAF_ADVANCE_CAMERA_H

#include "game/graphics/bg_pal_handler.h"
#include "game/control/cameras/room_names.h"


//contains information about a camera's status
typedef struct {
    char occupants: 4;
    char special: 2;
} CAM_DATA;

/* Cam Occupants */
#define CAM_OCC_EMPTY 0x00
#define CAM_OCC_FOXY 0x01
#define CAM_OCC_FREDDY 0x02
#define CAM_OCC_CHICA 0x04
#define CAM_OCC_BONNIE 0x08

#define CAM_OCC(b, c, r, o, n) ((l == q) << 3) | ((m == q) << 2) | ((n == q) << 1) | (o == r);

#define IS_FOXY(n) (n & CAM_OCC_FOXY) > 0
#define IS_FREDDY(n) (n & CAM_OCC_FREDDY) > 0
#define IS_CHICA(n) n & CAM_OCC_CHICA > 0
#define IS_BONNIE(n) n & CAM_OCC_BONNIE > 0

//NOTE: to remove CAM_OCC_X from n, use:
//  n &= ~CAM_OCC_X

/* Cam Spec */
#define CAM_SPEC_STD 0x0
#define CAM_SPEC_LOOK 0x1


/*other macros*/
#define SHOULD_PAN(n) n != ROOM_CLOSET && n != ROOM_KITCHEN



extern CAM_DATA CAMS[11];

void init_cams();

CAM_DATA get_cam_data(enum RoomNames room);

void select_cam(enum RoomNames room);

void set_cam_display(bool on);

void update_cam_pan();

#endif //FNAF_ADVANCE_CAMERA_H
