find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB SOURCES "*.cpp")

set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR})
target_link_libraries(${BINARY}_run ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY} ${SDL2TTF_LIBRARY})