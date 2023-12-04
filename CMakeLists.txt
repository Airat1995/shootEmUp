cmake_minimum_required(VERSION 3.25)
project(shootEmUp)

set(CMAKE_CXX_STANDARD 17)

add_executable(shootEmUp main.cpp)

if (DEBUG_CODE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DENGINE_DEBUG")
endif (DEBUG_CODE)

find_package(SDL2 REQUIRED)
include_directories(shootEmUp ${SDL2_INCLUDE_DIRS})

find_package(Vulkan REQUIRED)
include_directories(shootEmUp ${Vulkan_INCLUDE_DIR})

target_link_libraries(shootEmUp ${SDL2_LIBRARIES})
target_link_libraries(shootEmUp Vulkan::Vulkan)

include_directories(shootEmUp include Engine)

add_subdirectory(Engine/Window)
add_subdirectory(Engine/Render)
add_subdirectory(Engine/Asset)
add_subdirectory(Engine/Common)
add_subdirectory(Engine/Camera)
add_subdirectory(Engine/Input)

target_link_libraries(shootEmUp Render Window Asset Common Camera Input)