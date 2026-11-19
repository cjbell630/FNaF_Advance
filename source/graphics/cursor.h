#ifndef FNAF_ADVANCE_CURSOR_H
#define FNAF_ADVANCE_CURSOR_H

enum MainMenuOptions {
    NEW_GAME,CONTINUE,NIGHT_SIX,CUSTOM_NIGHT
};

struct CursorWrapper {
    void (*load)();
    void (*set_choice)(int choice);
};

extern struct CursorWrapper Cursor;


#endif //FNAF_ADVANCE_CURSOR_H