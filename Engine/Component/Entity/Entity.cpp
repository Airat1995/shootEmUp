
#include "Entity.h"

Entity::~Entity() {
    for (int index = components.size() - 1; index >= 0; --index) {
        components.at(index).Destroy();
    }
    components.clear();
}

void Entity::AddComponent(IComponent& component) {
    components.push_back(std::move(component));
}

void Entity::RemoveComponent(long long id) {
    for (int i = components.size() - 1; i >= 0; --i) {
        if (components.at(i).GetId() != id) continue;
        components.erase(components.begin() + i);
        break;
    }
}

void Entity::Update(double deltaTime) {
    for (int i = 0; i < components.size(); ++i) {
        auto &component = components.at(i);
        if (component.GetEnabled())
            component.Update(deltaTime);
    }
}

void Entity::FixedUpdate(double deltaTime) {
    for (int i = 0; i < components.size(); ++i) {
        auto &component = components.at(i);
        if (component.GetEnabled())
            component.FixedUpdate(deltaTime);
    }
}

void Entity::PrerenderUpdate(double alpha) {
}
