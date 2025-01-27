#include "World.h"


Engine::Physics::World::World::World(glm::vec3 position, float halfSize, float minNodeSize,
                                     int maxCollidersCountPerNode) : _tree({position, halfSize}, minNodeSize, maxCollidersCountPerNode)
{
}

void Engine::Physics::World::World::InsertCollider(Engine::Physics::Collider::Collider *collider)
{
    _treeColliders.emplace_back(collider);
    _tree.Insert(collider);
}
