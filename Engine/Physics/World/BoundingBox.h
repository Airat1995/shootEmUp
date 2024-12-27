#pragma once

#include "glm/vec3.hpp"
namespace Engine::Physics::World
{
    class BoundingBox
    {
    public:
        BoundingBox(glm::vec3 min, glm::vec3 max) : _min(min), _max(max), _center(min + glm::vec3{(max.x - min.x)/2, (max.y - min.y)/2, (max.z - min.z)/2})
        {
        }

        BoundingBox(glm::vec3 center, float size) : _min({center.x - size, center.y - size, center.z - size}), _max({center.x + size, center.y + size, center.z + size}), _center(center)
        {
        }

        [[nodiscard]] glm::vec3 GetMin() const noexcept
        {
            return _min;
        }

        [[nodiscard]] glm::vec3 GetMax() const noexcept
        {
            return _max;
        }

        [[nodiscard]] glm::vec3 GetCenter() const noexcept
        {
            return _center;
        }

        [[nodiscard]] float GetWidth() const noexcept
        {
            return _max.x - _min.x;
        }

        BoundingBox Extend(BoundingBox& extend)
        {
            glm::vec3 extendedMin {};
            glm::vec3 extendedMax {};
            extendedMin.x = std::min(_min.x, extend._min.x);
            extendedMin.y = std::min(_min.y, extend._min.y);
            extendedMax.x = std::max(_max.x, extend._max.x);
            extendedMax.y = std::max(_max.y, extend._max.y);
            BoundingBox extendedBox {extendedMin, extendedMax};
            return extendedBox;
        }

        bool Contains(glm::vec3 point) const noexcept
        {
            return _min.x >= point.x && _max.x <= point.x &&
                   _min.y >= point.y && _max.y <= point.y &&
                   _min.z >= point.z && _max.z <= point.z;
        }

    protected:
        glm::vec3 _min;
        glm::vec3 _max;
        glm::vec3 _center;
    };
}
