#pragma once

namespace Engine::Physics::Collider
{
    enum class CollisionState
    {
        Idle,
        Enter,
        Stay,
        Exit
    };
}