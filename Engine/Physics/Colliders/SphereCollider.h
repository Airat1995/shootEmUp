#pragma once
#include "Collider.h"

namespace Engine::Physics::Collider
{
    class SphereCollider : public Collider
    {
    public:
        SphereCollider(Component::Component::Transform& transform, double radius);

        ~SphereCollider() override;

        [[nodiscard]] bool IsColliding(Collider* anotherCollider) const noexcept override;

        [[nodiscard]] bool IsInsideCell(const glm::vec3 minCell, const glm::vec3 maxCell) const noexcept override;

        virtual Engine::Physics::Common::BoundingBox& GetBoundingBox() override;

        [[nodiscard]] double GetRadius() const noexcept;

    protected:
        double radius;
        Engine::Physics::Common::BoundingBox box;
    };
}
