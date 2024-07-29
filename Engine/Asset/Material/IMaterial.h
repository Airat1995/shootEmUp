#pragma once

#include <string>
#include <map>

#include "Asset/Image/IImage.h"
#include "Render/Swapchain/ISwapchain.h"
#include "Shared/RenderAsset/IBuffer.h"
#include "Shared/RenderAsset/RenderQueue.h"
#include "IShader.h"

namespace Engine::Assets::Material
{
    using namespace Engine::Assets::Image;
    using namespace Engine::Render::Buffer;
    using namespace Engine::Shared::RenderAsset;

    class IMaterial {
    public:
        IMaterial(std::map<ShaderType, IShader> &shaders, RenderQueue renderQueue);
        void SetRenderQueue(int value);

        void AddBuffer(IBuffer *buffer);

        void AddImage(IImage *image);

        std::map<ShaderType, IShader> &MaterialShaders();

        std::vector<IBuffer *> &Buffers();

        std::vector<IImage *> &Images();

        int GetRenderQueue() const;

    protected:

        //Used in code generated materials
        IMaterial() {
        }

        std::map<ShaderType, IShader> _shaders;

        std::vector<IBuffer *> _buffers;

        std::vector<IImage *> _images;

        int _renderQueue;
    };
}