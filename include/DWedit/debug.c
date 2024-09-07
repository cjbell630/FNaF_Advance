#include "debug.h"

/**
 * Override for vbaprint (see debug.s)
 * When a ROM is compiled with this (debug.c) instead of debug.s,
 * vbaprint calls will not cause a crash when run on real hardware.
 */
void vbaprint(const char *message) {
    return;
}