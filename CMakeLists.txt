cmake_minimum_required(VERSION 3.20)

project(bitC C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)


add_executable(bitC
    src/main.c
    src/display.c
    src/helper.c
    src/attack_tables.c
    src/init_attack.c
)

target_include_directories(bitC PRIVATE headers)
