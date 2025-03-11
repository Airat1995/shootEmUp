#pragma once

#include "SphereCollider.h"
#include "BoxCollider.h"

namespace Engine::Physics::Collider
{
    class CollisionCalculator {
    public:
        static bool BoxToSphereCollision(Collider* boxCollider, Collider* sphereCollider) {

            auto* boxLhs = dynamic_cast<BoxCollider*>(boxCollider);
            auto* sphereRhs = dynamic_cast<SphereCollider*>(sphereCollider);

            return BoxToSphereCollision(boxLhs->GetMin(), boxLhs->GetMax(), sphereRhs->GetPosition(), sphereRhs->GetRadius());
        }

        static bool BoxToSphereCollision(glm::vec3 boxMin, glm::vec3 boxMax, glm::vec3 sphereCenter, double radius) {
            double sqDist = SqDistPointAABB( sphereCenter, boxMin, boxMax);
            return sqDist <= radius * radius;
        }


        static double SqDistPointAABB(glm::vec3 center, glm::vec3 boxMin, glm::vec3 boxMax) {
            float sqDist = 0.0f;
            for (int i = 0; i < 3; i++) {
                float centerPoint = center[i];
                if (centerPoint < boxMin[i])
                    sqDist += (boxMin[i] - centerPoint) * (boxMin[i] - centerPoint);
                if (centerPoint > boxMax[i])
                    sqDist += (centerPoint - boxMax[i]) * (centerPoint - boxMax[i]);
            }
            return sqDist;
        }

        static bool BoxToBoxCollision(Collider* boxCollider, Collider* anotherBox) noexcept {

            auto* boxLhs = dynamic_cast<BoxCollider*>(boxCollider);
            auto* boxRhs = dynamic_cast<BoxCollider*>(anotherBox);

            glm::vec3 lhsMin = boxLhs->GetMin();
            glm::vec3 lhsMax = boxLhs->GetMax();

            glm::vec3 rhsMin = boxRhs->GetMin();
            glm::vec3 rhsMax = boxRhs->GetMax();

            return BoxToBoxCollision(lhsMin, lhsMax, rhsMin, rhsMax);
        }

        static bool BoxToBoxCollision(glm::vec3 lhsMin, glm::vec3 lhsMax, glm::vec3 rhsMin, glm::vec3 rhsMax) {
//            return lhsMin.x <= rhsMax.x && lhsMax.x >= rhsMin.x && lhsMin.y <= rhsMax.y && lhsMax.y >= rhsMax.y &&
//                lhsMin.z <= rhsMax.z && lhsMax.z >= rhsMin.z;

            if( lhsMax.x < rhsMin.x || lhsMin.x > rhsMax.x ) {
                return false;
            }
            if( lhsMax.y < rhsMin.y || lhsMin.y > rhsMax.y ) {
                return false;
            }

            if( lhsMax.z < rhsMin.z || lhsMin.z > rhsMax.z ) {
                return false;
            }

            return true;
        }

        static bool SphereToSphereCollision(Collider* sphereCollider, Collider* anotherSphere) {
            auto* sphereLhs = dynamic_cast<SphereCollider*>(sphereCollider);
            auto* sphereRhs = dynamic_cast<SphereCollider*>(anotherSphere);

            glm::vec3 sphereLhsCenter = sphereLhs->GetPosition();
            glm::vec3 sphereRhsCenter = sphereRhs->GetPosition();
            return SphereToSphereCollision(sphereLhsCenter, sphereLhs->GetRadius(), sphereRhsCenter, sphereRhs->GetRadius());
        }

        static bool SphereToSphereCollision(glm::vec3 sphereLhsCenter, double lhsRadius, glm::vec3 sphereRhsCenter, double rhsRadius) {
            float distance = glm::distance(sphereLhsCenter, sphereRhsCenter);
            return distance <= (lhsRadius + rhsRadius);
        }
    };
}
