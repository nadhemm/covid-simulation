cmake_minimum_required(VERSION 3.17)
project(c_project C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(c_project
        main.c)