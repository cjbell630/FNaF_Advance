#ifndef FNAF_ADVANCE_ANIMATRONICS_H
#define FNAF_ADVANCE_ANIMATRONICS_H

#include "game/room_names.h"

//TODO move these to another file about anim identities
// or make it an attribute of Animatronic?
#define FREDDY_FRAMECOUNT 180
#define FOXY_FRAMECOUNT 305
#define BONNIE_FRAMECOUNT 298
#define CHICA_FRAMECOUNT 300

#define NIGHT_1_START_LEVELS 0, 0, 0, 0
#define NIGHT_2_START_LEVELS 0, 3, 1, 1
#define NIGHT_3_START_LEVELS 1, 0, 5, 2
// TODO check notes wtf is 1 or 2???
#define NIGHT_4_START_LEVELS 2, 2, 4, 6
#define NIGHT_5_START_LEVELS 3, 5, 7, 5
#define NIGHT_6_START_LEVELS 4, 10, 12, 16

#define MAX_LEVEL 20



struct Animatronic {
    int lvl;
    int room_num;
    const enum RoomNames starting_room;

    //void (*init)();

    void (*update)(int frame_num);
};

extern struct Animatronic FREDDY;
extern struct Animatronic BONNIE;
extern struct Animatronic CHICA;
extern struct Animatronic FOXY;

struct AnimatronicsWrapper {
    void (*update)(int frame_num);
    void (*reset)();
    void (*on_night_start)(int night_num);
    void (*on_hour)(int hour);
    void (*set_levels)(int b_lvl, int c_lvl, int fr_lvl, int fo_lvl); // NOTE keep for custom night
    char (*get_room_occupants)(enum RoomNames room);
};
extern struct AnimatronicsWrapper Animatronics;

#endif //FNAF_ADVANCE_ANIMATRONICS_H
