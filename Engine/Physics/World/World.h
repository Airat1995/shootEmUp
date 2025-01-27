#pragma once

#include <vector>
#include "Octree.h"

namespace Engine::Physics::World
{
    class World
    {
    public:
        World(glm::vec3 position, float halfSize, float minNodeSize = DEFAULT_MIN_NODE_SIZE, int maxCollidersCountPerNode = DEFAULT_MAX_COLLIDERS_PER_NODE);

        void InsertCollider(Engine::Physics::Collider::Collider* collider);

    private:
        Octree _tree;
        std::vector<Engine::Physics::Collider::Collider*> _treeColliders;
    };
}