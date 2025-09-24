#ifndef FNAF_ADVANCE_CINEMATICS_H
#define FNAF_ADVANCE_CINEMATICS_H


struct CinematicsWrapper {
    void (*play_newspaper)();
    void (*play_night_intro)();
    void (*play_night_victory)();
    void (*play_night_death)();
};

extern struct CinematicsWrapper Cinematics;

#endif //FNAF_ADVANCE_CINEMATICS_H