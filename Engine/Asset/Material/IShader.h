#pragma once
#include "Common/IO/FileReader.h"

enum class ShaderType
{
    Vertex = 0x00000001,
    TesselationControl = 0x00000002,
    TesselationEvaluation = 0x00000004,
    Geometry = 0x00000008,
    Fragment = 0x00000010,
    Compute = 0x00000020,
    Raygen = 0x00000100,
    AnyHit = 0x00000200,
    ClosetHit = 0x00000400,
    Mesh = 0x00000080,
};

class IShader
{
public:
    explicit IShader(char *shaderData, unsigned long size, std::string name):
        _name(std::move(name)), _size(size)
    {
        _shaderData = new char[size];
        memcpy(_shaderData, shaderData, size);
    }


    char *ShaderData()
    {
        return _shaderData;
    }

    int ShaderSize()
    {
        return _size;
    }


    std::string &Name() noexcept
    {
        return _name;
    }

protected:
    //Used in code generated shaders
    IShader()
    {
    }

    std::string _name;

    char *_shaderData;

    unsigned long _size;
};

