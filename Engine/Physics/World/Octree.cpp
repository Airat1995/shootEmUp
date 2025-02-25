#include "Octree.h"

int Engine::Physics::World::Octree::Octree::MAX_COLLIDERS_PER_NODE = Engine::Physics::World::DEFAULT_MAX_COLLIDERS_PER_NODE;
float Engine::Physics::World::Octree::Octree::MIN_NODE_SIZE = Engine::Physics::World::DEFAULT_MIN_NODE_SIZE;

Engine::Physics::World::Octree::Octree(Engine::Physics::Common::BoundingBox treeBox, float minNodeSize, int maxCollidersCountPerNode) :
    _rootNode(nullptr, treeBox)
{
    Octree::MAX_COLLIDERS_PER_NODE = maxCollidersCountPerNode;
    Octree::MIN_NODE_SIZE = minNodeSize;
    _rootNode.SetNestedIndex(0);
}

void Engine::Physics::World::Octree::Insert(Collider::Collider* collider)
{
    _rootNode.InsertCollider(collider);
}
void Engine::Physics::World::Octree::Remove(Engine::Physics::Collider::Collider* collider)
{
    _rootNode.RemoveCollider(collider);
}

void Engine::Physics::World::Octree::FillCollidedObjects(CollisionInfoContainer& collisionInfoContainer)
{
    return _rootNode.FillCollidedObjects(collisionInfoContainer);
}
void Engine::Physics::World::Octree::Clear()
{
    _rootNode.Clear();
}
