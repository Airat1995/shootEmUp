//we will be using glsl version 4.5 syntax
#version 450

layout (location = 0) in vec4 position;

layout (binding = 0) uniform CameraObject
{
	mat4 model;
	mat4 view;
	mat4 proj;
} camera;

void main()
{
	//output the position of each vertex
	gl_Position = camera.proj * camera.view * camera.model * position;
}
