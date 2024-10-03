#pragma once

#include <string>
#include <map>

#include "Asset/Image/IImage.h"
#include "Render/Swapchain/ISwapchain.h"
#include "Shared/RenderAsset/IBuffer.h"
#include "Shared/RenderAsset/RenderQueue.h"
#include "IShader.h"
#include "Asset/Resources/IResource.h"

namespace Engine::Assets::Material
{
    using namespace Engine::Assets::Resource;
    using namespace Engine::Assets::Image;
    using namespace Engine::Render::Buffer;
    using namespace Engine::Shared::RenderAsset;

    class IMaterial : public IResource {
    public:
        IMaterial(std::unordered_map<const ShaderType, IShader> &shaders, RenderQueue renderQueue);
        void SetRenderQueue(int value);

        void AddBuffer(IBuffer *buffer);

        void AddImage(IImage *image);

        const std::unordered_map<const ShaderType, IShader>& MaterialShaders() const;

        std::vector<IBuffer *> &Buffers();

        std::vector<IImage *> &Images();

        int GetRenderQueue() const;

        uint32_t ShaderId() 
        {
            uint32_t resourceId = 0;
            for (auto &&shader : _shaders)
            {
                resourceId += shader.second.GetResourceId();
            }
            return resourceId;
        }

    protected:

        //Used in code generated materials
        IMaterial() {
        }

        std::unordered_map<const ShaderType, IShader> _shaders;

        std::vector<IBuffer *> _buffers;

        std::vector<IImage *> _images;

        int _renderQueue;
    };
}