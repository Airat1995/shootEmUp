#include "IMaterial.h"

namespace Engine::Assets::Material
{
    IMaterial::IMaterial(std::unordered_map<const ShaderType, IShader> &shaders, RenderQueue renderQueue) : IResource(),
        _shaders(shaders), _renderQueue(renderQueue)
    {
        _buffers = std::vector<IBuffer *>();
    }

    void IMaterial::SetRenderQueue(int value) {_renderQueue = value;}

    void IMaterial::AddBuffer(IBuffer *buffer) { _buffers.push_back(buffer); }

    void IMaterial::AddImage(IImage *image) { _images.push_back(image); }

    const std::unordered_map<const ShaderType, IShader>& IMaterial::MaterialShaders() const { return _shaders; }

    std::vector<IBuffer *> &IMaterial::Buffers() { return _buffers; }

    std::vector<IImage *> &IMaterial::Images() { return _images; }

    int IMaterial::GetRenderQueue() const { return _renderQueue; }
}