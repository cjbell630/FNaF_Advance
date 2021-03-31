#ifndef FNAF_ADVANCE_AI_H
#define FNAF_ADVANCE_AI_H

struct Animatronic {
    int lvl;
    int room_num;

    const char cam_occ; //TODO: may need to make unsigned

    void (*init)();

    void (*move_opp)(int roll);
};

extern struct Animatronic FREDDY;
extern struct Animatronic BONNIE;

extern void init_anims(int b_lvl, int c_lvl, int fr_lvl, int fo_lvl);

#endif //FNAF_ADVANCE_AI_H
