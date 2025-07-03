#include "power.h"
#include "util/util.h"
#include "tonc_types.h"
#include "game_state.h"
#include "DWedit/debug.h"

/* PREREQS */
// some functions in this file use the frame_multiple and NIGHT_NUM globals

/* CONSTANTS */

// technically the max power would be 100% = 1,000,000
// but in the og game for whatever reason it starts at 99.9% = 999
static const int MAX_POWER = 999000;

// the standard amount of power drained at various intervals depending on the night.
// equal to 0.1% power
static const int STD_POWER_DRAIN = 1000;

/* END CONSTANTS */


int power; // 100% = 1000000 power is floored; so trim last 4 digits when displaying

int bonus_drain_interval;
int foxy_drain_counter;

void update_power(byte usage) {
    if (frame_multiple(60/*TODO magic num: 1 second*/)) {
        // could make this a lookup table but all sources point to this being not any more efficient
        power -= (usage * STD_POWER_DRAIN); // drains usage*0.1% each second
        vbaprint("power drained 0.1%*usage (per second)\n");

        // all of the bonus drain intervals are multiples of 60 so this reduces comparisons
        if (frame_multiple(bonus_drain_interval)) {
            vbaprint("power drained 0.1% (bonus)\n");
            power -= STD_POWER_DRAIN; /* TODO magic number, drains 0.1% each time */
        }
    }
    if (power <= 0) {
        GAME_PHASE = NIGHT_POWER_OFF; // TODO maybe call an on_power_empty function somewhere
    }
}

void power_on_night_start() {
    power = MAX_POWER; // set power to max

    /* BONUS DRAIN */
    switch (NIGHT_NUM) {
        case 1: // Night 1 does not have bonus drain
            bonus_drain_interval = 130881600; //TODO magic number, frame_max from game_state
        case 2:
            bonus_drain_interval = 360; // 6s/360f
        case 3:
            bonus_drain_interval = 300; // 5s/300f
        case 4:
            bonus_drain_interval = 240; // 4s/240f
        default: // Night 5, 6, and Custom
            bonus_drain_interval = 180; // 3s/180f
    }

    /* FOXY COUNTER */
    foxy_drain_counter = 0;
}

/**
 * To be called when Foxy attacks the player, as he drains power each time.
 * The amount taken corresponds to:
 *      `(5a + 1)%` where `a` is the number of times Foxy has drained power that night.
 *      So the first time he takes 1%, then 6%, then 11%, etc
 * TODO should the foxy counter be in anims? does it need to know?
 */
void power_on_foxy_attack() {
    power -= (50000 * foxy_drain_counter) + 10000;
    foxy_drain_counter++;
    vbaprint("foxy drained power\n");
}

struct PowerWrapper Power = {
        .update = update_power,
        .on_night_start = power_on_night_start,
        .on_foxy_attack = power_on_foxy_attack
};
