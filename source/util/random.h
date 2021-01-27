//
// From https://www.coranac.com/tonc/text/gfx.htm#cd-qran, tweaked to allow modification from key inputs
//

#ifndef FNAF_ADVANCE_RANDOM_H
#define FNAF_ADVANCE_RANDOM_H

void scramble_rng(int modifier);

int rnd();

int rnd_max(int max);

int rnd_exclude(int max, int exclude);


#endif //FNAF_ADVANCE_RANDOM_H
