#ifndef FNAF_ADVANCE_CAM_NAV_H
#define FNAF_ADVANCE_CAM_NAV_H

struct CamMinimapWrapper {
    void (*move_focus)(const int horizontal, const int vertical);
};

extern struct CamMinimapWrapper CamMinimap;


#endif //FNAF_ADVANCE_CAM_NAV_H
