#include "power.h"
#include "util/util.h"

/* CONSTANTS */

/**
 * Drain applied each second,
 * where the index is the night num (Night 1: i=1)
 * and the value is the percent represented as an int (100% = 1000000)
 */
static int DRAIN_LEVELS_PER_SECOND[8] = {
        0, 0, 250, 300, 375, 500, 500, 500
};

/* END CONSTANTS */


int power; // 100% = 1000000 power is floored; so trim last 4 digits when displaying
int usage; // TODO change this to a function that runs a quick boolean operation on the lights, doors, and cams

/* these numbers are constant for each night; so to avoid costly division every frame, calculate at the start of each night */
int intervals[6];
int bonus_drain_per_second;
int foxy_drain_counter;

void update_power(int frame_num) {
    /* TODO is this correct? when does the timer reset in the original game?*/
    if (is_multiple(frame_num, intervals[usage])) {
        power -= 10000; /* TODO magic number, drains 1% each time */
    }
    if (is_multiple(frame_num, 60/*TODO magic num: 1 second*/)) {
        power -= bonus_drain_per_second;
    }
}

void power_on_night_start(int night_num) {
    /* CALC INTERVALS */
    // NOTE skips 0 so we can just use usage
    // TODO or skip the fan when calculating since it's always on?
    intervals[1] = 0; // this is just the base rate per night
    intervals[2] = 0; // 1u/2
    intervals[3] = 0; // 1u/3
    intervals[4] = 0; // 1u/4
    intervals[5] = 0; // 1u/5

    /* BONUS DRAIN */
    bonus_drain_per_second = DRAIN_LEVELS_PER_SECOND[night_num];

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
}

struct PowerWrapper Power = {
        .update = update_power,
        .on_night_start = power_on_night_start,
        .on_foxy_attack = power_on_foxy_attack
};
