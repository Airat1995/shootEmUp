#pragma once
#include <utility>
#include <__atomic/aliases.h>
#include "ColliderType.h"
#include "CollisionState.h"
#include "Physics/Common/BoundingBox.h"
#include "Component/Component/Transform.h"

namespace Engine::Physics::Collider
{
    using NodeId = std::atomic_uint32_t;
    static NodeId base = -1;
    class Collider
    {
    public:

        virtual ~Collider() = default;

        Collider(Component::Component::Transform& transform, ColliderType type) : _transform(transform), _type(type)
        {
            _id = (base.fetch_add(1, std::memory_order_relaxed) + 1);
        }

        [[nodiscard]] CollisionState GetState() const noexcept
        {
            return _collisionState;
        }

        [[nodiscard]] ColliderType GetType() const noexcept
        {
            return _type;
        }

        [[nodiscard]] virtual bool IsColliding(Collider* anotherCollider) const = 0;

        [[nodiscard]] virtual bool IsInsideCell(const glm::vec3 minCell, const glm::vec3 maxCell) const = 0;

        virtual Engine::Physics::Common::BoundingBox& GetBoundingBox() = 0;

        [[nodiscard]] glm::vec3 GetPosition() const
        {
            return _transform.GetPosition();
        }

        void SetState(CollisionState state, Collider* collider) {
            _collisionState = state;
        }

        int64_t GetId() const noexcept {
            return _id;
        }

        void SetColliding(Collider *collidingWith) {
            switch (_collisionState) {
            case CollisionState::Idle:
                break;
            case CollisionState::Stay:
                break;
            }
        }

    protected:
        CollisionState _collisionState = CollisionState::Idle;
        Component::Component::Transform& _transform;
        ColliderType _type = ColliderType::None;
    private:
        uint32_t _id;
    };
}