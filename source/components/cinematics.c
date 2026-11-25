#include "cinematics.h"
#include "images/office/office.h"
#include "images/backgrounds/newspaper/newspaper.h"
#include "images/backgrounds/static/static.h"
#include "images/backgrounds/loading/loading.h"
#include "tonc.h"
#include "debug.h"
#include "graphics/background.h"
#include "graphics/bg_pal_handler.h"
#include "graphics/display.h"
#include "graphics/static_handler.h"
#include "graphics/effects/cam_blip.h"


void cinematics_play_newspaper() {
    // TODO this is temp just to clear BG03
    CamBlipEffect.init();
    CamBlipEffect.load();

    Background.set_newspaper();
    Display.set_still_cinematic();
    /* TODO FADE in 2 SECONDS */
    int timer = 120;
    while (timer >= 0) {
        VBlankIntrWait();
        timer--;
    }
    /* SHOW 5 SECONDS */
    timer = 300;
    while (timer >= 0) {
        VBlankIntrWait();
        timer--;
    }
    /* TODO FADE OUT 2 SECONDS */
    timer = 120;
    while (timer >= 0) {
        VBlankIntrWait();
        timer--;
    }
}

void cinematics_play_night_intro() {
    Background.set_night_intro();
    Display.set_still_cinematic();
    mgba_printf("\n\n\n\n\n\nNIGHT XXXX 12AM\n\n\n\n\n\n\n");


    CamBlipEffect.init();
    CamBlipEffect.load();
    CamBlipEffect.reset();
    CamBlipEffect.start();
    // TODO play blip sound

    /* SHOW 2 SECONDS */
    int timer = 120;
    while (timer >= 0) {
        CamBlipEffect.update();
        VBlankIntrWait();
        timer--;
    }
    /* TODO FADE OUT 1 SECOND */
    timer = 60;
    while (timer >= 0) {
        VBlankIntrWait();
        timer--;
    }
}

void cinematics_play_night_victory() {
    mgba_printf("\n\n\n\n\n\n5AM..........\n\n\n\n\n");
    /* TODO FADE IN 1 SECOND */
    int timer = 60;
    while (timer >= 0) {
        VBlankIntrWait();
        timer--;
    }

    /* TODO SCROLL 5 SECONDS */
    timer = 300;
    while (timer >= 0) {
        VBlankIntrWait();
        timer--;
    }

    mgba_printf("\n\n\n\n\n\n6AM!!!!!!\n\n\n\n\n");

    /* SHOW 3 SECONDS */
    timer = 180;
    while (timer >= 0) {
        VBlankIntrWait();
        timer--;
    }
    /* TODO FADE OUT 1 SECOND */
    timer = 60;
    while (timer >= 0) {
        VBlankIntrWait();
        timer--;
    }
}

void cinematics_play_night_death() {
    mgba_printf("\n\n\n\n\n\nSTATIC\n\n\n\n\n");

    /* TODO SHOW STATIC 10 SECONDS */
    int timer = 600;
    while (timer >= 0) {
        VBlankIntrWait();
        timer--;
    }

    /* TODO FADE IN DEATH SCREEN 1 SECOND */
    timer = 60;
    while (timer >= 0) {
        VBlankIntrWait();
        timer--;
    }

    mgba_printf("\n\n\n\n\n\nYOU DIED\n\n\n\n\n");
    /* SHOW 10 SECONDS */
    timer = 600;
    while (timer >= 0) {
        VBlankIntrWait();
        timer--;
    }
}

struct CinematicsWrapper Cinematics = {
    .play_newspaper = &cinematics_play_newspaper,
    .play_night_intro = &cinematics_play_night_intro,
    .play_night_victory = &cinematics_play_night_victory,
    .play_night_death = &cinematics_play_night_death
};
