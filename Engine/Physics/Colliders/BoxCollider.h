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

        [[nodiscard]] glm::vec3 GetMin() const noexcept;

        [[nodiscard]] glm::vec3 GetMax() const noexcept;

    protected:
        glm::vec3 min;
        glm::vec3 max;
    };
}