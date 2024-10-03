#pragma once

namespace Engine::Physics::Collider
{
    enum class ColliderType : int8_t
    {
        None = -1,
        Box = 0,
        Sphere = 1,
    };
}