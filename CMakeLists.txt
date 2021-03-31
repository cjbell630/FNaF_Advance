cmake_minimum_required(VERSION 3.17)
project(FNaF_Advance C)

set(CMAKE_C_STANDARD 11)

add_executable(FNaF_Advance
        source/main.c
        source/game/menu.c
        source/init.c source/game/game.c source/game/game.h source/game/graphics/bg_pal_handler.c
        source/game/graphics/bg_pal_handler.h source/game/control/cameras/camera.c source/game/control/cameras/camera.h
        source/game/control/controls.h source/game/control/game_clock.c source/game/control/game_clock.h
        source/util/random.h source/util/random.c source/util/util.h source/game/graphics/static_handler.c
        source/game/graphics/static_handler.h source/game/control/cameras/cam_nav.c source/game/control/cameras/cam_nav.h
        source/game/control/ai/ai.c source/game/control/ai/ai.h)
