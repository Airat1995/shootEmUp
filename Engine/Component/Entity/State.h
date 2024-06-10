#pragma once

#include "glm/glm.hpp"

class State {
public:
    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;

    State& operator=(State& copyObj) {
        std::swap(position, copyObj.position);
        std::swap(scale, copyObj.scale);
        std::swap(rotation, copyObj.rotation);

        return *this;
    }
};