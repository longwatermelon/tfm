cmake_minimum_required(VERSION 3.20.5)
set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(tfm)

add_executable(tfm
    src/main.c
    src/prog.h
    src/prog.c
    src/fs.h
    src/fs.c
)

target_compile_options(tfm PRIVATE -ggdb)
target_link_libraries(tfm PRIVATE ncurses)

