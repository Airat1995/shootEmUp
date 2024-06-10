cmake_minimum_required(VERSION 3.8)
project(Component)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE Component_SRC
        "*.h"
        "*.cpp"
)

include_directories(../)
include_directories(.)

add_library(Component STATIC ${Component_SRC})

set_target_properties(Component PROPERTIES LINKER_LANGUAGE CXX)