set(BINARY ${CMAKE_PROJECT_NAME})
set(SOURCES main.cpp ../include/model.h model.cpp "game.cpp" "../include/game.h" "gui.cpp")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(SDL2 REQUIRED)
find_package(SDL2TTF REQUIRED)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR} ${SDL2IMAGE_INCLUDE_DIRS})
add_executable(${BINARY}_run ${SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES})

# sdl2 include & libs
target_include_directories(${BINARY}_run PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR})
target_link_libraries(${BINARY}_run ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARY} ${SDL2IMAGE_LIBRARIES})
