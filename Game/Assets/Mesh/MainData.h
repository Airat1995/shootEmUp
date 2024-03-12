#pragma once

#include "Asset/Mesh/Mesh.h"

class MainVertexData : BaseVertexData {
public:
    explicit MainVertexData(vec4 position) : position(position) {
    }

    glm::vec<4, float> position;
};