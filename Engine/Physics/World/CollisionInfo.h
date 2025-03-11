#pragma once
#include "Physics/Colliders/Collider.h"

namespace Engine::Physics::World
{
    class CollisionInfo
    {
        using Collider = Engine::Physics::Collider::Collider;

    public:
        Collider *FirstCollider;
        uint32_t _firstIdCollider;
        Collider *SecondCollider;
        uint32_t _secondIdCollider;

        CollisionInfo(Collider *firstCollider, Collider *secondCollider) :
            FirstCollider(firstCollider), _firstIdCollider(firstCollider->GetId()), SecondCollider(secondCollider), _secondIdCollider(secondCollider->GetId()), _usageCount(0) {}

        inline bool IsSame(uint32_t anotherFCId, uint32_t anotherSCId) {
            
            if(_firstIdCollider != anotherFCId)
            {
                if(_firstIdCollider != anotherSCId)
                {
                    return false;
                }
            }

            if(_secondIdCollider != anotherFCId)
            {
                if(_secondIdCollider != anotherSCId)
                {
                    return false;
                }
            }

            return true;
        }

        static inline bool IsSame(uint32_t firstIdCollider, uint32_t secondIdCollider, uint32_t anotherFCId, uint32_t anotherSCId) {

            if(firstIdCollider != anotherFCId)
            {
                if(firstIdCollider != anotherSCId)
                {
                    return false;
                }
            }
            
            if(secondIdCollider != anotherFCId)
            {
                if(secondIdCollider != anotherSCId)
                {
                    return false;
                }
            }

            return true;
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
