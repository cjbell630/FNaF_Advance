# ENVIRONMENT CHECKS!!

message(STATUS "Checking environment... ")

if(NOT CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR
            "\nPlease call CMake with: \n"
            "  -DCMAKE_TOOLCHAIN_FILE=[path to /devkitpro/ directory]/cmake/GBA.cmake\n"
    )
endif()

if(NOT DEFINED DKP_GBA_PLATFORM_LIBRARY OR
        NOT DKP_GBA_PLATFORM_LIBRARY STREQUAL "libtonc")
    message(FATAL_ERROR
            "\nPlease call CMake with:\n"
            "  -DDKP_GBA_PLATFORM_LIBRARY=libtonc\n"
    )
endif()

message(STATUS "Passed checks! :)")


cmake_minimum_required(VERSION 3.17)
project(FNaF_Advance C ASM)

set(CMAKE_C_STANDARD 17)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS source/*.c)
file(GLOB_RECURSE ASSET_FILES CONFIGURE_DEPENDS assets/*.c)
set(DEBUG_H_FILE include/debug.h)

set(ALL_SOURCES ${SRC_FILES} ${ASSET_FILES} ${DEBUG_H_FILE})
find_program(gbafix gbafix HINTS "$ENV{DEVKITPRO}/tools/bin")

add_executable(${PROJECT_NAME} ${ALL_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
        source
        assets
        include
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
)

target_compile_options(${PROJECT_NAME} PRIVATE
        -O2
        -Wall
        -fno-strict-aliasing
)
target_link_libraries(${PROJECT_NAME} tonc)
target_link_options(${PROJECT_NAME} PRIVATE -specs=gba.specs)

set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_NAME ${PROJECT_NAME}
        SUFFIX ".elf"
)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary
        $<TARGET_FILE:${PROJECT_NAME}>
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.gba
        COMMAND ${DEVKITPRO}/tools/bin/gbafix ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.gba -t${PROJECT_NAME}
        COMMENT "Fixing ROM..."
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.gba ${PROJECT_SOURCE_DIR}/out/${PROJECT_NAME}.gba
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.*
        COMMENT "Cleaning and moving ROM to ${PROJECT_SOURCE_DIR}/out ..."
)
