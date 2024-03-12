#version 450

layout (location = 0) in vec4 position;

layout (location = 0) out vec4 color;

layout (binding = 0) uniform CameraObject
{
    mat4 view;
    mat4 proj;
} camera;

layout ( push_constant ) uniform ModelObject
{
    mat4 model;
} modelMat;

#pragma main main

void main()
{
    gl_Position = position * modelMat.model;
    color = vec4(position.xyz, 1.0);
}