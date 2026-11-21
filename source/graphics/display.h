#ifndef FNAF_ADVANCE_DISPLAY_H
#define FNAF_ADVANCE_DISPLAY_H
#include <stdbool.h>

struct DisplayWrapper {
    void (*set_main_menu)();
    void (*set_still_cinematic)();
    void (*set_office)();
    void (*set_cams)(bool stunned);
};

extern struct DisplayWrapper Display;

#endif //FNAF_ADVANCE_DISPLAY_H
