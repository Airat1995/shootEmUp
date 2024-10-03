#include "Cell.h"

Engine::Physics::World::Cell::Cell(glm::vec3 min, glm::vec3 max) : _min(min), _max(max)
{
}

bool Engine::Physics::World::Cell::TryToAdd(Collider::Collider *collider) noexcept {
    bool insideCell = collider->IsInsideCell(_min, _max);
    if(insideCell)
    {
        _colliders.push_back(collider);
        _active = true;
    }
    
    return insideCell;
}

glm::vec3 Engine::Physics::World::Cell::GetMin() const noexcept
{
    return _min;
}

glm::vec3 Engine::Physics::World::Cell::GetMax() const noexcept
{
    return _max;
}

void Engine::Physics::World::Cell::FillGraph(Engine::Physics::World::CollisionGraph &graph)
{
    if(!_active)
    {
        return;
    }
    for (int lhsColliderIndex = 0; lhsColliderIndex < _colliders.size() - 1; ++lhsColliderIndex)
    {
        for (int rhsColliderIndex = lhsColliderIndex + 1; rhsColliderIndex < _colliders.size(); ++rhsColliderIndex)
        {
            Collider::Collider* lhsCollider = _colliders[lhsColliderIndex];
            Collider::Collider* rhsCollider = _colliders[rhsColliderIndex];

            bool isColliding = lhsCollider->IsColliding(rhsCollider);
            if(isColliding)
            {
                graph.TryAdd(lhsCollider, rhsCollider);
            }
        }
    }
}

void Engine::Physics::World::Cell::Clear()
{
    _active = false;
    _colliders.clear();
}
