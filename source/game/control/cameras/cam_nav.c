#include "cam_nav.h"
#include "camera.h"
#include "room_names.h"

TRIBIT_2D_POINT CURR_CAM_POINT = {1, 0};

const CAM_NAV_POINT CAM_NAV_MAP[8][8] = {
        {
                CAM_POINT_NOGO,       CAM_POINT_STATIC(ROOM_STAGE),       CAM_POINT_NOGO,
                CAM_POINT_NULL,       CAM_POINT_WARP(1, 1) /*more*/
        },
        {
                CAM_POINT_WARP(4, 1), CAM_POINT_STATIC(ROOM_DINING),      CAM_POINT_STATIC(ROOM_RESTROOMS),
                CAM_POINT_NOGO,       CAM_POINT_STATIC(ROOM_BACKSTAGE), CAM_POINT_WARP(1, 1),
                CAM_POINT_WARP(2, 1)
        },
        {
                CAM_POINT_NULL,       CAM_POINT_WARP(5, 4),              CAM_POINT_WARP(6, 2),
                CAM_POINT_NULL,       CAM_POINT_WARP(4, 5),            CAM_POINT_WARP(4, 5),
                CAM_POINT_STATIC(ROOM_KITCHEN), CAM_POINT_NOGO
        },
        {
                CAM_POINT_WARP(4, 5), CAM_POINT_STATIC(ROOM_WEST),        CAM_POINT_STATIC(ROOM_EAST),
                CAM_POINT_WARP(6, 2), CAM_POINT_NULL,                  CAM_POINT_WARP(1, 1),
                CAM_POINT_WARP(2, 3) /*more*/
        },
        {
                CAM_POINT_NOGO,       CAM_POINT_STATIC(ROOM_WEST_CORNER), CAM_POINT_STATIC(ROOM_EAST_CORNER),
                CAM_POINT_NOGO,       CAM_POINT_WARP(4, 1),            CAM_POINT_STATIC(ROOM_PIRATE),
                CAM_POINT_WARP(6, 2) /*more*/
        },
        {
                CAM_POINT_NULL,       CAM_POINT_NOGO,                    CAM_POINT_NOGO,
                CAM_POINT_NOGO,       CAM_POINT_STATIC(ROOM_CLOSET),    CAM_POINT_WARP(1, 3)
                /*more*/
        },
        {
                CAM_POINT_NULL,       CAM_POINT_NULL,                    CAM_POINT_NULL,
                CAM_POINT_NULL,       CAM_POINT_WARP(1, 3) /*more*/
        },
        {
                CAM_POINT_NULL,       CAM_POINT_NOGO /*more*/
        }
};

void navigate_cams(int horizontal, int vertical) {
    char buf[16];
    /*vbaprint("horiz: ");
    sprintf(buf, "%d", horizontal);
    vbaprint(buf);
    vbaprint("\nvert: ");
    sprintf(buf, "%d", vertical);
    vbaprint(buf);*/
    //TODO: better comparisons here
    TRIBIT_2D_POINT prev = CURR_CAM_POINT;
    //TODO make 8 a constant
    CURR_CAM_POINT.x = (CURR_CAM_POINT.x + horizontal) % 8; //TODO: modulo necessary if bitfield length is defined as 3?
    CURR_CAM_POINT.y = (CURR_CAM_POINT.y - vertical) % 8;
    if (!(horizontal == 0 && vertical == 0)) { //if moved
        CAM_NAV_POINT point = CAM_NAV_MAP[CURR_CAM_POINT.y][CURR_CAM_POINT.x]; //reversed on purpose
        switch (point.type) {
            case CAM_POINT_TYPE_NOGO: // nogo
                CURR_CAM_POINT = prev;
                break;
            case CAM_POINT_TYPE_WARP: // warp
                CURR_CAM_POINT = point.warp_point;
                cam_select_room(CAM_NAV_MAP[CURR_CAM_POINT.y][CURR_CAM_POINT.x].cam_num);
                break;
            case CAM_POINT_TYPE_STATIC: // static point
                cam_select_room(point.cam_num);
                break;
            default:
                break;
        }
    }
}