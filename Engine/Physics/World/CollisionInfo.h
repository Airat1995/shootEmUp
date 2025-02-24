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
            FirstCollider(firstCollider), SecondCollider(secondCollider) {}

        inline bool IsSame(Collider *anotherFirst, Collider *anotherSecond) {
            int containerFCId = FirstCollider->GetId();
            int containerSCId = SecondCollider->GetId();

            int anotherFCId = anotherFirst->GetId();
            int anotherSCId = anotherSecond->GetId();

            bool containedFirst = containerFCId == anotherFCId || containerFCId == anotherSCId;
            bool containedSecond = containerSCId == anotherFCId || containerSCId == anotherSCId;

            return containedFirst && containedSecond;
        }
    };
}
