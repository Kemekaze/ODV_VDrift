cmake_minimum_required(VERSION 3.5)
project(vDODV-test-input)

set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Isrc -I/usr/include/SDL2")



find_package(libcluon REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(
 SYSTEM ${CMAKE_BINARY_DIR}
 ${CLUON_INCLUDE_DIRS}
 /app/lib
 /app/build
)

#add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/messages.cpp
#                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#                   COMMAND cluon-msc --cpp-sources --cpp-add-include-file=messages.hpp --out=${CMAKE_BINARY_DIR}/messages.cpp ${CMAKE_BINARY_DIR}/config/messages.odvd
#                   COMMAND cluon-msc --cpp-headers --out=${CMAKE_BINARY_DIR}/messages.hpp ${CMAKE_BINARY_DIR}/config/messages.odvd
#                   DEPENDS ${CMAKE_BINARY_DIR}/config/messages.odvd)
#
add_executable(${PROJECT_NAME}
/app/build/messages.cpp
${CMAKE_CURRENT_SOURCE_DIR}/main.cpp

)

target_link_libraries(${PROJECT_NAME} ${CLUON_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
