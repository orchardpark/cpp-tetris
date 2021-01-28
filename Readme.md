# CPP-Tetris

C++ implementation of the Tetris game.

## Compilation & Installation

Only tested on Ubuntu Linux. Windows is *not* supported.

Requirements:

- [CMake](https://cmake.org/) 3.16 or higher.
- [SDL2](https://www.libsdl.org/download-2.0.php)
  * Install `libsdl2-dev`
  * Install `libsdl2-ttf-dev`
  * Install `libsdl2-image-dev`
- [GTest](https://github.com/google/googletest) 
  * Install it by cloning the repo and copying its contents to `/lib/googletest`

In order to build this game first create the build directory
`mkdir build`. Change to build directory `cd build` then run 
`cmake ..` to configure and `make` to build. The program can then be run by
executing `./cpp-tetris`.

## Architecture


