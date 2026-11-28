#include "objects.h"

#include <tonc_oam.h>

void object_load(enum ObjectNames object_name) {

}

void object_set_pos(enum ObjectNames object_name, int x, int y) {
    obj_set_pos(&oam_mem[object_name], x, y);
}

struct ObjectsWrapper Objects = {
    .load = &object_load,
    .set_position = &object_set_pos
};