#pragma once

#include <vulkan/vulkan.h>
#include "IFramebuffer.h"
#include "Render/Swapchain/ISwapchain.h"
#include "Render/Render/VulkanRenderpass.h"
#include "Render/Pipeline/VulkanPipeline.h"
#include "Render/Command/VulkanCommandPool.h"
#include "Shared/RenderAsset/IBuffer.h"
#include "VulkanDepthBuffer.h"


namespace Engine::Render::Buffer
{
    using namespace std;
    using namespace Engine::Render::AssetWrapper;
    using namespace Engine::Render::Swapchain;

    class VulkanFramebuffer : public IFramebuffer {
    public:
        VulkanFramebuffer(VkDevice device, uint32_t grapQueueFI, uint32_t presentQueueFI, ISwapchain &swapchain,
                          VulkanRenderpass &renderpass, VulkanCommandPool &commandPool, VulkanDepthBuffer &depthBuffer);

        VulkanFramebuffer(VkDevice device, uint32_t grapQueueFI, uint32_t presentQueueFI, ISwapchain &swapchain,
                          BufferlessVulkanImage &image, VulkanRenderpass &renderpass, VulkanCommandPool &commandPool,
                          VulkanDepthBuffer &depthBuffer);


        VkFramebuffer *Framebuffer(int index);

        int FramebufferCount() const;

        void CreateQueues(VkDevice device, uint32_t grapQueueFI, uint32_t presentQueueFI);

        virtual ~VulkanFramebuffer();

        void SubmitFramebuffer(int index);

        VkQueue PresentQueue();

        VkQueue DrawQueue();

    private:
        vector<VkFramebuffer> *_swapChainFramebuffers;

        vector<SwapchainBuffer> *_swapchainBuffers;

        VkDevice _device;

        VkQueue _drawQueue;

        VkQueue _presentQueue;

        ISwapchain &_swapchain;

        VulkanCommandPool &_commandPool;

        VulkanRenderpass &_renderpass;

        VkSemaphore presentCompleteSemaphore;

        VkSemaphore renderCompleteSemaphore;

        std::vector<VkFence> waitFences;

        PFN_vkQueuePresentKHR fpQueuePresentKHR;
    };
}