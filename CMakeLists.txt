cmake_minimum_required(VERSION 3.17)
project(FNaF_Advance C)

set(CMAKE_C_STANDARD 11)

add_executable(FNaF_Advance
        source/main.c
        source/menu.c
        source/init.c source/init.c source/init.c source/game.c source/game.h source/screen_handler.c source/screen_handler.h source/camera.c source/camera.h source/controls.h)
