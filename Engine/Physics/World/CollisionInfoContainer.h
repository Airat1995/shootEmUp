#pragma once

#include <vector>
#include "Physics/Colliders/Collider.h"
#include "Physics/Colliders/CollisionState.h"
#include "CollisionInfo.h"

namespace Engine::Physics::World
{
    class CollisionInfoContainer
    {
        using Collider = Engine::Physics::Collider::Collider;
        using CollisionState = Engine::Physics::Collider::CollisionState;

    private:
        std::vector<CollisionInfo> _previousFrameCollider;
        std::vector<CollisionInfo> _currentFrameCollider;

    public:

        inline void StartColliding() {
            _previousFrameCollider.clear();
            _previousFrameCollider = _currentFrameCollider;
            _currentFrameCollider.clear();
        }

        inline bool IsAlreadyContainsCollisionPair(Collider *firstCollider, Collider *secondCollider) {
            for (int infoIndex = 0; infoIndex < _currentFrameCollider.size(); ++infoIndex) {
                bool isSame = _currentFrameCollider[infoIndex].IsSame(firstCollider, secondCollider);
                if (isSame) {
                    return true;
                }
            }

            return false;
        }

        inline void Insert(Collider *firstCollider, Collider *secondCollider) {
            CollisionInfo collisionInfo{firstCollider, secondCollider};

            _currentFrameCollider.emplace_back(collisionInfo);
        }

        void TryInsert(Collider *firstCollider, Collider *secondCollider) {
            if(!IsAlreadyContainsCollisionPair(firstCollider, secondCollider)) {
                Insert(firstCollider, secondCollider);
            }
        }

        void NotifyAllColliders() {
            for (int currentFrameCollIndex = 0; currentFrameCollIndex < _currentFrameCollider.size(); ++currentFrameCollIndex) {
                CollisionInfo& collisionInfo = _currentFrameCollider[currentFrameCollIndex];
                bool foundAny = false;
                for (int previousFrameCollIndex = 0; previousFrameCollIndex < _previousFrameCollider.size(); ++previousFrameCollIndex) {
                    CollisionInfo& prevFrameInfo = _previousFrameCollider[previousFrameCollIndex];
                    if(prevFrameInfo.IsSame(collisionInfo)) {
                        collisionInfo.FirstCollider->SetState(CollisionState::Stay, collisionInfo.SecondCollider);
                        collisionInfo.SecondCollider->SetState(CollisionState::Stay, collisionInfo.FirstCollider);
                        prevFrameInfo.IncreaseUsageCount();
                        foundAny = true;
                        break;
                    }
                }
                if(!foundAny) {
                    collisionInfo.FirstCollider->SetState(CollisionState::Enter, collisionInfo.SecondCollider);
                    collisionInfo.SecondCollider->SetState(CollisionState::Enter, collisionInfo.FirstCollider);
                }
            }

            for (int previousFrameCollIndex = 0; previousFrameCollIndex < _previousFrameCollider.size(); ++previousFrameCollIndex) {
                CollisionInfo &prevFrameInfo = _previousFrameCollider[previousFrameCollIndex];
                if(prevFrameInfo.GetUsageCount() == 0) {
                    prevFrameInfo.FirstCollider->SetState(CollisionState::Exit, prevFrameInfo.SecondCollider);
                    prevFrameInfo.SecondCollider->SetState(CollisionState::Exit, prevFrameInfo.FirstCollider);
                }
                prevFrameInfo.ClearUsageCount();
            }
        }
    };
}
