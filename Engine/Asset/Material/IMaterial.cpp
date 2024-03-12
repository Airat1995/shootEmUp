#include "IMaterial.h"

IMaterial::IMaterial(std::map<ShaderType, IShader>& shaders, RenderQueue renderQueue) : _shaders(shaders), _renderQueue(renderQueue)
{
	_buffers = std::vector<IBuffer*>();
}

void IMaterial::AddBuffer(IBuffer* buffer)
{
	_buffers.push_back(buffer);
}

void IMaterial::AddImage(IImage* image)
{
	_images.push_back(image);
}

std::map<ShaderType, IShader>& IMaterial::MaterialShaders()
{
	return _shaders;
}

std::vector<IBuffer*>& IMaterial::Buffers()
{
	return _buffers;
}

std::vector<IImage*>& IMaterial::Images()
{
	return _images;
}

RenderQueue IMaterial::GetRenderQueue()
{
	return _renderQueue;
}
