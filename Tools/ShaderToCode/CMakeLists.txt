cmake_minimum_required(VERSION 3.8)

project(ShaderToCode)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE Input_SRC
        "*.h"
        "*.cpp"
)

add_executable(ShaderToCode shaderToCode.cpp
        vertexStruct.h)