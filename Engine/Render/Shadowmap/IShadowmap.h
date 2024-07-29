#pragma once
#include "Render/Command/ICommandBuffer.h"

namespace Engine::Render::Shadowmap
{
    using namespace Engine::Render::Command;

    class IShadowmap
    {
    public:

        IShadowmap(int width, int height, int binding) : _width(width), _height(height), _binding(binding) {}

        virtual void Draw(ICommandBuffer* commandBuffer, int index) = 0;

    protected:

        int _width;

        int _height;

        int _binding;
    };
}
