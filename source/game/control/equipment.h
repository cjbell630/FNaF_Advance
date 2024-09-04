#ifndef FNAF_ADVANCE_EQUIPMENT_H
#define FNAF_ADVANCE_EQUIPMENT_H

#include "tonc_types.h"

struct EquipmentWrapper {
    //void (*update)(int frame_num);
    void (*on_night_start)(int night_num);
    void (*toggle_right_door)();
    byte (*get_usage)();
};

extern struct EquipmentWrapper Equipment;

#endif //FNAF_ADVANCE_EQUIPMENT_H
