#ifndef FNAF_ADVANCE_CURSOR_H
#define FNAF_ADVANCE_CURSOR_H

struct CursorWrapper {
    void (*init)();
    void (*load)();
    void (*set_choice)(int choice);
};

extern struct CursorWrapper Cursor;


#endif //FNAF_ADVANCE_CURSOR_H