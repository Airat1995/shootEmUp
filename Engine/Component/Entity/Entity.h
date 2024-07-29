
#pragma once

#include <vector>
#include "Component/Component/IComponent.h"

namespace Engine::Component::Entity
{
    using namespace Engine::Component::Component;

    class Entity
    {
    public:
        virtual ~Entity();

        virtual void AddComponent(Component::IComponent &component);

        virtual void RemoveComponent(long long id);

        virtual void Update(double deltaTime);

        virtual void FixedUpdate(double deltaTime);

        virtual void PrerenderUpdate(double alpha);

    protected:
        std::vector<Component::IComponent> components;
    };
}