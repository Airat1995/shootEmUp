#pragma once

#include "Asset/Mesh/Mesh.h"

class MainVertexData : BaseVertexData {
public:
    explicit MainVertexData(vec4 position) : position(position) {
    }

    MainVertexData() :
            position(vec<4, float>(0)), normal(vec<3, float>(0)) {

    }

    bool operator==(const MainVertexData &other) const {
        return position == other.position;
    }

    glm::vec<4, float> position;
    glm::vec<3, float> normal;
};
