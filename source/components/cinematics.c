#include "cinematics.h"
#include "images/office/office.h"
#include "images/backgrounds/newspaper/newspaper.h"
#include "images/backgrounds/static/static.h"
#include "images/backgrounds/loading/loading.h"
#include "tonc.h"
#include "DWedit/debug.h"
#include "graphics/bg_pal_handler.h"
#include "graphics/static_handler.h"

const int NEWSPAPER_PB = 1;
const int NEWSPAPER_CBB = 0;
const int NEWSPAPER_SBB = 28;

void cinematics_play_newspaper() {
    vbaprint("done showing newspaper palette\n");
    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0; // load newspaper into memory
    // Load palette
    load_bg_pal(newspaperPal, newspaperPalLen, NEWSPAPER_PB);
    set_bg_palbank(NEWSPAPER_PB);

    // Load tiles into CBB 0
    memcpy(&tile_mem[NEWSPAPER_CBB][0], newspaperTiles, newspaperTilesLen);

    // Load map into SBB 30
    memcpy(&se_mem[NEWSPAPER_SBB][0], newspaperMap, newspaperMapLen);
    REG_BG0CNT = BG_CBB(NEWSPAPER_CBB) | BG_SBB(NEWSPAPER_SBB) | BG_4BPP | BG_REG_32x32;
    REG_DISPCNT = DCNT_BG0 | DCNT_MODE0;
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
    //TODO show night intro screen

    vbaprint("\n\n\n\n\n\nNIGHT XXXX 12AM\n\n\n\n\n\n\n");

    /* SHOW 2 SECONDS */
    int timer = 120;
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

void cinematics_play_night_victory() {
    vbaprint("\n\n\n\n\n\n5AM..........\n\n\n\n\n");
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

    vbaprint("\n\n\n\n\n\n6AM!!!!!!\n\n\n\n\n");

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
    vbaprint("\n\n\n\n\n\nSTATIC\n\n\n\n\n");

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

    vbaprint("\n\n\n\n\n\nYOU DIED\n\n\n\n\n");
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
