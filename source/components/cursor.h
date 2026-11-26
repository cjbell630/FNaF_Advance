#ifndef FNAF_ADVANCE_CURSOR_H
#define FNAF_ADVANCE_CURSOR_H
#include <stdbool.h>
#include "const/menu_options.h"

struct CursorWrapper {
    void (*load)();
    void (*hide)();
    void (*down)();
    void (*up)();
    bool (*set_choice)(enum MainMenuOption choice);
    enum MainMenuOption (*get_choice)();
};

extern struct CursorWrapper Cursor;


#endif //FNAF_ADVANCE_CURSOR_H
