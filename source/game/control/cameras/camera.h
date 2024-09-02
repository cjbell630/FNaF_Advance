#ifndef FNAF_ADVANCE_CAMERA_H
#define FNAF_ADVANCE_CAMERA_H

#include "game/graphics/bg_pal_handler.h"

/*Cam Num Marcos*/
#define CAM_STAGE 0
#define CAM_DINING 1
#define CAM_PIRATE 2
#define CAM_WEST 3
#define CAM_WEST_CORNER 4
#define CAM_CLOSET 5
#define CAM_EAST 6
#define CAM_EAST_CORNER 7
#define CAM_BACKSTAGE 8
#define CAM_KITCHEN 9
#define CAM_RESTROOMS 10

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
#define CURR_IS_STILL CURR_CAM == CAM_CLOSET || CURR_CAM == CAM_KITCHEN

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
