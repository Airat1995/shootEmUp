#pragma once

#include "glm/glm.hpp"

namespace Engine::Component::Component
{
    class State {
    public:
        glm::vec3 position;
        glm::vec3 scale;
        glm::quat rotation;

        State& operator=(State copyObj) {
            using std::swap;

            std::swap(position, copyObj.position);
            std::swap(scale, copyObj.scale);
            std::swap(rotation, copyObj.rotation);

            return *this;
        }

        static State Empty() {
            State state {};
            state.position = glm::vec3(0, 0, 0);
            state.scale = glm::vec3(1, 1, 1);
            state.rotation = glm::quat();

            return state;
        }
    };
}