#include <tonc_irq.h>
#include "debug.h"
#include "ctrl/menu_loop.h"
#include "ctrl/game_state.h"
#include "ctrl/game_loop.h"


int main() {
    mgba_printf("entry\n");
    irq_init(NULL);
    irq_add(II_VBLANK, NULL);
    GAME_PHASE = MENU_HOME;
    NIGHT_NUM = 0;

    while (1) {
        run_menu_loop();
        run_game_loop();
    }
    return 0;
}
