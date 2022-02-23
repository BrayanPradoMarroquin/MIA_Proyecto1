cmake_minimum_required(VERSION 3.21)
project(Proyecto1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Proyecto1
        Analizador.h
        main.cpp
        mk.h)
