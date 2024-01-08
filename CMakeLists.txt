cmake_minimum_required(VERSION 3.16)

project(snake)

set(src game.cpp print.cpp print.h)

add_executable(snake ${src})

target_link_libraries(snake ncurses)
