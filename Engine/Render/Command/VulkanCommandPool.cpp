#include "VulkanCommandPool.h"
namespace Engine::Render::Command
{
    VulkanCommandPool::VulkanCommandPool(VkDevice device, int queueFamilyIndex) : _device(device)
    {
        VkCommandPoolCreateInfo commandPoolInfo;
        commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        commandPoolInfo.pNext = nullptr;
        commandPoolInfo.queueFamilyIndex = queueFamilyIndex;
        commandPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        _vulkanCommandBuffers = {};
        const VkResult result = vkCreateCommandPool(device, &commandPoolInfo, nullptr, &_commandPool);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Unable to create command pool!");
        }
    }

    VulkanCommandPool::~VulkanCommandPool()
    {
        auto* commandBuffers = new VkCommandBuffer[_commandBuffers.size()];
        for (int commandBufferIndex = 0; commandBufferIndex < _commandBuffers.size(); ++commandBufferIndex)
            commandBuffers[commandBufferIndex] = _commandBuffers[commandBufferIndex].CommandBuffer();

        vkFreeCommandBuffers(_device, _commandPool, _commandBuffers.size(), commandBuffers);
        vkDestroyCommandPool(_device, _commandPool, nullptr);
        delete[] commandBuffers;
    }

    void VulkanCommandPool::AddCommandBuffer()
    {
        VulkanCommandBuffer commandBuffer = VulkanCommandBuffer(_device, _commandPool);
        _commandBuffers.push_back(commandBuffer);
        _vulkanCommandBuffers.push_back(commandBuffer.CommandBuffer());
    }

    void VulkanCommandPool::BeginCommandPool()
    {
        for (auto commandBuffer : _commandBuffers)
            commandBuffer.BeginCommandBuffer();
    }

    int VulkanCommandPool::CommandBufferCount()
    {
        return _commandBuffers.size();
    }

    VulkanCommandBuffer& VulkanCommandPool::CommandBuffer(int index)
    {
        return _commandBuffers[index];
    }

    void VulkanCommandPool::ResetCommandBuffers()
    {
        for (VulkanCommandBuffer commandBuffer : _commandBuffers)
        {
            commandBuffer.Reset();
        }
    }

    VkCommandPool VulkanCommandPool::CommandPool()
    {
        return _commandPool;
    }

    VkCommandBuffer* VulkanCommandPool::CommandBuffersData()
    {
        return  _vulkanCommandBuffers.data();
    }
}