cmake_minimum_required(VERSION 3.20)

project(bitC C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB PIECES_SOURCES src/pieces/*.c)
file(GLOB HELPER_SOURCES src/helper/*.c)

add_executable(bitC
    src/main.c
    src/init_attack.c
    src/occupancy.c
    src/attack.c
    src/moves.c

    ${PIECES_SOURCES}
    ${HELPER_SOURCES}
)

target_include_directories(bitC PRIVATE headers)
