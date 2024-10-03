cmake_minimum_required(VERSION 3.25)

project(Physics)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE Physics_SRC
        "*.h"
        "*.cpp"
)

include_directories(../)
include_directories(.)


add_library(Physics STATIC ${Physics_SRC})

set_target_properties(Physics PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(Physics Component)