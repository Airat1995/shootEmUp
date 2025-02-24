#pragma once

namespace Engine::Common::System
{
    class PhysicUpdatableSystem {
    public:
        virtual ~PhysicUpdatableSystem() = default;

        virtual void PhysicalUpdate(double deltaTime) = 0;
    };
}
