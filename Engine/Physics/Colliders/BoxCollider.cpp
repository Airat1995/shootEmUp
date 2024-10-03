#include "BoxCollider.h"
#include "ColliderType.h"
#include "CollisionCalculator.h"

namespace Engine::Physics::Collider
{
    BoxCollider::BoxCollider(Component::Component::Transform &transform, const glm::vec3 min, const glm::vec3 max) :
        Collider(transform, ColliderType::Box), min(min), max(max) {}

    BoxCollider::~BoxCollider() {
        _collisionState = CollisionState::Idle;
        min = glm::vec3(0,0,0);
        max = glm::vec3(0,0,0);
    }

    bool BoxCollider::IsColliding(Collider *anotherCollider) const noexcept {
        bool isColliding = false;
        switch (anotherCollider->GetType()) {
        case ColliderType::Box:
            isColliding = CollisionCalculator::BoxToBoxCollision((Collider *)this, anotherCollider);
            break;
        case ColliderType::Sphere:
            isColliding = CollisionCalculator::BoxToSphereCollision((Collider *)this, anotherCollider);
            break;
        case ColliderType::None:
            isColliding = false;
            break;
        }

        return isColliding;
    }

    bool BoxCollider::IsInsideCell(const glm::vec3 minCell, const glm::vec3 maxCell) const noexcept {
        glm::vec3 collMin = GetMin();
        glm::vec3 collMax = GetMax();

        return CollisionCalculator::BoxToBoxCollision(collMin, collMax, minCell, maxCell);
    }

    glm::vec3 BoxCollider::GetMin() const noexcept {
        return _transform.GetPosition() + min;
    }

    glm::vec3 BoxCollider::GetMax() const noexcept {
        return _transform.GetPosition() + max;
    }
}