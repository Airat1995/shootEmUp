#pragma once

#include <vector>
#include "Physics/Colliders/Collider.h"
#include "CollisionInfo.h"

namespace Engine::Physics::World
{
    class CollisionInfoContainer
    {
        using Collider = Engine::Physics::Collider::Collider;

    private:
        std::vector<CollisionInfo> frameCollider;

    public:
        inline bool IsAlreadyContainsCollisionPair(Collider *firstCollider, Collider *secondCollider) {
            for (int infoIndex = 0; infoIndex < frameCollider.size(); ++infoIndex) {
                bool isSame = frameCollider[infoIndex].IsSame(firstCollider, secondCollider);
                if (isSame) {
                    return true;
                }
            }

            return false;
        }

        inline void Insert(Collider *firstCollider, Collider *secondCollider) {
            CollisionInfo collisionInfo{firstCollider, secondCollider};

            frameCollider.emplace_back(collisionInfo);
        }

        void TryInsert(Collider *firstCollider, Collider *secondCollider) {
            if(!IsAlreadyContainsCollisionPair(firstCollider, secondCollider)) {
                Insert(firstCollider, secondCollider);
            }
        }

        void Clear() { frameCollider.empty(); }
    };
}
