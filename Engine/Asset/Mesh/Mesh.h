
#pragma once

#include <utility>

#include "IMesh.h"
#include "BaseVertexDescriptor.h"
#include "Asset/Resources/IResource.h"

namespace Engine::Assets::Mesh
{
    using namespace Engine::Assets::Resource;
    using namespace Engine::Assets::Material;

    template
            <
                    typename VertexDataT,
                    typename = enable_if<is_base_of_v<VertexDataT, BaseVertexDescriptor>>
            >
    class Mesh : public IMesh {
    public:
        Mesh(const Mesh &mesh) : IResource (mesh) {}
        Mesh(Mesh &&mesh) : IResource(mesh) {}
        Mesh &operator=(const Mesh &) = delete;
        Mesh &operator=(Mesh &&) = delete;
        virtual ~Mesh() = default;

        Mesh(VertexDataT &vertexDescriptor, IMaterial &material)
                : IMesh(), _vertexDescriptor(vertexDescriptor), _vertices(), _material(std::move(material)),
                  _indexes(vertexDescriptor.Indices()) {
            FillVertexDatas();
            if (!_indexes.empty()) {
                _indexed = true;
            }
        }

        void FillVertexDatas() {
            _vertexDatas = vector<BaseVertexData>();
            for (size_t index = 0; index < _vertices.size(); ++index) {
                _vertexDatas.push_back(_vertices[index].GetVertexData());
            }
        }

        const void *VerticesData() override {
            return _vertexDatas.data();
        }

        int VertexCount() override {
            return _vertices.size();
        }

        void const *IndicesData() override {
            return _indexes.data();
        }

        int RequiredBufferSize() override {
            return VertexSize() * _vertexDatas.size();
        }

        int VertexSize() override {
            return VertexDataT::VertexSize();
        }

        int IndexSize() override {
            return _indexes.size();
        }

        vector<VertexAttributeInfo> VertexInfo() override {
            return VertexDataT::GetVertexInfo();
        }

        vector<VertexBindingInfo> GetVertexBindingInfo() override {
            return _vertices.at(0).GetBindingInfo();
        }

        const unordered_map<const ShaderType, IShader>& Shaders() const override {
            return _material.MaterialShaders();
        }

        IMaterial *Material() override {
            return &_material;
        }

        void AddPerObjectBuffer(IBuffer *buffer) override {
            _perObjectBuffers.push_back(buffer);
        }

        vector<IBuffer *> &PerObjectBuffers() override {
            return _perObjectBuffers;
        }

    protected:

        vector<VertexDataT> _vertices;

        vector<uint16_t> _indexes;

        vector<IBuffer *> _perObjectBuffers;

        VertexDataT &_vertexDescriptor;

    private:
        bool _indexed = false;

        vector<BaseVertexData> _vertexDatas;

        IMaterial _material;
    };
}