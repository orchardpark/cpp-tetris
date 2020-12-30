set(BINARY ${CMAKE_PROJECT_NAME})
set(SOURCES main.cpp ../include/model.h model.cpp gamelogic.cpp ../include/gamelogic.h)
add_executable(${BINARY}_run ${SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES})
