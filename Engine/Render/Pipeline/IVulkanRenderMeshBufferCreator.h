#pragma once
#include "Asset/Mesh/IMesh.h"
#include "Render/Buffer/VulkanBuffer.h"

namespace Engine::Render::Pipeline
{
    using namespace std;
    using namespace Engine::Assets::Mesh;
    using namespace Engine::Render::Buffer;

    class IVulkanRenderMeshBufferCreator
    {
    public:
        virtual void AddMesh(IMesh *mesh, vector<VulkanBuffer> perObjectBuffers) = 0;
        virtual void RemoveMesh(IMesh * mesh) = 0;
    };
}