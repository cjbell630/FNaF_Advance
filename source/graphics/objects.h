#ifndef FNAF_ADVANCE_OBJECTS_H
#define FNAF_ADVANCE_OBJECTS_H

enum ObjectNames {
    OBJECT_CURSOR
};

struct ObjectsWrapper {
    void (*load)(enum ObjectNames object_name);
    void (*set_position)(enum ObjectNames object_name, int x, int y);
};

extern struct ObjectsWrapper Objects;

#endif //FNAF_ADVANCE_OBJECTS_H
