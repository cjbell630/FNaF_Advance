#include "menu_loop.h"

#include "menu.h"

#include "debug.h"

void run_menu_loop() {
    init_menu();
    mgba_printf("initialized menu\n");
    activate_menu();
    mgba_printf("activate menu exited\n");
}