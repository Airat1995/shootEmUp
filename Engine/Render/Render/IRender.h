#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Asset/Mesh/IMesh.h"
#include "Camera/CameraObject.h"


namespace Engine::Render::Render
{
    using namespace std;
    using namespace Engine::Assets::Mesh;
    using namespace Engine::Camera;

    class IRender {
    public:
        virtual ~IRender() = default;

        virtual void Init() = 0;

        virtual void AddMesh(IMesh *mesh) = 0;

        virtual void RemoveMesh(IMesh *mesh) = 0;

        virtual void DrawFrame() = 0;
    };
}
