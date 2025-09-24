#include "animatronic.h"
#include "game_state.h"
#include "util/random.h"

/**
 * Rolls to see if an animatronic can move.
 * The odds of moving at each opportunity (opportunity frequency differs for each anim) are
 * lvl / MAX_LEVEL
 * Where lvl is the animatronic's level
 * Ex. If the animatronic is set to level 1, there is a 1/20 chance it can move
 *     If the animatronic is set to level 19, there is a 19/20 chance it can move
 * @param anim a pointer to the anim to check for
 * @return true if the anim can move on this opportunity, false if not
 */
bool try_move(struct Animatronic *anim) {
    return anim->lvl >= (rnd_max(MAX_LEVEL) + 1);
}


void trigger_jumpscare(enum Jumpscares character, bool show_cams_animation) {
    JUMPSCARER = character;
    SHOW_CAM_ANIM_ON_JUMPSCARE = show_cams_animation;
    GAME_PHASE = NIGHT_JUMPSCARE;
}