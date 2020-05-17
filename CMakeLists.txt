cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(pixel_poker)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
 
add_executable(poker_game ${SOURCES})

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR})

target_link_libraries(poker_game ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY})