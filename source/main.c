#include "ctrl/menu_loop.h"
#include "ctrl/game_state.h"
#include "ctrl/game_loop.h"

#include "debug.h"
#include <tonc_irq.h>

int main() {
    mgba_printf("entry\n");
    irq_init(NULL);
    irq_add(II_VBLANK, NULL);

    reset_game_state();

    while (1) {
        run_menu_loop();
        run_game_loop();
    }
    return 0;
}
