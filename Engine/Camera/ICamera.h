#pragma once

#include "CameraObject.h"


template<typename T>
class ICamera {
public:
    virtual void SetPosition(glm::vec3 &position) = 0;

    virtual void SetRotation(glm::vec3 &rotation) = 0;

    virtual void Rotate(glm::vec3 &delta) = 0;

    virtual void Move(glm::vec3 &delta) = 0;

    virtual void SetPerspective(float fov, float aspect, float zNear, float zFar) = 0;

    virtual void SetAspect(float aspect) = 0;

    virtual float GetNear() = 0;

    virtual float GetFar() = 0;

    virtual glm::vec3 GetPosition() = 0;

    virtual T &GetCameraObject() = 0;
};