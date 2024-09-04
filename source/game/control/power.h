#ifndef FNAF_ADVANCE_POWER_H
#define FNAF_ADVANCE_POWER_H

#include "tonc_types.h"

struct PowerWrapper {
    void (*update)(int frame_num, byte usage);
    void (*on_night_start)(int night_num);
    void (*on_foxy_attack)();
};

extern struct PowerWrapper Power;



#endif //FNAF_ADVANCE_POWER_H
