#include "VulkanRenderpass.h"
#include <stdexcept>
#include <vector>

namespace Engine::Render::Render
{
    VulkanRenderpass::VulkanRenderpass(VkDevice device, VkFormat colorFormat, VkFormat depthFormat) {
        VkAttachmentDescription colorAttachment = {};
        colorAttachment.format = colorFormat;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentDescription depthAttachment{};
        depthAttachment.format = depthFormat;
        depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkAttachmentReference colorAttachmentRef = {};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkAttachmentReference depthAttachmentRef{};
        depthAttachmentRef.attachment = 1;
        depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass = {};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;
        subpass.pDepthStencilAttachment = &depthAttachmentRef;

        VkSubpassDependency dependency = {};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        std::vector<VkAttachmentDescription> attachments = {colorAttachment, depthAttachment};

        VkRenderPassCreateInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = attachments.size();
        renderPassInfo.pAttachments = attachments.data();
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;

        VkResult createResult = vkCreateRenderPass(device, &renderPassInfo, nullptr, &_renderPass);

        if (createResult != VK_SUCCESS)
            throw std::runtime_error("failed to create render pass!");
    }

    VkRenderPass VulkanRenderpass::RenderPass() {
        return _renderPass;
    }

    void
    VulkanRenderpass::BeginRenderPass(int width, int height, VkFramebuffer framebuffer, VkCommandBuffer commandBuffer) {
        VkClearValue clearValues[2];
        clearValues[0].color = {0.0f, 0.0f, 0.7f, 1.0f};
        clearValues[1].depthStencil = {1.0f, 0};


        _renderPassBeginInfo = {};
        _renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        _renderPassBeginInfo.renderPass = _renderPass;
        _renderPassBeginInfo.renderArea.offset.x = 0;
        _renderPassBeginInfo.renderArea.offset.y = 0;
        _renderPassBeginInfo.renderArea.extent.width = width;
        _renderPassBeginInfo.renderArea.extent.height = height;
        _renderPassBeginInfo.clearValueCount = 2;
        _renderPassBeginInfo.pClearValues = clearValues;
        _renderPassBeginInfo.framebuffer = framebuffer;
        _renderPassBeginInfo.pNext = nullptr;
        vkCmdBeginRenderPass(commandBuffer,
                             &_renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
    }

    void VulkanRenderpass::EndRenderPass(VkCommandBuffer commandBuffer) {
        vkCmdEndRenderPass(commandBuffer);

    }
}