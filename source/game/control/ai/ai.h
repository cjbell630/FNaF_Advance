#ifndef FNAF_ADVANCE_AI_H
#define FNAF_ADVANCE_AI_H

//TODO move these to another file about anim identities
// or make it an attribute of Animatronic?
#define FREDDY_FRAMECOUNT 180
#define FOXY_FRAMECOUNT 305
#define BONNIE_FRAMECOUNT 298
#define CHICA_FRAMECOUNT 300

#define MAX_LEVEL 20

struct Animatronic {
    int lvl;
    int room_num;

    void (*init)();

    void (*update)(int frame_num);
};

extern struct Animatronic FREDDY;
extern struct Animatronic BONNIE;

struct AnimatronicsWrapper {
    void (*update)(int frame_num);
    void (*reset)();
    void (*set_levels)(int b_lvl, int c_lvl, int fr_lvl, int fo_lvl);
    char (*get_room_occupants)(int room_num);
};
extern struct AnimatronicsWrapper Animatronics;

#endif //FNAF_ADVANCE_AI_H
