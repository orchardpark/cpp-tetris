cmake_minimum_required(VERSION 3.16)

project(cpp_tetris)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
include_directories(src)
add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib/googletest)


# copy fonts
file(COPY fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# copy textures
file(COPY textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

