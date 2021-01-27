//
// Created by cb106 on 1/22/2021.
//

#ifndef FNAF_ADVANCE_CAMERA_H
#define FNAF_ADVANCE_CAMERA_H

#include "../graphics/bg_pal_handler.h"

/*Cam Num Marcos*/
#define CAM_STAGE 0x00
#define CAM_DINING 0x01
#define CAM_PIRATE 0x02
#define CAM_WEST 0x03
#define CAM_WEST_CORNER 0x04
#define CAM_CLOSET 0x05
#define CAM_EAST 0x06
#define CAM_EAST_CORNER 0x07
#define CAM_BACKSTAGE 0x08
#define CAM_KITCHEN 0x09
#define CAM_RESTROOMS 0x0A

typedef struct {
    unsigned x: 3;
    unsigned y: 3;
} TRIBIT_2D_POINT;

typedef struct {
    unsigned num:3;
}CAM_NUM;

//represents information for use in the map for moving around the cam map
typedef struct {
    unsigned type: 2;
    TRIBIT_2D_POINT warp_point;
    u8 cam_num; //fuck this, no matter what I try, it keeps truncating it down to 2 bits or something when I try to make it an 3 bits long
} CAM_CTRL_POINT;

/* Control point macros*/
#define CAM_POINT_TYPE_NOGO 0x0
#define CAM_POINT_TYPE_WARP 0x1
#define CAM_POINT_TYPE_STATIC 0x2
#define CAM_POINT_NULL {CAM_POINT_TYPE_NOGO, {0x0, 0x0}, 0}
#define CAM_POINT_NOGO {CAM_POINT_TYPE_NOGO, {0x0, 0x0}, 0}
#define CAM_POINT_WARP(x, y) {CAM_POINT_TYPE_WARP, {x, y}, 0}
#define CAM_POINT_STATIC(n) {CAM_POINT_TYPE_STATIC, {0, 0}, n}


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

/* Cam Spec */
#define CAM_SPEC_STD 0x0
#define CAM_SPEC_LOOK 0x1


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

extern const CAM_CTRL_POINT CAM_CTRL_MAP[8][8];

extern CAM_DATA CAMS[11];

void init_cams();

CAM_DATA get_cam_data(int cam_num);

CAM_IMG_DATA get_cam_img_data(int cam_num);

void select_cam(int cam_num);

void select_next_cam();

void select_prev_cam();

void cam_map_control(int horizontal, int vertical);

void set_cam_display(int on);

void toggle_cam_display();

int are_cams_up();

void scroll_cams();

#endif //FNAF_ADVANCE_CAMERA_H
