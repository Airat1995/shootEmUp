#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

//TODO win over CMake about redundant Asset folder!
#include "Asset/Material/IShader.h"
#include "Asset/Material/IMaterial.h"
#include "VertexAttributeInfo.h"
#include "VertexBindingInfo.h"
#include "Shared/RenderAsset/IBuffer.h"

namespace Engine::Assets::Mesh
{
    using namespace Engine::Assets::Material;

    class IMesh {
    public:
        virtual ~IMesh() = default;

        virtual const void *VerticesData() = 0;

        virtual void const *IndicesData() = 0;

        virtual int VertexCount() = 0;

        virtual int IndexCount() = 0;

        virtual int RequiredBufferSize() = 0;

        virtual int VertexSize() = 0;

        virtual int IndexSize() = 0;

        virtual std::vector<VertexAttributeInfo> VertexInfo() = 0;

        virtual std::vector<VertexBindingInfo> GetVertexBindingInfo() = 0;

        virtual std::map<ShaderType, IShader> &Shaders() = 0;

        virtual void AddPerObjectBuffer(IBuffer *buffer) = 0;

        virtual std::vector<IBuffer *> &PerObjectBuffers() = 0;

        virtual IMaterial *Material() = 0;

        virtual bool IsStatic() {
            return _isStatic;
        }

        virtual void SetStatic(bool isStatic) {
            _isStatic = isStatic;
        }

        virtual void Move(glm::vec3& delta) {
            _model = glm::translate(_model, delta);
        }

        virtual void SetPosition(glm::vec3& position) {
            _model = glm::translate(glm::mat4(1), position);
        }

    protected:
        glm::mat4 _model;

        bool _isStatic;

        IMaterial *_material;
        IBuffer *_modelBuffer;
        std::vector<IBuffer *> _perObjectBuffers;
        std::vector<uint32_t> _indicies;
    };
}