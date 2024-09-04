#ifndef FNAF_ADVANCE_POWER_H
#define FNAF_ADVANCE_POWER_H


struct PowerWrapper {
    void (*update)(int frame_num);
    void (*on_night_start)(int night_num);
    void (*on_foxy_attack)();
};

extern struct PowerWrapper Power;



#endif //FNAF_ADVANCE_POWER_H
