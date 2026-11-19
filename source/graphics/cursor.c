#include "cursor.h"
#include "tonc.h"
#include <string.h>
#include "images/sprites/cursor/cursor_image.h"

int choice;
OBJ_ATTR *cursor;
#define TILE_START 0
#define LAYER_0 3
#define LAYER_1 2
#define LAYER_2 1
#define LAYER_3 0

void cursor_init() {
    choice = 0;
}

void cursor_load() {
    cursor = &oam_mem[0];
    obj_set_attr(
            cursor,
            ATTR0_REG ,//| ATTR0_SQUARE | ATTR0_4BPP,
            ATTR1_SIZE_8x8,
            ATTR2_PALBANK(0) | ATTR2_ID(0) | ATTR2_PRIO(LAYER_0)
    );

    obj_unhide(cursor, ATTR0_REG);
    memcpy(&tile_mem[4][0], &cursor_imageTiles, cursor_imageTilesLen);
    memcpy(&pal_obj_bank[0], &cursor_imagePal, cursor_imagePalLen);
    obj_set_pos(cursor, 0 , 0);
}

void cursor_set_choice(int newChoice) {

}

struct CursorWrapper Cursor = {
    .init = &cursor_init,
    .load = &cursor_load,
    .set_choice = &cursor_set_choice
};