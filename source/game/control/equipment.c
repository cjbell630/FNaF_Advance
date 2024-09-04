#include "equipment.h"
#include "tonc_types.h"

/* EQUIPMENT VARS */
bool right_door, left_door, right_light, left_light, camera;

/* END EQUIPMENT VARS */

byte equipment_get_usage() {
    return right_door + left_door + right_light + left_light + camera;
}

void equipment_on_night_start(int night_num) {
    /* INIT EQUIPMENT VARS */
    right_door = left_door = right_light = left_light = camera = false;
}

struct EquipmentWrapper Equipment = {
        .get_usage = equipment_get_usage,
        .on_night_start = equipment_on_night_start
};