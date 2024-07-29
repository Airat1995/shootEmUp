#pragma once

#include <glm/glm.hpp>
namespace Engine::Camera
{
    struct CameraObject {
        glm::mat4 _model = glm::transpose(glm::mat4(
                1, 0, 0, 1,
                0, 1, 0, 1,
                0, 0, 1, 1,
                0, 0, 0, 1
        ));
        glm::mat4 _view{1};
        glm::mat4 _proj{1};
    };
}