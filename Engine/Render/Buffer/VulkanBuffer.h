#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "BaseBuffer.h"


namespace Engine::Render::Buffer
{
    using namespace std;
    using namespace Engine::Assets::Image;
    using namespace Engine::Shared::RenderAsset;

    class VulkanBuffer {
    public:

        VulkanBuffer() {} //Empty constructor

        VulkanBuffer(VkDevice device, VkPhysicalDevice physical, Assets::Image::BufferStageFlag stageFlag, BufferUsageFlag usage,
                     BufferSharingMode sharingMode, const void *data, int size, int bindingId);

        static uint32_t FindMemoryType(uint32_t typeFilter, VkPhysicalDeviceMemoryProperties memoryProperties,
                                       VkMemoryPropertyFlags properties);

        void Fill();

        void Flush();

        virtual ~VulkanBuffer();

        void Destroy() const noexcept;

        VkBuffer Buffer() const;

        [[nodiscard]] int Binding() const;

        [[nodiscard]] int Size() const;

        const void *DataLocation() const;

        [[nodiscard]] VkDescriptorSetLayout DescriptorSetLayout() const;

        [[nodiscard]] VkDescriptorSetLayoutBinding DescriptorBindingInfo() const;

        VkDescriptorBufferInfo *BufferDescriptorInfo();

        static VkDescriptorType BufferUsageToDescriptorType(BufferUsageFlag bufferUsageFlag);

        static VkShaderStageFlagBits GetUsage(Assets::Image::BufferStageFlag stage);

    protected:
        VkBuffer _buffer;
        VkDeviceMemory _memory;
        VkDescriptorBufferInfo _bufferDescriptorInfo;
        VkDescriptorSetLayoutBinding _layoutBinding;
        VkDevice _device;
        VkBufferCreateInfo _bufferInfo;
        VkMemoryRequirements _memoryReq;
        VkPhysicalDevice _physical;
        BufferUsageFlag _usage;
        BufferSharingMode _sharingMode;
        VkDescriptorSetLayout _descriptorSetLayout;

        int _size;
        int _bindingId;
        int _dataSize;
        const void *_dataLocation;
        uint8_t *_dataPointer = nullptr;


    };
}