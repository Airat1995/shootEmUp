#pragma once

#include "Asset/Mesh/Mesh.h"

namespace Game::Assets::Mesh
{
    using namespace glm;
    using namespace Engine::Assets::Mesh;

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

        vec<4, float> position;
        vec<3, float> normal;
    };
}