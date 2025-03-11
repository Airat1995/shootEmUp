#pragma once

#include "glm/vec3.hpp"
namespace Engine::Physics::Common
{
    class BoundingBox
    {
    public:
        BoundingBox(glm::vec3 position, float halfSize);

        BoundingBox(glm::vec3 min, glm::vec3 max);

        [[nodiscard]] inline glm::vec3 GetPosition() const noexcept
        {
            return _pos;
        }

        inline void SetPosition(glm::vec3 newPosition) noexcept
        {
            _pos = newPosition;
        }

        [[nodiscard]] inline float GetSize() const noexcept
        {
            return _halfSize;
        }

        [[nodiscard]] bool IsOverlap(BoundingBox& box) const noexcept;

    private:

        glm::vec3 _pos{};
        float _halfSize;
    };
}