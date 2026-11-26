#ifndef FNAF_ADVANCE_SOUND_H
#define FNAF_ADVANCE_SOUND_H

enum Sounds {
    SOUND_WINDOWSCARE, SOUND_CAM_BLIP, SOUND_EQUIPMENT_DISABLED
};

struct SoundController {
    void (*play)(enum Sounds sound);
};

extern struct SoundController Sound;

#endif //FNAF_ADVANCE_SOUND_H
