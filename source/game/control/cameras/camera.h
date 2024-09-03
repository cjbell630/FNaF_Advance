#ifndef FNAF_ADVANCE_CAMERA_H
#define FNAF_ADVANCE_CAMERA_H

#include "game/graphics/bg_pal_handler.h"


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

extern CAM_DATA CAMS[11];

void init_cams();

CAM_DATA get_cam_data(int cam_num);

CAM_IMG_DATA get_cam_img_data(int cam_num);

void select_cam(int cam_num);

void select_next_cam();

void select_prev_cam();

void set_cam_display(int on);

void toggle_cam_display();

int are_cams_up();

void scroll_cams();

#endif //FNAF_ADVANCE_CAMERA_H
