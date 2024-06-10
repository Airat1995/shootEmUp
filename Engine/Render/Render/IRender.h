#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Asset/Mesh/IMesh.h"
#include "Camera/CameraObject.h"


using namespace std;

class IRender {
public:
    virtual ~IRender() = default;

    virtual void Init() = 0;

    virtual void AddMesh(IMesh *mesh) = 0;

    virtual void RemoveMesh(IMesh *mesh) = 0;

    virtual void DrawFrame() = 0;

    virtual void AddShadowmap(glm::vec4 *lightPosition, CameraObject *camera) = 0;
};

