#pragma once
#include <glm/glm.hpp>

class ShadowmapBuffer
{
public:
	glm::mat4 ModelMatrix;
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix;
    glm::vec4 LightPosition;
};
