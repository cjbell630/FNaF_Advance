#include "cam_nav.h"
#include "components/camera.h"
#include "room_names.h"

TRIBIT_2D_POINT CURR_CAM_POINT = {1, 0};

/**
 * This is a 8x8 grid, [x][y]
 * altho for some reason I think I wrote CAM_POINT_WARP(1, 1) backwards so that's y,x
 * This grid is navigated using the D pad (right=x++, up=y++, etc)
 * When each of the following points are landed on, there is an effect:
 *
 * CAM_POINT_STATIC() displays the camera for that corresponding room
 * CAM_POINT_WARP jumps to the specified coordinates on the map
 * CAM_POINT_NOGO if the user tries to go here, it will fail. the user will stay in the previous spot
 * CAM_POINT_NULL a spacer, theoretically means this space should never be reached...
 * (but TODO in practice the user can move to these spaces, so make them have the same effect as nogo)
 *
 * This information defines how the camera map is navigated by the user.
 */
const CAM_NAV_POINT CAM_NAV_MAP[8][8] = {
        {
                CAM_POINT_NOGO,                          CAM_POINT_STATIC(ROOM_STAGE),         CAM_POINT_NOGO,
                CAM_POINT_NULL,                        CAM_POINT_WARP(1, 1) /* TO DINING */         /*more*/
        },
        {
                CAM_POINT_WARP(4, 1) /* TO BACKSTAGE */, CAM_POINT_STATIC(ROOM_DINING),        CAM_POINT_STATIC(
                                                                                                       ROOM_RESTROOMS),
                CAM_POINT_NOGO,                        CAM_POINT_STATIC(ROOM_BACKSTAGE),        CAM_POINT_WARP(1,
                                                                                                               1) /* TO DINING */,
                CAM_POINT_WARP(2, 1) /* TO RESTROOMS */
        },
        {
                CAM_POINT_NULL,                          CAM_POINT_WARP(5, 4) /* TO PIRATE */, CAM_POINT_WARP(6,
                                                                                                              2) /* TO KITCHEN */,
                CAM_POINT_NULL,                        CAM_POINT_WARP(4, 5) /* TO CLOSET */,    CAM_POINT_WARP(2,
                                                                                                               3) /* TO EAST */,
                CAM_POINT_STATIC(ROOM_KITCHEN), CAM_POINT_NOGO
        },
        {
                CAM_POINT_WARP(4, 5) /* TO CLOSET */,    CAM_POINT_STATIC(ROOM_WEST),          CAM_POINT_STATIC(
                                                                                                       ROOM_EAST),
                CAM_POINT_WARP(6, 2) /* TO KITCHEN */, CAM_POINT_NULL,                          CAM_POINT_WARP(1,
                                                                                                               1) /* TO DINING */,
                CAM_POINT_WARP(2, 3) /* TO EAST */ /*more*/
        },
        {
                CAM_POINT_NOGO,                          CAM_POINT_STATIC(ROOM_WEST_CORNER),   CAM_POINT_STATIC(
                                                                                                       ROOM_EAST_CORNER),
                CAM_POINT_NOGO,                        CAM_POINT_WARP(4, 1) /* TO BACKSTAGE */, CAM_POINT_STATIC(
                                                                                                        ROOM_PIRATE),
                CAM_POINT_WARP(6, 2) /* TO KITCHEN */ /*more*/
        },
        {
                CAM_POINT_NULL,                          CAM_POINT_NOGO,                       CAM_POINT_NOGO,
                CAM_POINT_NOGO,                        CAM_POINT_STATIC(ROOM_CLOSET),           CAM_POINT_WARP(1,
                                                                                                               3) /* TO WEST */
                /*more*/
        },
        {
                CAM_POINT_NULL,                          CAM_POINT_NULL,                       CAM_POINT_NULL,
                CAM_POINT_NULL,                        CAM_POINT_WARP(1, 3) /* TO WEST */           /*more*/
        },
        {
                CAM_POINT_NULL,                          CAM_POINT_NOGO                               /*more*/
        }
};

void navigate_cams(int horizontal, int vertical) {
    //TODO: better comparisons here
    TRIBIT_2D_POINT prev = CURR_CAM_POINT;
    //TODO make 8 a constant
    CURR_CAM_POINT.x = (CURR_CAM_POINT.x + horizontal) % 8; //TODO: modulo necessary if bitfield screen_entry_length is defined as 3?
    CURR_CAM_POINT.y = (CURR_CAM_POINT.y - vertical) % 8;
    if (!(horizontal == 0 && vertical == 0)) { //if moved
        CAM_NAV_POINT point = CAM_NAV_MAP[CURR_CAM_POINT.y][CURR_CAM_POINT.x]; //reversed on purpose
        switch (point.type) {
            case CAM_POINT_TYPE_NOGO: // nogo
                CURR_CAM_POINT = prev;
                break;
            case CAM_POINT_TYPE_WARP: // warp
                CURR_CAM_POINT = point.warp_point;
                Cameras.select_room(CAM_NAV_MAP[CURR_CAM_POINT.y][CURR_CAM_POINT.x].cam_num);
                break;
            case CAM_POINT_TYPE_STATIC: // static point
                Cameras.select_room(point.cam_num);
                break;
            default:
                break;
        }
    }
}