//
// Created by cb106 on 1/27/2021.
//

#ifndef FNAF_ADVANCE_CAM_NAV_H
#define FNAF_ADVANCE_CAM_NAV_H

#include "../../../include/tonclib/tonc.h"

typedef struct {
    unsigned x: 3;
    unsigned y: 3;
} TRIBIT_2D_POINT;

//represents information for use in the map for moving around the cam map
typedef struct {
    unsigned type: 2;
    TRIBIT_2D_POINT warp_point;
    u8 cam_num; //fuck this, no matter what I try, it keeps truncating it down to 2 bits or something when I try to make it an 3 bits long
} CAM_NAV_POINT;

/* Control point macros*/
#define CAM_POINT_TYPE_NOGO 0x0
#define CAM_POINT_TYPE_WARP 0x1
#define CAM_POINT_TYPE_STATIC 0x2
#define CAM_POINT_NULL {CAM_POINT_TYPE_NOGO, {0x0, 0x0}, 0}
#define CAM_POINT_NOGO {CAM_POINT_TYPE_NOGO, {0x0, 0x0}, 0}
#define CAM_POINT_WARP(x, y) {CAM_POINT_TYPE_WARP, {x, y}, 0}
#define CAM_POINT_STATIC(n) {CAM_POINT_TYPE_STATIC, {0, 0}, n}

extern const CAM_NAV_POINT CAM_NAV_MAP[8][8];

void navigate_cams(int horizontal, int vertical);


#endif //FNAF_ADVANCE_CAM_NAV_H
