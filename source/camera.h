//
// Created by cb106 on 1/22/2021.
//

#ifndef FNAF_ADVANCE_CAMERA_H
#define FNAF_ADVANCE_CAMERA_H

#include "../assets/images/backgrounds/error/error.h"
#include "screen_handler.h"

typedef struct {
    char cam_num: 4;
    char occupants: 4;
    char special: 1;
} CAM_DATA;

typedef struct {
    unsigned short *cam_tiles;
    unsigned short *cam_tiles_len;
    unsigned short *cam_pal;
    unsigned short *cam_pal_len;
    unsigned short *cam_map;
    unsigned short *cam_map_len;
} CAM_IMG_DATA;

static const CAM_IMG_DATA CAM_IMG_MAP[12][5][2] = {
        { /* STAGE (0) */
                { // Empty
                        { // Std
                                errorTiles, errorTilesLen,
                                errorPal, errorPalLen,
                                errorMap, errorMapLen
                        },
                        { // Spec

                        }
                }
        }
};

extern CAM_DATA *CAMS[16];

void init_cams();

CAM_DATA get_cam_data(int cam_num);

CAM_IMG_DATA get_cam_img_data(int cam_num);

void select_cam(int cam_num);

void set_cam_display(int on);

void toggle_cam_display();

int get_cam_status();

#endif //FNAF_ADVANCE_CAMERA_H
