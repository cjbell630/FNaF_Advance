#ifndef FNAF_ADVANCE_ANIMATRONICS_H
#define FNAF_ADVANCE_ANIMATRONICS_H

#include <tonc_types.h>
#include "game/room_names.h"
#include "animatronic.h"

#define NIGHT_1_START_LEVELS 0, 0, 0, 0
#define NIGHT_2_START_LEVELS 0, 3, 1, 1
#define NIGHT_3_START_LEVELS 1, 0, 5, 2
// TODO check notes wtf is 1 or 2???
#define NIGHT_4_START_LEVELS 2, 2, 4, 6
#define NIGHT_5_START_LEVELS 3, 5, 7, 5
#define NIGHT_6_START_LEVELS 4, 10, 12, 16


#define OCCUPANTS_EMPTY 0
#define OCCUPANTS_ONLY_FOXY 0b1000
#define OCCUPANTS_ONLY_CHICA 0b0100
#define OCCUPANTS_ONLY_BONNIE 0b0010
#define OCCUPANTS_ONLY_FREDDY 0b0001

struct AnimatronicsWrapper {
    void (*update)(bool cams_are_up, enum RoomNames selected_cam);
    void (*update_power_off)();

    void (*reset)();

    void (*on_night_start)();

    void (*on_hour)(int hour);

    void (*on_power_off)();

    void (*set_levels)(int b_lvl, int c_lvl, int fr_lvl, int fo_lvl); // NOTE keep for custom night
    u8 (*get_room_occupants)(enum RoomNames room);
};

extern struct AnimatronicsWrapper Animatronics;

#endif //FNAF_ADVANCE_ANIMATRONICS_H
