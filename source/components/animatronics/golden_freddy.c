#include "golden_freddy.h"
#include "DWedit/debug.h"
#include "util/random.h"
#include "game/room_names.h"

bool GOLDEN_FREDDY_APPEARED;

void golden_freddy_update(bool cams_are_up, enum RoomNames selected_cam) {
    if (GOLDEN_FREDDY_APPEARED) {
        return;
    }
    if (cams_are_up && selected_cam == ROOM_WEST_CORNER) {
        if (AnimatronicGoldenFreddy.room_num == ROOM_WEST_CORNER) {
            AnimatronicGoldenFreddy.room_num = ROOM_OFFICE;
            vbaprint("GOLDEN FREDDY IN OFFICE\n\n\n\n");
        }
        return;
    }
    if (AnimatronicGoldenFreddy.timer > -1) {
        AnimatronicGoldenFreddy.timer--;
        if (AnimatronicGoldenFreddy.timer < 1) {
            trigger_jumpscare(JUMPSCARE_GOLDEN, false);
        }
        return;
    }
    if (
        AnimatronicGoldenFreddy.room_num == AnimatronicGoldenFreddy.starting_room
        && frame_multiple(AnimatronicGoldenFreddy.movement_framecount)
    ) {
        vbaprint("Golden Freddy movement opp\n");
        if (rnd_max(10/* 34464TODO is this the number I wanna go with? also magic*/)==0) {
            vbaprint("GOLDEN FREDDY TRIGGERED!!!!!!!!!!!!!!\n\n\n\n\n\n\n\n\n\n");
            AnimatronicGoldenFreddy.room_num = ROOM_WEST_CORNER;
        }
    }
}

void golden_freddy_on_cams_up() {
    // if golden freddy is in the office and the cams are brought up, end his appearance
    if (AnimatronicGoldenFreddy.room_num == ROOM_OFFICE) {
        vbaprint("GOLDEN FREDDY RESET\n\n\n\n");
        AnimatronicGoldenFreddy.room_num = AnimatronicGoldenFreddy.starting_room;
        GOLDEN_FREDDY_APPEARED = true;
        AnimatronicGoldenFreddy.timer = -1;
    }
}

void golden_freddy_on_cams_down() {
    if (AnimatronicGoldenFreddy.room_num == ROOM_OFFICE) {
        vbaprint("GOLDEN FREDDY JUMPSCARE TIMER STARTED\n\n\n\n");
        AnimatronicGoldenFreddy.timer = 300;
    }
}

void golden_freddy_on_night_start() {
    AnimatronicGoldenFreddy.room_num = AnimatronicGoldenFreddy.starting_room;
    AnimatronicGoldenFreddy.timer = -1;
    GOLDEN_FREDDY_APPEARED = false;
}

struct Animatronic AnimatronicGoldenFreddy = {
    .on_night_start = &golden_freddy_on_night_start,
    .starting_room = ROOM_NOWHERE,
    .movement_framecount = 60,
    .update = &golden_freddy_update,
    .on_cams_up = &golden_freddy_on_cams_up,
    .on_cams_down = &golden_freddy_on_cams_down
};
