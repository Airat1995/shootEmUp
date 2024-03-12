
#pragma once
#include "MainData.h"
#include "Asset/Mesh/IMesh.h"
#include "MainDescriptor.h"


class MainMesh : public IMesh {
public:

    explicit MainMesh(std::vector<MainVertexData> vertecies, IMaterial* material);

    MainMesh(std::vector<MainVertexData> vertecies, std::vector<int> indicies, IMaterial* material);

    const void * VerticesData() override;
    const void * IndicesData() override;
    int VertexCount() override;
    int IndexCount() override;
    int RequiredBufferSize() override;
    int VertexSize() override;
    int IndexSize() override;
    std::vector<VertexAttributeInfo> VertexInfo() override;
    std::vector<VertexBindingInfo> GetVertexBindingInfo() override;
    std::map<ShaderType, IShader> & Shaders() override;
    void AddPerObjectBuffer(IBuffer *buffer) override;
    std::vector<IBuffer *> & PerObjectBuffers() override;
    IMaterial * Material() override;

private:

    std::vector<MainVertexData> _vertecies;

};
