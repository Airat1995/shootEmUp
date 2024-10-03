#pragma once
#include <__atomic/aliases.h>
#include <vector>
#include <thread>

#include "Cell.h"
#include "CollisionGraph.h"
#include "Physics/Colliders/Collider.h"

namespace Engine::Physics::World
{
    static constexpr float inf = std::numeric_limits<float>::infinity();
    using NodeId = std::atomic_uint32_t;
    static constexpr NodeId null = -1;

    class World
    {
    public:
        World(glm::vec3 min, glm::vec3 max, glm::vec3 cellSize);
        ~World();

        void Update(double deltaTime);

        void AddCollider(Collider::Collider* collider);

        void ClearGraph();

    protected:

        glm::vec3 cellSize = {1, 1, 1};
        glm::vec3 min {-inf, -inf, -inf};
        glm::vec3 max {inf, inf, inf};
        uint _threadsCount;
        uint _countPerThreads;
        CollisionGraph _collisionGraph;
        std::vector<Cell> _cells;
        std::vector<Cell*> _activeCells;
        std::vector<Collider::Collider*> _nonColliding;
        std::vector<Collider::Collider*> _colliding;
        std::vector<Collider::Collider*> _colliders;

    private:
        std::vector<std::thread> _cellsAddingThreads;
    };
}
