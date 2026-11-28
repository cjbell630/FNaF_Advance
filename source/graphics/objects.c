#include "objects.h"

#include <tonc_oam.h>

void object_load(enum ObjectNames object_name) {
}

void object_set_pos(enum ObjectNames object_name, int x, int y) {
    obj_set_pos(&oam_mem[object_name], x, y);
}

void object_hide(enum ObjectNames object_name) {
    obj_hide(&oam_mem[object_name]);
}

void object_show(enum ObjectNames object_name) {
    obj_unhide(&oam_mem[object_name], ATTR0_REG); // TODO mode
}

struct ObjectController Objects = {
    .load = &object_load,
    .set_position = &object_set_pos,
    .show = &object_show,
    .hide = &object_hide
};
