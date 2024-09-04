#include "equipment.h"
#include "tonc_types.h"
#include "game/control/cameras/camera.h"

/* EQUIPMENT VARS */
bool statuses[5];

/**
 * Gets the total number of equipment being used
 * @return
 */
byte equipment_get_usage() {
    return statuses[RIGHT_DOOR] + statuses[LEFT_DOOR] + statuses[RIGHT_LIGHT] + statuses[LEFT_LIGHT] + statuses[CAMERA];
}

void equipment_on_night_start(int night_num) {
    /* INIT EQUIPMENT VARS */
    statuses[RIGHT_DOOR] = statuses[LEFT_DOOR] = statuses[RIGHT_LIGHT] = statuses[LEFT_LIGHT] = statuses[CAMERA] = false;
}

/**
 * Returns the status of the specified equipment
 * @param target enum EquipmentNames, the target to check
 * @return true if the target was set to on, false if off
 */
bool equipment_is_on(enum EquipmentNames target) {
    return statuses[target];
}

/**
 * Toggles the specified equipment and returns the new value.
 * TODO is the return necessary?
 * @param target enum EquipmentNames, the target to toggle
 * @return true if the target was set to on, false if off
 */
bool equipment_toggle(enum EquipmentNames target) {
    bool newStatus = (statuses[target] = !statuses[target]);
    // TODO visual effects

    // side effects
    // NOTE technically this is only necessary when the equipment is going from off->on,
    // but in all cases the equipment that would be disabled cannot be activated when on->off anyway.
    // maybe putting an if statement could save comparisons tho?
    switch (target) {
        case RIGHT_LIGHT: // activating the right light disables the left light
            statuses[LEFT_LIGHT] = false;
            break;
        case LEFT_LIGHT: // activating the left light disables the right light
            statuses[RIGHT_LIGHT] = false;
            break;
        case CAMERA: // activating the camera disables both lights
            statuses[RIGHT_LIGHT] = statuses[LEFT_LIGHT] = false;
            set_cam_display_visible(newStatus);
            break;
        default:
            break;
    }
    return newStatus;
}

struct EquipmentWrapper Equipment = {
        .get_usage = equipment_get_usage,
        .on_night_start = equipment_on_night_start,
        .toggle = equipment_toggle,
        .is_on = equipment_is_on
};