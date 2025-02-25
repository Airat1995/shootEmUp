#pragma once
#include "Physics/Colliders/Collider.h"

namespace Engine::Physics::World
{
    class CollisionInfo
    {
        using Collider = Engine::Physics::Collider::Collider;

    public:
        Collider *FirstCollider;
        Collider *SecondCollider;

        CollisionInfo(Collider *firstCollider, Collider *secondCollider) :
            FirstCollider(firstCollider), SecondCollider(secondCollider), _usageCount(0) {}

        inline bool IsSame(Collider *anotherFirst, Collider *anotherSecond) {
            int containerFCId = FirstCollider->GetId();
            int containerSCId = SecondCollider->GetId();

            int anotherFCId = anotherFirst->GetId();
            int anotherSCId = anotherSecond->GetId();

            if(anotherFCId == anotherSCId) {
                printf("SAME ADDED!");
            }

            bool containedFirst = containerFCId == anotherFCId || containerFCId == anotherSCId;
            bool containedSecond = containerSCId == anotherFCId || containerSCId == anotherSCId;

            return containedFirst && containedSecond;
        }
        inline bool IsSame(CollisionInfo info) {
            return IsSame(info.FirstCollider, info.SecondCollider);
        }

        inline void IncreaseUsageCount() noexcept {
            _usageCount++;
        }

        inline void ClearUsageCount() noexcept {
            _usageCount = 0;
        }

        inline uint32_t GetUsageCount() const noexcept {
            return _usageCount;
        }


    protected:
        uint32_t _usageCount;
    };
}
