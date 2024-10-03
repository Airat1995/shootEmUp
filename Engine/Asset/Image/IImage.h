#pragma once

#include "vector"

#include "ImageFlags.h"
#include "StageFlag.h"
#include "Asset/Resources/IResource.h"

namespace Engine::Assets::Image
{
    using namespace Engine::Assets::Resource;

    class IImage : public IResource {
    public:
        IImage(ImageFormat format, ImageType type, ImageUsage usage, BufferStageFlag stage, int binding, int width,
               int height, int sampleCount, std::vector<unsigned char> &imageData);

        IImage(ImageFormat format, ImageType type, ImageUsage usage, BufferStageFlag stage, int binding, int width,
               int height, int sampleCount);

        int Width() const;

        int Height() const;

        ImageType Type() const;

        ImageFormat Format() const;

        std::vector<unsigned char> *ImageData();

        ImageUsage Usage() const;

        BufferStageFlag Stage() const;

        int Binding() const;

        int SampleCount() const;

    protected:

        const int _width;

        const int _height;

        int _binding;

        const int _sampleCount;

        std::vector<unsigned char> _imageData;

        ImageFormat _format;

        ImageType _type;

        ImageUsage _usage;

        BufferStageFlag _stage;
    };
}