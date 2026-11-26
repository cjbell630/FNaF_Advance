#ifndef FNAF_ADVANCE_SOUND_H
#define FNAF_ADVANCE_SOUND_H

enum Sounds {
    SOUND_WINDOWSCARE
};

struct SoundController {
    void (*play)(enum Sounds sound);
};

extern struct SoundController Sound;

#endif //FNAF_ADVANCE_SOUND_H
