#pragma once

#include "Asset/Mesh/Mesh.h"

namespace Game::Assets::Mesh
{
    using namespace Engine::Assets::Mesh;

    class MainDescriptorVertexDescriptor : public BaseVertexDescriptor {
    public:
        MainDescriptorVertexDescriptor() {
            _vertexInfo = vector<VertexAttributeInfo>();
            VertexAttributeInfo position{};
            position.Location = 0;
            position.Offset = 0;
            position.Format = Format::Vector4SF;
            _vertexInfo.push_back(position);

            VertexAttributeInfo normal{};
            normal.Location = 1;
            normal.Offset = 16;
            normal.Format = Format::Vector3SF;
            _vertexInfo.push_back(normal);

            _bindingInfo = vector<VertexBindingInfo>();
            VertexBindingInfo bindingInfo{};
            bindingInfo.BindId = 0;
            bindingInfo.Size = 28;
            bindingInfo.Instanced = false;
            _bindingInfo.push_back(bindingInfo);
        }
    };
}