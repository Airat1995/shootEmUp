#pragma once

#include "Asset/Image/IImage.h"
#include "Asset/Image/ImageFlags.h"
#include "Asset/Image/StageFlag.h"
#include "Render/Command/VulkanCommandPool.h"
#include "VulkanImage.h"

namespace Engine::Render::AssetWrapper
{
    using namespace std;
    using namespace Assets::Image;
    using namespace Engine::Render::Buffer;
    using namespace Engine::Render::Command;

    class BufferlessVulkanImage : public IImage
    {
    public:
        BufferlessVulkanImage(VulkanCommandPool* commandPool, ImageFormat format,
                              ImageType type, ImageUsage imageUsage,
                              BufferStageFlag stage,
            int width, int height, int imageCount, VkDevice device,	VkPhysicalDevice gpu, int binding, int graphicsFamilyIndex, int samples);

        VkImageView View();

        VkImage Image();

        static VkFormat ImageFormatToVulkan(ImageFormat format);

        static VkImageType ImageTypeToVulkan(ImageType type);

        static VkImageViewType ImageTypeToVulkanViewType(ImageType type);

        static VkImageUsageFlagBits ImageUsageToVulkan(ImageUsage usage);

        static int ImageCount(vector<unsigned char>& image, ImageType imageType, int width, int height, int channelsCount);

        static int ChannelsCount(ImageFormat format);

        static VkImageMemoryBarrier CreateImageMemoryBarrier();

        static bool MemoryTypeFromProperties(VkPhysicalDeviceMemoryProperties memoryProperties, uint32_t typeBits, VkFlags requirements_mask, uint32_t* typeIndex);

    protected:

        void CreateCopyCommandBuffer(VkImageUsageFlagBits imageUsage);

        void CreateSampler();

        void CreateDescriptorSetLayout();

        std::vector<VkBufferImageCopy> CreateRegion() const;

        VkImage _image;

        VkDeviceMemory _mem;

        VkImageView _view;

        VkImageLayout _imageLayout;

        VkDescriptorSetLayout _descriptorSetLayout;

        VkPhysicalDeviceMemoryProperties _memoryProperties;

        VkDevice _device;

        VulkanCommandBuffer* _commandBuffer;

        VulkanCommandPool* _commandPool;

        VkQueue _imageSubmitQueue;

        VkSampler _sampler;

        VkDescriptorImageInfo _imageInfo;

        VkDescriptorSetLayoutBinding _samplerLayoutBinding;

        int _graphicsFamilyIndex;

    };
}