#include "equipment.h"
#include "tonc_types.h"
#include "camera.h"
#include "graphics.h"

const u8 NUM_DOOR_FRAMES = 15; // TODO move

/* EQUIPMENT VARS */
bool statuses[5];
u8 l_door_anim_frame;
u8 r_door_anim_frame;
u8 cam_device_anim_timer;
s8 cam_device_anim_offset;

/**
 * Gets the total number of equipment being used
 * @return
 */
byte equipment_get_usage() {
    return statuses[RIGHT_DOOR] + statuses[LEFT_DOOR] + statuses[RIGHT_LIGHT] + statuses[LEFT_LIGHT] + statuses[CAMERA];
}

void equipment_on_night_start() {
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
 * Toggles light. Side effects: clears lights if toggled off.
 * Weird code but it's like this for maximum efficiency! Use defines below!
 * @param toggled the enum of the light to toggle
 * @param other the enum of the other light
 */
void toggle_light(enum EquipmentNames toggled, enum EquipmentNames other) {
    if (statuses[toggled]) {
        statuses[toggled] = false;
        Graphics.clear_office_lights();
        return;
    }
    // TODO force enable lights
    // TODO play windowscare sound
    statuses[toggled] = true;
    statuses[other] = false;
}

#define toggle_left_light() toggle_light(LEFT_LIGHT, RIGHT_LIGHT)
#define toggle_right_light() toggle_light(RIGHT_LIGHT, LEFT_LIGHT)

/**
 * Toggles the specified equipment
 *
 * @param target enum EquipmentNames, the target to toggle
 */
void equipment_toggle(enum EquipmentNames target) {
    // TODO visual effects

    // side effects
    // NOTE technically this is only necessary when the equipment is going from off->on,
    // but in all cases the equipment that would be disabled cannot be activated when on->off anyway.
    // maybe putting an if statement could save comparisons tho?
    switch (target) {
        case RIGHT_LIGHT:
            toggle_right_light();
            break;
        case LEFT_LIGHT:
            toggle_left_light();
            break;
        case CAMERA: // activating the camera disables both lights
            if (statuses[CAMERA]) { // if this will close the cam
                cam_device_anim_offset = -11;
            } else { // if this will open the cam
                cam_device_anim_offset = 0;
                statuses[RIGHT_LIGHT] = statuses[LEFT_LIGHT] = false;
            }
            cam_device_anim_timer = 11; // TODO use stored num frames
            statuses[CAMERA] = false;
            break;
        case LEFT_DOOR:
            if (l_door_anim_frame == 0) { // TODO check if bonnie is in room
                l_door_anim_frame = NUM_DOOR_FRAMES;
                statuses[LEFT_DOOR] = !statuses[LEFT_DOOR];
            }
            break;
        case RIGHT_DOOR:
            if (r_door_anim_frame == 0) { // TODO check if freddy or chica is in room
                r_door_anim_frame = NUM_DOOR_FRAMES;
                statuses[RIGHT_DOOR] = !statuses[RIGHT_DOOR];
            }
            break;
    }
}

//TODO for now, this has the side effect of animating the cam since it's called every frame the cam is not up.
// if it's called twice per frame, change this.
bool equipment_is_animating_cam() {
    if (cam_device_anim_timer) {
        cam_device_anim_timer--;
        // TODO graphics get frame timer+offset
        if (cam_device_anim_timer == 0) {
            vbaprint("cam anim timer is 0\n");
            if (cam_device_anim_offset == 0) { // if cams are now up
                vbaprint("cams are now up\n");
                Cameras.set_visible();
                statuses[CAMERA] = true;
            }
        }
        return true;
    }
    return false;
}

void equipment_update() {
    // TODO repetitive, clean
    if (l_door_anim_frame) {
        l_door_anim_frame--;
        vbaprint("l door frame\n");
        Graphics.load_left_door_frame(
                statuses[LEFT_DOOR] ? NUM_DOOR_FRAMES - l_door_anim_frame - 1 : l_door_anim_frame);
    }
    if (r_door_anim_frame) {
        r_door_anim_frame--;
        vbaprint("r door frame\n");
        Graphics.load_right_door_frame(
                statuses[RIGHT_DOOR] ? NUM_DOOR_FRAMES - r_door_anim_frame - 1 : r_door_anim_frame);
    }
}

struct EquipmentWrapper Equipment = {
        .get_usage = equipment_get_usage,
        .on_night_start = equipment_on_night_start,
        .toggle = equipment_toggle,
        .is_on = equipment_is_on,
        .is_animating_cam = equipment_is_animating_cam,
        .update = equipment_update
};