#ifndef FNAF_ADVANCE_EQUIPMENT_H
#define FNAF_ADVANCE_EQUIPMENT_H

#include "tonc_types.h"

enum EquipmentNames {
    RIGHT_DOOR, LEFT_DOOR, RIGHT_LIGHT, LEFT_LIGHT, CAMERA
};

struct EquipmentWrapper {
    void (*update)();

    void (*on_night_start)();

    byte (*get_usage)();

    bool (*is_on)(enum EquipmentNames target);

    void (*toggle)(enum EquipmentNames target);

    bool (*force_light_off)(enum EquipmentNames light);

    void (*disable)(enum EquipmentNames target);

    bool (*is_animating_cam)();
};

extern struct EquipmentWrapper Equipment;

#endif //FNAF_ADVANCE_EQUIPMENT_H
