#pragma once
#include <glm/detail/type_quat.hpp>


#include "IComponent.h"
#include "State.h"

namespace Engine::Component::Component
{
    class Transform final : IComponent {
    public:
        [[nodiscard]] glm::vec3 GetPosition() const noexcept;
        [[nodiscard]] glm::vec3 GetScale() const noexcept;
        [[nodiscard]] glm::quat GetRotation() const noexcept;

        [[nodiscard]] glm::vec3 GetInterpolatedPosition(double alpha) const noexcept;
        [[nodiscard]] glm::vec3 GetInterpolatedScale(double alpha) const noexcept;
        [[nodiscard]] glm::quat GetInterpolatedRotation(double alpha) const noexcept;

        void SetPosition(const glm::vec3 &position) noexcept;
        void SetScale(const glm::vec3 &scale) noexcept;
        void SetRotation(const glm::quat &rotation) noexcept;

        void AddPosition(const glm::vec3 &position) noexcept;
        void AddScale(const glm::vec3 &scale) noexcept;
        void AddRotation(const glm::quat &rotation) noexcept;

    private:
        State _previousState = State::Empty();
        State _currentState = State::Empty();

    };
}