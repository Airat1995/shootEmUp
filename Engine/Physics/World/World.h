#pragma once

#include <vector>
#include "Octree.h"
#include "CollisionInfoContainer.h"
#include "Common/System/PhysicUpdatableSystem.h"

namespace Engine::Physics::World
{
    class World : Engine::Common::System::PhysicUpdatableSystem
    {
    public:
        World(glm::vec3 position, float halfSize, float minNodeSize = DEFAULT_MIN_NODE_SIZE, int maxCollidersCountPerNode = DEFAULT_MAX_COLLIDERS_PER_NODE);

        void InsertCollider(Engine::Physics::Collider::Collider* collider);

        void RemoveCollider(Engine::Physics::Collider::Collider *collider);

        void PhysicalUpdate(double deltaTime) override;

    private:
        Octree _tree;
        CollisionInfoContainer _frameColliders;
        std::vector<Engine::Physics::Collider::Collider*> _treeColliders;
    };
}