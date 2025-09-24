#include "animatronics_controller.h"
#include "animatronic.h"
#include "DWedit/debug.h"
#include "util/random.h"
#include "util/util.h"
#include "game/room_names.h"
#include "game_state.h"
#include "components/equipment.h"
#include "components/graphics.h"
#include "components/power.h"
#include <stdio.h>
#include "foxy.h"
#include "bonnie.h"
#include "freddy.h"
#include "chica.h"

/* PREREQS */
// some functions in this file use the frame_multiple and NIGHT_NUM globals

/* CONSTANTS */


enum FreddyPowerOffPhases {
    FREDDY_POWEROFF_WAITING, FREDDY_POWEROFF_MUSIC_BOX, FREDDY_POWEROFF_BLACKOUT
};

/* END CONSTANTS */



/*  COLLECTIVE  */
void set_levels(int fr_lvl, int b_lvl, int c_lvl, int fo_lvl) { // TODO make these orders consistent or something please
    BONNIE.lvl = b_lvl;
    FREDDY.lvl = fr_lvl;
    CHICA.lvl = c_lvl;
    FOXY.lvl = fo_lvl;
}

void on_night_start() {
    // TODO a little cringe, maybe there's a better way to write this
    switch (NIGHT_NUM) {
        case 1:
            set_levels(NIGHT_1_START_LEVELS);
            break;
        case 2:
            set_levels(NIGHT_2_START_LEVELS);
            break;
        case 3:
            set_levels(NIGHT_3_START_LEVELS);
            break;
        case 4:
            set_levels(NIGHT_4_START_LEVELS);
            break;
        case 5:
            set_levels(NIGHT_5_START_LEVELS);
            break;
        case 6:
            set_levels(NIGHT_6_START_LEVELS);
            break;
        default: // custom night
            break;
    }
    FREDDY.on_night_start();
    BONNIE.on_night_start();
    CHICA.on_night_start();
    FOXY.on_night_start();
}

void update_anims(bool cams_are_up, enum RoomNames selected_cam) {
    // TODO can I put them in a list or something and do for each, and then say if frame mult of internal attribute
    BONNIE.update(cams_are_up, selected_cam);
    FREDDY.update(cams_are_up, selected_cam);
    CHICA.update(cams_are_up, selected_cam);
    FOXY.update(cams_are_up, selected_cam);
}

void update_power_off() {
    // TODO this could be relegated to the game loop to reduce checks, but it might make the loop code a bit messy
    // TODO magic numbers
    FREDDY.timer--;
    switch (FREDDY.phase) {
        case FREDDY_POWEROFF_WAITING:
            // TODO this could cause freddy to immediately show his face on power down;
            // is there a guaranteed 5 seconds before the checks begin?
            if (FREDDY.timer < 1 || (frame_multiple(300) && rnd_max(5) == 0)) {
                FREDDY.phase++;
                FREDDY.timer = 1200;
                vbaprint("Freddy face is now visible and music box is playing\n");
                // TODO trigger visual audio etc
            }
            break;
        case FREDDY_POWEROFF_MUSIC_BOX:
            // TODO trigger freddy face update
            if (FREDDY.timer < 1 || (frame_multiple(300) && rnd_max(5) == 0)) {
                FREDDY.phase++;
                FREDDY.timer = 1200;
                vbaprint("Full blackout now\n");
                // TODO trigger visual audio etc
            }
            break;
        case FREDDY_POWEROFF_BLACKOUT:
            if (FREDDY.timer < 1 || (frame_multiple(120) && rnd_max(5) == 0)) {
                trigger_jumpscare(JUMPSCARE_FREDDY_POWER, false);
            }
            break;
    }
}

/**
 * To be called when the hour changes ex. 1->2 3->4
 *
 * @param hour the CURRENT hour
 */
void on_hour(int hour) {
    switch (hour) {
        case 2:
            BONNIE.lvl++;
            vbaprint("bonnie level increased\n");
            break;
        case 3:
        case 4:
            BONNIE.lvl++;
            FOXY.lvl++;
            CHICA.lvl++;
            vbaprint("bonnie, foxy, and chica levels increased\n");
            break;
        default:
            break;
    }
}

void on_power_off() {
    FREDDY.phase = FREDDY_POWEROFF_WAITING;
    FREDDY.timer = 1200;
}

// TODO define this in camera.c?
u8 get_room_occupants(enum RoomNames room) {
    return ((FOXY.room_num == room) << 3) | ((CHICA.room_num == room) << 2) |
           ((BONNIE.room_num == room) << 1) | (FREDDY.room_num == room);
}

struct AnimatronicsWrapper Animatronics = {
    .update = update_anims,
    .on_night_start = on_night_start,
    .set_levels = set_levels,
    .get_room_occupants = get_room_occupants,
    .on_hour = on_hour,
    .on_power_off = on_power_off,
    .update_power_off = update_power_off
};
