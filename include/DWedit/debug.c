#include "debug.h"

/**
 * Override for mgba_printf (see debug.s)
 * When a ROM is compiled with this (debug.c) instead of debug.s,
 * mgba_printf calls will not cause a crash when run on real hardware.
 */
void mgba_printf(const char* message) {
    return;
}
