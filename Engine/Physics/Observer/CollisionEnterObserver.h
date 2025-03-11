#pragma once

#include "Common/Observer/Observer.h"


namespace Engine::Physics::Collider
{
    class Collider;
}

namespace Engine::Physics::Observer
{
    using namespace Engine::Physics;

    class CollisionEnterObserver : public Engine::Common::Observer::IObserver<Engine::Physics::Collider::Collider>
    {
    public:
    };
}