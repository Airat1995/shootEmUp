cmake_minimum_required (VERSION 3.8)

project(Window)

set(SOURCE_FILES IWindow.cpp SDLWindow.cpp)
set(HEADER_FILES IWindow.h SDLWindow.cpp)

find_package(SDL2 REQUIRED)
include_directories(Window ${SDL2_INCLUDE_DIRS})

include_directories(../)

# We declare the project as a static library and add all the source code files to it.
add_library(Window STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(Window Render)