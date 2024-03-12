
#include "MainMesh.h"
#include "Render/Buffer/BaseBuffer.h"
#include <utility>

static MainDescriptorVertexDescriptor _descriptor = {};

MainMesh::MainMesh(std::vector<MainVertexData> vertecies, IMaterial* material) : _vertecies(std::move(vertecies))
{
    _material = material;
}

MainMesh::MainMesh(std::vector<MainVertexData> vertecies, std::vector<int> indicies, IMaterial* material) : _vertecies(std::move(vertecies))
{
    _material = material;
    _indicies = std::move(indicies);
    _modelBuffer = new BaseBuffer(BufferUsageFlag::UniformBuffer, BufferSharingMode::Exclusive, &_model, BufferStageFlag::Vertex, 1);
    _perObjectBuffers.push_back(_modelBuffer);
}

const void * MainMesh::VerticesData()
{
    return _vertecies.data();
}

const void * MainMesh::IndicesData()
{
    return _indicies.data();
}

int MainMesh::VertexCount()
{
    return _vertecies.size();
}

int MainMesh::RequiredBufferSize()
{
    return VertexSize() * VertexCount();
}

int MainMesh::VertexSize()
{
    return sizeof(MainVertexData);
}

int MainMesh::IndexSize()
{
    return sizeof(int);
}

int MainMesh::IndexCount()
{
    return _indicies.size();
}

std::vector<VertexAttributeInfo> MainMesh::VertexInfo()
{
    return _descriptor.GetVertexInfo();
}

std::vector<VertexBindingInfo> MainMesh::GetVertexBindingInfo()
{
    return _descriptor.GetBindingInfo();
}

std::map<ShaderType, IShader> & MainMesh::Shaders()
{
    return _material->MaterialShaders();
}

void MainMesh::AddPerObjectBuffer(IBuffer *buffer)
{
    _perObjectBuffers.push_back(buffer);
}

std::vector<IBuffer *> & MainMesh::PerObjectBuffers()
{
    return _perObjectBuffers;
}

IMaterial * MainMesh::Material()
{
    return _material;
}
