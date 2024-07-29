//
// Created by Айрат Насыров on 29.07.2024.
//

#include "Transform.h"
glm::vec3 Engine::Component::Component::Transform::GetPosition() const noexcept
{
    return _currentState.position;
}

glm::vec3 Engine::Component::Component::Transform::GetScale() const noexcept
{
    return _currentState.scale;
}

glm::quat Engine::Component::Component::Transform::GetRotation() const noexcept
{
    return _currentState.rotation;
}

glm::vec3 Engine::Component::Component::Transform::GetInterpolatedPosition(const double alpha) const noexcept
{
    glm::vec3 interpolatedPosition = _currentState.position * static_cast<float>(alpha) + _previousState.position * static_cast<float>(1 - alpha);
    return interpolatedPosition;
}

glm::vec3 Engine::Component::Component::Transform::GetInterpolatedScale(const double alpha) const noexcept
{
    glm::vec3 interpolatedScale = _currentState.scale * static_cast<float>(alpha) + _previousState.scale * static_cast<float>(1 - alpha);
    return interpolatedScale;
}

glm::quat Engine::Component::Component::Transform::GetInterpolatedRotation(const double alpha) const noexcept
{
    glm::quat interpolatedRotation = _currentState.rotation * static_cast<float>(alpha) + _previousState.rotation * static_cast<float>(1 - alpha);
    return interpolatedRotation;
}

void Engine::Component::Component::Transform::SetPosition(const glm::vec3 &position) noexcept
{
    _previousState.position = _currentState.position;
    _currentState.position = position;
}

void Engine::Component::Component::Transform::SetScale(const glm::vec3 &scale) noexcept
{
    _previousState.scale = _currentState.scale;
    _currentState.scale = scale;
}

void Engine::Component::Component::Transform::SetRotation(const glm::quat &rotation) noexcept
{
    _previousState.rotation = _currentState.rotation;
    _currentState.rotation = rotation;
}

void Engine::Component::Component::Transform::AddPosition(const glm::vec3 &position) noexcept
{
    _previousState.position = _currentState.position;
    _currentState.position += position;
}

void Engine::Component::Component::Transform::AddScale(const glm::vec3 &scale) noexcept
{
    _previousState.scale = _currentState.scale;
    _currentState.scale += scale;
}

void Engine::Component::Component::Transform::AddRotation(const glm::quat &rotation) noexcept
{
    _previousState.rotation = _currentState.rotation;
    _currentState.rotation += rotation;
}