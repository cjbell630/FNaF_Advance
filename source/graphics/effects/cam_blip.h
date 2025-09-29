#ifndef FNAF_ADVANCE_CAM_BLIP_H
#define FNAF_ADVANCE_CAM_BLIP_H


struct CamBlipWrapper {
    void (*init)();
    void (*load)();
    void (*update)();
    void (*start)();
    void (*reset)();
};

extern struct CamBlipWrapper CamBlipEffect;

#endif //FNAF_ADVANCE_CAM_BLIP_H