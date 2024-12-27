#pragma once
#include "Asset/Mesh/IMesh.h"
#include "Render/Buffer/VertexBuffer.h"
#include "Render/Shader/VulkanShader.h"
#include "Render/Buffer/VulkanBuffer.h"
#include "Render/Pipeline/IVulkanRenderMeshBufferCreator.h"
#include "VulkanImage.h"

namespace Engine::Render::AssetWrapper
{
    using namespace Engine::Assets::Material;
    using namespace Engine::Assets::Mesh;
    using namespace Engine::Render::Pipeline;

    class VulkanMeshData
    {
    public:
        VulkanMeshData(IMesh * mesh, VkDevice device, VkPhysicalDevice gpu, VulkanCommandPool* commandPool, uint32_t graphicsQueueFamilyIndex);

        IMesh* RawMesh() const noexcept;

        void Draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, uint32_t firstBinding, uint32_t bindingCount) noexcept;

        vector<VkVertexInputBindingDescription> BindingDescriptions();

        vector<VkVertexInputAttributeDescription> AttributeDescriptions();

        vector<VulkanBuffer>& Buffers() noexcept;

        vector<VulkanImage>& Images() noexcept;

        vector<VulkanBuffer>& PerObjectBuffersInfo();

    private:
        vector<VkVertexInputBindingDescription> _bindingDescriptions;

        vector<VkVertexInputAttributeDescription> _attributeDescriptions;

        IMesh* _mesh;

        vector<VulkanBuffer> _buffers;

        vector<VulkanImage> _images;

        vector<VulkanBuffer> _perObjectBuffers;// = std::map<IMesh*, vector<VulkanBuffer>>();

        VertexBuffer _vertexBuffer;

        VulkanBuffer _indices;

        int _vertexCount;

        int _indicesSize;

        bool _needRebuild;

        bool _indexed;

        inline VkVertexInputAttributeDescription CreateAttributeDescription(
            uint32_t binding,
            uint32_t location,
            VkFormat format,
            uint32_t offset)
        {
            VkVertexInputAttributeDescription vInputAttribDescription{};
            vInputAttribDescription.location = location;
            vInputAttribDescription.binding = binding;
            vInputAttribDescription.format = format;
            vInputAttribDescription.offset = offset;
            return vInputAttribDescription;
        }

        inline VkVertexInputBindingDescription CreateInputBindingDescription(
            uint32_t binding,
            uint32_t stride,
            VkVertexInputRate inputRate)
        {
            VkVertexInputBindingDescription vInputBindDescription{};
            vInputBindDescription.binding = binding;
            vInputBindDescription.stride = stride;
            vInputBindDescription.inputRate = inputRate;
            return vInputBindDescription;
        }

    protected:
        inline VkFormat EnumFormatToVulkanFormat(Format format)
        {
            VkFormat vulkanFormat = VK_FORMAT_UNDEFINED;
            switch (format)
            {
            case Format::Int:
                vulkanFormat = VK_FORMAT_R8_SINT;
                break;
            case Format::UInt:
                vulkanFormat = VK_FORMAT_R8_UINT;
                break;
            case Format::Float:
                vulkanFormat = VK_FORMAT_R32_SFLOAT;
                break;
            case Format::Double:
                vulkanFormat = VK_FORMAT_R16_SFLOAT;
                break;
            case Format::Vector1F:
            case Format::Vector1SF:
                vulkanFormat = VK_FORMAT_R8_SSCALED;
                break;
            case Format::Vector1I:
                vulkanFormat = VK_FORMAT_R8_SSCALED;
                break;
            case Format::Vector2F:
            case Format::Vector2SF:
                vulkanFormat = VK_FORMAT_R32G32_SFLOAT;
                break;
            case Format::Vector2I:
                vulkanFormat = VK_FORMAT_R32G32_SINT;
                break;
            case Format::Vector3F:
            case Format::Vector3SF:
                vulkanFormat = VK_FORMAT_R32G32B32_SFLOAT;
                break;
            case Format::Vector3I:
                vulkanFormat = VK_FORMAT_R32G32B32_SINT;
                break;
            case Format::Vector4F:
            case Format::Vector4SF:
                vulkanFormat = VK_FORMAT_R32G32B32A32_SFLOAT;
                break;
            case Format::Vector4I:
                vulkanFormat = VK_FORMAT_R32G32B32A32_SINT;
                break;
            case Format::Quaternion:
                break;
            default:;
            }

            return vulkanFormat;
        }
    };
}
