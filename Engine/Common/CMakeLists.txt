cmake_minimum_required(VERSION 3.8)

project(Common)

file(GLOB_RECURSE Common_SRC
        "*.h"
        "*.cpp"
)

include_directories(../)

# We declare the project as a static library and add all the source code files to it.
add_library(Common STATIC ${Common_SRC} System/UpdatableSystem.h)