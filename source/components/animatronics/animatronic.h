#ifndef FNAF_ADVANCE_ANIMATRONIC_H
#define FNAF_ADVANCE_ANIMATRONIC_H

#include "game/room_names.h"
#include <tonc_types.h>
#include "game_state.h"

#define MAX_LEVEL 20

struct Animatronic {
    int lvl;
    int room_num;
    int phase;
    u8 close_far;
    int timer;
    const enum RoomNames starting_room;

    //void (*init)();

    void (*update)(bool cams_are_up, enum RoomNames selected_cam);
    void (*on_night_start)();
};

bool try_move(struct Animatronic *anim);

void trigger_jumpscare(enum Jumpscares character, bool show_cams_animation);

#endif //FNAF_ADVANCE_ANIMATRONIC_H