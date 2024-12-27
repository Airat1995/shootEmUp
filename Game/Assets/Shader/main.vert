#version 450

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;

layout (location = 0) out vec4 color;

layout (std140, binding = 1) uniform CameraObject
{
    mat4 model;
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
    vec4 objectWorlPosition = modelMat.model * position;
    gl_Position = camera.proj * camera.view * objectWorlPosition;
    color = vec4(normal, 1.0);
}