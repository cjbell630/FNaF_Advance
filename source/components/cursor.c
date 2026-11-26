#include "components/cursor.h"
#include "tonc.h"
#include <string.h>
#include "images/sprites/cursor/cursor_image.h"

enum MainMenuOption choice; // TODO handle for other menus
OBJ_ATTR *cursor;
// TODO move
#define CURSOR_TILE_START 1
#define CURSOR_PALBANK 0
#define LAYER_0 3
#define LAYER_1 2
#define LAYER_2 1
#define LAYER_3 0

#define CURSOR_X 20
#define OPTION_Y(n) (95+15*(n))



enum MainMenuOption cursor_get_choice() {
    return choice;
}

void cursor_load() {
    cursor = &oam_mem[0];
    obj_set_attr(
            cursor,
            ATTR0_REG | ATTR0_SQUARE | ATTR0_4BPP,
            ATTR1_SIZE_8x8,
            ATTR2_PALBANK(CURSOR_PALBANK) | ATTR2_ID(CURSOR_TILE_START) | ATTR2_PRIO(LAYER_0)
    );

    obj_unhide(cursor, ATTR0_REG);
    memcpy(&tile_mem[4][CURSOR_TILE_START], &cursor_imageTiles, cursor_imageTilesLen);
    memcpy(&pal_obj_bank[CURSOR_PALBANK], &cursor_imagePal, cursor_imagePalLen);
    //cursor_set_choice(choice);
}

void cursor_hide() {
    obj_hide(cursor);
}


bool cursor_set_choice(enum MainMenuOption newChoice) {
    // TODO check if option is selectable based on game progress

    choice = newChoice;
    obj_set_pos(cursor, CURSOR_X, OPTION_Y(choice));
    return true;
}

void cursor_down() {
    int new_choice = choice + 1;
    while (new_choice < 2/*TODO magic*/ && !cursor_set_choice(new_choice)) {
        new_choice++;
    }
}

void cursor_up() {
    int new_choice = choice - 1;
    while (new_choice > -1 && !cursor_set_choice(new_choice)) {
        new_choice--;
    }
}


struct CursorWrapper Cursor = {
    .load = &cursor_load,
    .hide = &cursor_hide,
    .down = &cursor_down,
    .up = &cursor_up,
    .set_choice = &cursor_set_choice,
    .get_choice = &cursor_get_choice
};