#pragma once

#include "Asset/Material/IShader.h"

class MainFragmentShader : public IShader {
    friend class MainMaterial;

protected:
    MainFragmentShader() : IShader() {
        _name = "main";
        _size = 0;
        std::ifstream shaderFile("/Users/airat/Projects/shootEmUp/Game/Assets/Shader/main.frag.spv",
                                 std::ios::in | std::ios::binary | std::ios::ate);
        if (shaderFile.is_open()) {
            const auto size = shaderFile.tellg();
            _size = size;
            _shaderData = new char[size];
            shaderFile.seekg(0, std::ios::beg);
            shaderFile.read(_shaderData, size);
            shaderFile.close();
        } else throw std::runtime_error("Unable to load shader file " + _name);
    }
};