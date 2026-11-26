#ifndef FNAF_ADVANCE_BACKGROUND_H
#define FNAF_ADVANCE_BACKGROUND_H

#include "frames/frame.h"

#define MAIN_CBB 0
#define MAIN_SBB 30

struct BackgroundWrapper {
    void (*set_main_menu)();
    void (*set_newspaper)();
    void (*set_night_intro)();
    void (*set_office)();
    void (*set_cams)();
    void (*load_frame)(const Frame* frame, const u16 cbb, const u16 sbb);
};

extern struct BackgroundWrapper Background;

#endif //FNAF_ADVANCE_BACKGROUND_H
