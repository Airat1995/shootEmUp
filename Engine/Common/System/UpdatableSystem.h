#pragma once

namespace Engine::Common::System
{
    class UpdatableSystem {
    public:
        virtual ~UpdatableSystem() = default;

        virtual void Update(double deltaTime) = 0;
    };
}