#pragma once

#include <glm/glm.hpp>
#include "VertexAttributeInfo.h"
#include "VertexBindingInfo.h"

using namespace std;
using namespace glm;

class BaseVertexData {
};

/**
 * Base data description structure
 * MUST FIT _bindingDescriptions and _attributeDescriptions to properly work with vertex input buffer
 */
class BaseVertexDescriptor {
public:
    virtual ~BaseVertexDescriptor() = default;

    vector<BaseVertexData> Vertecies() {
        return _vertexData;
    }

    vector<uint16_t> Indicies() {
        return _indices;
    }

    vector<VertexBindingInfo> &GetBindingInfo() {
        return _bindingInfo;
    }

    vector<VertexAttributeInfo> &GetVertexInfo() {
        return _vertexInfo;
    }

protected:
    vector<VertexAttributeInfo> _vertexInfo;

    vector<VertexBindingInfo> _bindingInfo;

    vector<BaseVertexData> _vertexData;

    vector<uint16_t> _indices;
};

