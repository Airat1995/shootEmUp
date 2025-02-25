#include "World.h"


Engine::Physics::World::World::World(glm::vec3 position, float halfSize, float minNodeSize,
                                     int maxCollidersCountPerNode) : _tree({position, halfSize}, minNodeSize, maxCollidersCountPerNode)
{
    _frameColliders = {};
}

void Engine::Physics::World::World::InsertCollider(Engine::Physics::Collider::Collider* collider)
{
    _treeColliders.emplace_back(collider);
    _tree.Insert(collider);
}
void Engine::Physics::World::World::RemoveCollider(Engine::Physics::Collider::Collider* collider)
{
    if(std::find(_treeColliders.begin(), _treeColliders.end(), collider) == _treeColliders.end())
        return;

    _treeColliders.erase(std::remove(_treeColliders.begin(), _treeColliders.end(), collider), _treeColliders.end());
    _tree.Remove(collider);
}
void Engine::Physics::World::World::PhysicalUpdate(double deltaTime)
{
    _tree.Clear();
    for (int colliderIndex = 0; colliderIndex < _treeColliders.size(); ++colliderIndex) {
        _tree.Insert(_treeColliders[colliderIndex]);
    }

    _frameColliders.StartColliding();
    _tree.FillCollidedObjects(_frameColliders);
    _frameColliders.NotifyAllColliders();
}