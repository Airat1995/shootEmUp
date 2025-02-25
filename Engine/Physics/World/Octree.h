#pragma once

#include <vector>
#include "CollisionInfo.h"
#include "CollisionInfoContainer.h"
#include "Physics/Colliders/Collider.h"
#include "Physics/Common/BoundingBox.h"
#include "Physics/World/Node.h"
#include "glm/vec3.hpp"

namespace Engine::Physics::World
{

    static const int DEFAULT_MAX_COLLIDERS_PER_NODE = 2;
    static const float DEFAULT_MIN_NODE_SIZE = 1.0f;

    class Octree
    {
    public:
        static int MAX_COLLIDERS_PER_NODE;
        static float MIN_NODE_SIZE;

        explicit Octree(Engine::Physics::Common::BoundingBox treeBox, float minNodeSize = DEFAULT_MIN_NODE_SIZE, int maxCollidersCountPerNode = DEFAULT_MAX_COLLIDERS_PER_NODE);

        void Insert(Collider::Collider* collider);

        void Remove(Collider::Collider *collider);

        void FillCollidedObjects(CollisionInfoContainer& collisionInfoContainer);

        void Clear();

    protected:
        Engine::Physics::World::Node _rootNode;
    };
}