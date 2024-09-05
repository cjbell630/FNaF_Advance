#ifndef FNAF_ADVANCE_EQUIPMENT_H
#define FNAF_ADVANCE_EQUIPMENT_H

#include "tonc_types.h"

enum EquipmentNames {
    RIGHT_DOOR, LEFT_DOOR, RIGHT_LIGHT, LEFT_LIGHT, CAMERA
};

struct EquipmentWrapper {
    //void (*update)(int frame_num);
    void (*on_night_start)(int night_num);

    byte (*get_usage)();

    bool (*is_on)(enum EquipmentNames target);

    bool (*toggle)(enum EquipmentNames target);
};

extern struct EquipmentWrapper Equipment;

#endif //FNAF_ADVANCE_EQUIPMENT_H
