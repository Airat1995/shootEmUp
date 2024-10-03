#pragma once
#include <vector>

#include "../Colliders/Collider.h"
#include "CollisionGraph.h"

namespace Engine::Physics::World
{
    class Cell
    {
    public:
        Cell(glm::vec3 min, glm::vec3 max);

        bool TryToAdd(Collider::Collider* collider) noexcept;

        [[nodiscard]] glm::vec3 GetMin() const noexcept;
        [[nodiscard]] glm::vec3 GetMax() const noexcept;


        void FillGraph(Engine::Physics::World::CollisionGraph& graph);

        void Clear();

    protected:
        glm::vec3 _min;
        glm::vec3 _max;

        std::vector<Collider::Collider*> _colliders;

    private:
        bool _active;
    };
}