
#pragma once

#include "tiny_obj_loader.h"
#include "MainData.h"
#include "Asset/Mesh/IMesh.h"
#include "MainDescriptor.h"

namespace Game::Assets::Mesh
{
    using namespace Game::Assets::Mesh;

    class MainMesh : public IMesh {
    public:

        explicit MainMesh(std::vector<MainVertexData> vertecies, IMaterial *material);

        MainMesh(std::vector<MainVertexData> vertecies, std::vector<uint32_t> indicies, IMaterial *material);

        static MainMesh *Parse(const std::filesystem::path &filePath, IMaterial *material);

        const void *VerticesData() override;

        const void *IndicesData() override;

        int VertexCount() override;

        int IndexCount() override;

        int RequiredBufferSize() override;

        int VertexSize() override;

        int IndexSize() override;

        std::vector<VertexAttributeInfo> VertexInfo() override;

        std::vector<VertexBindingInfo> GetVertexBindingInfo() override;

        const std::unordered_map<const ShaderType, IShader> &Shaders() const override;

        void AddPerObjectBuffer(IBuffer *buffer) override;

        std::vector<IBuffer *> &PerObjectBuffers() override;

        IMaterial *Material() override;

        std::vector<MainVertexData> &GetVertecies();

    private:

        std::vector<MainVertexData> _vertecies;

    };
}