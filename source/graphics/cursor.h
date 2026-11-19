#ifndef FNAF_ADVANCE_CURSOR_H
#define FNAF_ADVANCE_CURSOR_H

enum MainMenuOption {
    MENU_NEW_GAME, MENU_CONTINUE, MENU_NIGHT_SIX, MENU_CUSTOM_NIGHT
};

struct CursorWrapper {
    void (*load)();
    void (*set_choice)(enum MainMenuOption choice);
    enum MainMenuOption (*get_choice)();
};

extern struct CursorWrapper Cursor;


#endif //FNAF_ADVANCE_CURSOR_H
