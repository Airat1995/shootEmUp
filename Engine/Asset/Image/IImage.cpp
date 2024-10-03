#include "IImage.h"

namespace Engine::Assets::Image
{
    IImage::IImage(ImageFormat format, ImageType type, ImageUsage usage, BufferStageFlag stage, int binding, int width,
                   int height, int sampleCount, std::vector<unsigned char> &imageData) : IResource(),
            _width(width), _height(height), _binding(binding), _sampleCount(sampleCount), _imageData(imageData),
              _format(format), _type(type), _usage(usage), _stage(stage) {
    }

    IImage::IImage(ImageFormat format, ImageType type, ImageUsage usage, BufferStageFlag stage, int binding, int width,
                   int height, int sampleCount) : IResource(), _width(width), _height(height), _binding(binding),
                                                  _sampleCount(sampleCount), _imageData(), _format(format), _type(type),
                                                  _usage(usage), _stage(stage) {

    }

    int IImage::Width() const {
        return _width;
    }

    int IImage::Height() const {
        return _height;
    }

    ImageType IImage::Type() const {
        return _type;
    }

    ImageFormat IImage::Format() const {
        return _format;
    }

    std::vector<unsigned char> *IImage::ImageData() {
        return &_imageData;
    }

    ImageUsage IImage::Usage() const {
        return _usage;
    }

    BufferStageFlag IImage::Stage() const {
        return _stage;
    }

    int IImage::Binding() const {
        return _binding;
    }

    int IImage::SampleCount() const {
        return _sampleCount;
    }
}