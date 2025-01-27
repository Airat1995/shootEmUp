#pragma once
#include <__atomic/aliases.h>
#include "ColliderType.h"
#include "CollisionState.h"
#include "Physics/Common/BoundingBox.h"
#include "Component/Component/Transform.h"

namespace Engine::Physics::Collider
{
    class Collider
    {
        using NodeId = std::atomic_uint32_t;
        static constexpr NodeId null = -1;

    public:
        virtual ~Collider() = default;
        explicit Collider(Component::Component::Transform& transform, ColliderType type) : _transform(transform), _type(type) {}

        [[nodiscard]] CollisionState GetState() const noexcept
        {
            return _collisionState;
        }

        [[nodiscard]] ColliderType GetType() const noexcept
        {
            return _type;
        }

        [[nodiscard]] virtual bool IsColliding(Collider* anotherCollider) const noexcept = 0;

        [[nodiscard]] virtual bool IsInsideCell(const glm::vec3 minCell, const glm::vec3 maxCell) const noexcept = 0;

        virtual Engine::Physics::Common::BoundingBox& GetBoundingBox() = 0;

        [[nodiscard]] glm::vec3 GetPosition() const noexcept {
            return _transform.GetPosition();
        }

        void SetState(CollisionState state) {
            _collisionState = state;
        }

    protected:
        CollisionState _collisionState = CollisionState::Idle;
        Component::Component::Transform& _transform;
        ColliderType _type = ColliderType::None;
    };
}