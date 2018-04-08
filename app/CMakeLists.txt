cmake_minimum_required(VERSION 3.5)
project(vDODV)
set(CMAKE_CXX_STANDARD 14)

find_package(libcluon REQUIRED)
include_directories(SYSTEM ${CLUON_INCLUDE_DIRS})

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/messages.cpp
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   COMMAND cluon-msc --cpp-sources --cpp-add-include-file=messages.hpp --out=${CMAKE_BINARY_DIR}/messages.cpp ${CMAKE_CURRENT_SOURCE_DIR}/messages.odvd
                   COMMAND cluon-msc --cpp-headers --out=${CMAKE_BINARY_DIR}/messages.hpp ${CMAKE_CURRENT_SOURCE_DIR}/messages.odvd
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/messages.odvd)
include_directories(SYSTEM ${CMAKE_BINARY_DIR})

INCLUDE (CheckIncludeFiles)
# usage: CHECK_INCLUDE_FILES (<header> <RESULT_VARIABLE> )

CHECK_INCLUDE_FILES (GL/gl.h HAVE_GL_H)
CHECK_INCLUDE_FILES (SDL2/SDL.h HAVE_SDL_H)
CHECK_INCLUDE_FILES (SDL2/SDL_image.h HAVE_SDL_IMAGE_H)
CHECK_INCLUDE_FILES (vorbis/vorbisfile.h HAVE_VORBISFILE_H)
#CHECK_INCLUDE_FILES (bullet/btBulletCollisionCommon.h HAVE_BT_BULLET_COLLISION:COMMON_H)


add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/openVDrift.cpp ${CMAKE_BINARY_DIR}/messages.cpp)
target_link_libraries(${PROJECT_NAME} ${CLUON_LIBRARIES})
