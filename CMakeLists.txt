cmake_minimum_required(VERSION 3.17)
project(FNaF_Advance)

set(CMAKE_C_STANDARD 17)

find_library(TONC_LIB libtonc)

include_directories(
        ${CMAKE_SOURCE_DIR}/source
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_SOURCE_DIR}/include
)

file(GLOB_RECURSE SOURCE_C "source/*.c")
file(GLOB_RECURSE SOURCE_H "source/*.h")

add_executable(FNaF_Advance ${SOURCE_C} ${SOURCE_H})

target_link_libraries(FNaF_Advance ${TONC_LIB})
