cmake_minimum_required (VERSION 3.8)

project(Asset)

file(GLOB_RECURSE Asset_SRC
        "*.h"
        "*.cpp"
        )

include_directories(../)
include_directories(.)
include_directories(../Shared)

# We declare the project as a static library and add all the source code files to it.
add_library(Asset STATIC ${Asset_SRC})

target_link_libraries(Asset Common)