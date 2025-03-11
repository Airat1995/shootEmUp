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

    public:
        std::vector<CollisionInfo> _previousFrameCollider;
        std::vector<CollisionInfo> _currentFrameCollider;

    public:

        inline void StartColliding() {
            _previousFrameCollider.clear();
            _previousFrameCollider = _currentFrameCollider;
            _currentFrameCollider.clear();
        }

        void TryInsert(Collider *firstCollider, Collider *secondCollider) {

            uint32_t firstColliderId = firstCollider->GetId();
            uint32_t secondColliderId = secondCollider->GetId();
            for (int infoIndex = 0; infoIndex < _currentFrameCollider.size(); ++infoIndex) {
                bool isSame = _currentFrameCollider[infoIndex].IsSame(firstColliderId, secondColliderId);
                if (isSame) {
                    return;
                }
            }

            CollisionInfo collisionInfo{firstCollider, secondCollider};

            _currentFrameCollider.emplace_back(collisionInfo);
        }

        void NotifyAllColliders() {
            for (int currentFrameCollIndex = 0; currentFrameCollIndex < _currentFrameCollider.size(); ++currentFrameCollIndex) {
                CollisionInfo& collisionInfo = _currentFrameCollider[currentFrameCollIndex];
                uint32_t firstCollisionInfoFCId = collisionInfo.FirstCollider->GetId();
                uint32_t firstCollisionInfoSCId = collisionInfo.SecondCollider->GetId();
                bool foundAny = false;
                for (int previousFrameCollIndex = 0; previousFrameCollIndex < _previousFrameCollider.size(); ++previousFrameCollIndex) {
                    CollisionInfo& prevFrameInfo = _previousFrameCollider[previousFrameCollIndex];
                    uint32_t secondCollisionInfoFCId = prevFrameInfo.FirstCollider->GetId();
                    uint32_t secondCollisionInfoSCId = prevFrameInfo.SecondCollider->GetId();
                    if(CollisionInfo::IsSame(firstCollisionInfoFCId, firstCollisionInfoSCId, secondCollisionInfoFCId, secondCollisionInfoSCId)) {
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
