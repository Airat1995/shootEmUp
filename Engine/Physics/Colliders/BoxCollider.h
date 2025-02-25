#pragma once
#include "Collider.h"

namespace Engine::Physics::Collider
{
    class BoxCollider : public Collider
    {
    public:
        BoxCollider(Component::Component::Transform& transform, const glm::vec3 min, const glm::vec3 max);

        ~BoxCollider() override;

        [[nodiscard]] bool IsColliding(Collider* anotherCollider) const noexcept override;

        [[nodiscard]] bool IsInsideCell(const glm::vec3 minCell, const glm::vec3 maxCell) const noexcept override;

        virtual Engine::Physics::Common::BoundingBox& GetBoundingBox() override;

        [[nodiscard]] inline glm::vec3 GetMin() const noexcept;

        [[nodiscard]] inline glm::vec3 GetMax() const noexcept;

    protected:
        glm::vec3 sizeMin;
        glm::vec3 sizeMax;
        Engine::Physics::Common::BoundingBox box;
    };
}