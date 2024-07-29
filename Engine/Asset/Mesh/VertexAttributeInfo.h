#pragma once

#include "Format.h"
namespace Engine::Assets::Mesh
{
    struct VertexAttributeInfo {
        int Location;

        Format Format;

        int Offset;
    };
}