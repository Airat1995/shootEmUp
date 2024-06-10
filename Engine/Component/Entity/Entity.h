
#pragma once

#include <vector>
#include "Component/Component/IComponent.h"

class Entity {
public:
    virtual ~Entity();

    virtual void AddComponent(IComponent& component);

    virtual void RemoveComponent(long long id);

    virtual void Update(double deltaTime);

    virtual void FixedUpdate(double deltaTime);

    virtual void PrerenderUpdate(double alpha);

protected:

    std::vector<IComponent> components;
};
