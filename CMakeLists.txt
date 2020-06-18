cmake_minimum_required(VERSION 3.16)
project(cpp_tetris)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_tetris src/main.cpp include/model.h src/model.cpp src/gamelogic.cpp include/gamelogic.h)