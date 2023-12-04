cmake_minimum_required (VERSION 3.8)

project(Input)

set (CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE Input_SRC
        "*.h"
        "*.cpp"
        )

include_directories(../)
include_directories(.)
include_directories(../Shared)

# We declare the project as a static library and add all the source code files to it.
add_library(Input STATIC ${Input_SRC} InputMap.cpp InputMap.h KeyCode.h InputState.h
        InputContext.h
        InputContext.cpp)