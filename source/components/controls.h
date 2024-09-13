#ifndef FNAF_ADVANCE_CONTROLS_H
#define FNAF_ADVANCE_CONTROLS_H


struct ControlsWrapper {
    void (*update_office)();
    void (*update_cam)();
    void (*update_menu)();

    /* CALLBACKS */
    //void (*on_menu_select)();
    //void
    /* END CALLBACKS */
};

extern struct ControlsWrapper Controls;

#endif //FNAF_ADVANCE_CONTROLS_H
