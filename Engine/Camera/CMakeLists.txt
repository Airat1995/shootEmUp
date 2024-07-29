cmake_minimum_required(VERSION 3.8)

project(Camera)

file(GLOB_RECURSE Camera_SRC
        "*.h"
        "*.cpp"
)

include_directories(../)
include_directories(.)

# We declare the project as a static library and add all the source code files to it.
add_library(Camera STATIC ${Camera_SRC})
set_target_properties(Camera PROPERTIES LINKER_LANGUAGE CXX)