#ifndef FNAF_ADVANCE_OBJECTS_H
#define FNAF_ADVANCE_OBJECTS_H

#include <stdbool.h>

enum ObjectNames {
    OBJECT_CURSOR
};

struct ObjectController {
    void (*load)(enum ObjectNames object_name);
    void (*set_position)(enum ObjectNames object_name, int x, int y);
    void (*show)(enum ObjectNames object_name);
    void (*hide)(enum ObjectNames object_name);
};

extern struct ObjectController Objects;

#endif //FNAF_ADVANCE_OBJECTS_H
