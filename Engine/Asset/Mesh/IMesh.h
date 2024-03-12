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

class IMesh
{
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

    virtual bool IsStatic()
    {
        return _isStatic;
    }

    virtual void SetStatic(bool isStatic)
    {
        _isStatic = isStatic;
    }

protected:
    glm::mat4 _model;

    bool _isStatic;

    IMaterial* _material;
    IBuffer* _modelBuffer;
    std::vector<IBuffer*> _perObjectBuffers;
    std::vector<int> _indicies;
};
