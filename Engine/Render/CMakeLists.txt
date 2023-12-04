cmake_minimum_required (VERSION 3.8)

project(Render)

set (CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE Render_SRC
        "*.h"
        "*.cpp"
        )

include_directories(../)
include_directories(.)
include_directories(../Shared)

# We declare the project as a static library and add all the source code files to it.
add_library(Render STATIC ${Render_SRC})

target_link_libraries(Render Asset Camera)