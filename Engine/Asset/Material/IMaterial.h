#pragma once

#include <string>
#include <map>

#include "Asset/Image/IImage.h"
#include "Render/Swapchain/ISwapchain.h"
#include "Shared/RenderAsset/IBuffer.h"
#include "Shared/RenderAsset/RenderQueue.h"
#include "IShader.h"

class IMaterial {
public:
    IMaterial(std::map<ShaderType, IShader> &shaders, RenderQueue renderQueue);

    void AddBuffer(IBuffer *buffer);

    void AddImage(IImage *image);

    std::map<ShaderType, IShader> &MaterialShaders();

    std::vector<IBuffer *> &Buffers();

    std::vector<IImage *> &Images();

    RenderQueue GetRenderQueue();

protected:

    //Used in code generated materials
    IMaterial() {
    }

    std::map<ShaderType, IShader> _shaders;

    std::vector<IBuffer *> _buffers;

    std::vector<IImage *> _images;

    RenderQueue _renderQueue;
};
