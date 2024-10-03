#pragma once
#include <vector>


#include "Physics/Colliders/Collider.h"

namespace Engine::Physics::World
{
    class CollisionNode
    {
    public:
        Collider::Collider* first;
        Collider::Collider* second;

        bool AreEqual(Collider::Collider* collidingFirst, Collider::Collider* collidingSecond) const noexcept
        {
            const auto firstAddr = std::addressof(first);
            const auto secondAddr = std::addressof(second);

            const auto firstCollidingAddr = std::addressof(collidingFirst);
            const auto secondCollidingAddr = std::addressof(collidingSecond);

            if(firstAddr != firstCollidingAddr || firstAddr != secondCollidingAddr) {
                return false;
            }

            if(secondAddr != secondCollidingAddr || secondAddr != firstCollidingAddr) {
                return false;
            }

            return true;
        }
    };

    class CollisionGraph
    {
    public:
        void TryAdd(Collider::Collider* first, Collider::Collider* second)
        {
            if(graph.empty())
            {
                AddToCollisionGraph(first, second);
            }
            else
            {
                for (int graphId = 0; graphId < graph.size(); graphId++) {
                    if (graph[graphId].AreEqual(first, second)) {
                        continue;
                    }
                    AddToCollisionGraph(first, second);
                    break;
                }
            }
        }

        void Clear()
        {
            graph.clear();
        }

    protected:
        std::vector<CollisionNode> graph;

    private:
        void AddToCollisionGraph(Collider::Collider* first, Collider::Collider* second)
        {
            graph.push_back({first, second});
        }
    };
}