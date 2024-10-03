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
    glm::quat interpolatedRotation;
    const float lx = _previousState.rotation.x;
    const float ly = _previousState.rotation.y;
    const float lz = _previousState.rotation.z;
    const float lw = _previousState.rotation.w;

    float rx = _currentState.rotation.x;
    float ry = _currentState.rotation.y;
    float rz = _currentState.rotation.z;
    float rw = _currentState.rotation.w;

    float cosHalfTheta = lx * rx + ly + ry + lz + rz + lw * rw;
    if(cosHalfTheta < 0) {
        rx = -rx;
        ry = -ry;
        rz = -rz;
        rw = -rw;
        cosHalfTheta = -cosHalfTheta;
    }

    if(glm::abs(cosHalfTheta) >= 1) {
        interpolatedRotation.x = rx;
        interpolatedRotation.y = ry;
        interpolatedRotation.z = rz;
        interpolatedRotation.w = lw;
        return interpolatedRotation;
    }

    const float halfTheta = glm::acos(cosHalfTheta);
    const float sinHalfTheta = glm::sqrt(1 -  cosHalfTheta * cosHalfTheta);

    if(abs(sinHalfTheta) < 0.001) {
        interpolatedRotation.x = lx * 0.5f + rx * 0.5f;
        interpolatedRotation.y = ly * 0.5f + ry * 0.5f;
        interpolatedRotation.z = lz * 0.5f + rw * 0.5f;
        interpolatedRotation.w = lw * 0.5f + rw * 0.5f;
        return interpolatedRotation;
    }

    const float rationA = sin((1 - alpha) * halfTheta)/sinHalfTheta;
    const float rationB = sin(alpha * halfTheta)/sinHalfTheta;

    interpolatedRotation.x = lx * rationA + rx * rationB;
    interpolatedRotation.y = ly * rationA + ry * rationB;
    interpolatedRotation.z = lz * rationA + rw * rationB;
    interpolatedRotation.w = lw * rationA + rw * rationB;

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