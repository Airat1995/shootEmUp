#pragma once

#include "Asset/Material/IMaterial.h"
#include "MainFragmentShader.h"
#include "MainVertexShader.h"

class MainMaterial : public IMaterial {
public:
    MainMaterial() {
        _shaders.emplace(ShaderType::Fragment, MainFragmentShader{});
        _shaders.emplace(ShaderType::Vertex, MainVertexShader{});
    }
};