#include "SphereCollider.h"
#include "ColliderType.h"
#include "CollisionCalculator.h"

namespace Engine::Physics::Collider
{
    SphereCollider::SphereCollider(Component::Component::Transform &transform,
                                                              double radius) :
        Collider(transform, ColliderType::Sphere), radius(radius), box({transform.GetPosition(), (float)radius}) {}

    SphereCollider::~SphereCollider() {
        radius = 0;
        _collisionState = CollisionState::Idle;
    }

    bool SphereCollider::IsColliding(Engine::Physics::Collider::Collider *anotherCollider) const noexcept {
        bool isColliding = false;
        switch (anotherCollider->GetType()) {
        case ColliderType::Box:
            isColliding = CollisionCalculator::BoxToSphereCollision(anotherCollider, (Collider *)this);
            break;
        case ColliderType::Sphere:
            isColliding = CollisionCalculator::SphereToSphereCollision((Collider *)this, anotherCollider);
            break;
        case ColliderType::None:
            isColliding = false;
            break;
        }
        return isColliding;
    }

    bool SphereCollider::IsInsideCell(const glm::vec3 minCell, const glm::vec3 maxCell) const noexcept {
        return CollisionCalculator::BoxToSphereCollision(minCell, maxCell, GetPosition(), GetRadius());
    }

    double SphereCollider::GetRadius() const noexcept {
        return radius;
    }
    Engine::Physics::Common::BoundingBox &SphereCollider::GetBoundingBox()
    {
        box.SetPosition(_transform.GetPosition());
        return box;
    }
}