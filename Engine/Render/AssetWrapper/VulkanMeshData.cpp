#include "VulkanMeshData.h"

namespace Engine::Render::AssetWrapper
{
    VulkanMeshData::VulkanMeshData(IMesh* mesh, VkDevice device, VkPhysicalDevice gpu, VulkanCommandPool* commandPool, uint32_t graphicsQueueFamilyIndex) : _mesh(mesh), _vertexBuffer{}
    {  
       for (auto *buffer : mesh->Material()->Buffers())
       {
           VulkanBuffer bufferData =
               VulkanBuffer(device, gpu, buffer->StageFlag(), buffer->Usage(), buffer->SharingMode(),
                            buffer->RawData(), buffer->Size(), buffer->BindingId());
            bufferData.Fill();
           _buffers.push_back(bufferData);
       }

       for (auto *image : mesh->Material()->Images())
       {
           auto imageData = VulkanImage(commandPool, image->Format(), image->Type(), image->Usage(), image->Stage(),
                                        image->Width(), image->Height(), *image->ImageData(), device, gpu,
                                        image->Binding(), graphicsQueueFamilyIndex, image->SampleCount());
           _images.push_back(imageData);
       }

        for (vector<IBuffer *>::value_type &buffer : mesh->PerObjectBuffers())
        {
            VulkanBuffer constBuffer = {device, gpu, buffer->StageFlag(), buffer->Usage(), buffer->SharingMode(),
                            buffer->RawData(), buffer->Size(), buffer->BindingId()};
            _perObjectBuffers.push_back(constBuffer);
        }

       _vertexBuffer = {device, gpu, mesh->RequiredBufferSize(), mesh->VertexCount()};
       _vertexBuffer.Fill(mesh->VerticesData());
       _vertexCount = mesh->VertexCount();

        if (mesh->IndexCount() > 0)
        {
            _indices = {device, gpu, BufferStageFlag::Vertex,
                                                      BufferUsageFlag::IndexBuffer | BufferUsageFlag::TransferDst, BufferSharingMode::Exclusive,
                                                      mesh->IndicesData(), mesh->IndexSize() * mesh->IndexCount(), 0};

            _indices.Fill();
            _indicesSize = mesh->IndexCount();
            _indexed = true;
        }

        _bindingDescriptions = vector<VkVertexInputBindingDescription>();
        vector<VertexAttributeInfo> vertexAttributesBindings = _mesh->VertexInfo();
        vector<VertexBindingInfo> vertexBindings = _mesh->GetVertexBindingInfo();
        for (auto& vertexBinding : vertexBindings)
        {
            for (auto& attributeBinding : vertexAttributesBindings)
            {
                VkVertexInputAttributeDescription vertexAttribute = CreateAttributeDescription(vertexBinding.BindId, attributeBinding.Location,
                    EnumFormatToVulkanFormat(attributeBinding.Format), attributeBinding.Offset);
                _attributeDescriptions.push_back(vertexAttribute);
            }

            VkVertexInputRate inputRate = vertexBinding.Instanced ? VkVertexInputRate::VK_VERTEX_INPUT_RATE_INSTANCE : VkVertexInputRate::VK_VERTEX_INPUT_RATE_VERTEX;
            VkVertexInputBindingDescription bindingDescriptions =
                CreateInputBindingDescription(vertexBinding.BindId,
                    vertexBinding.Size, inputRate);

            _bindingDescriptions.push_back(bindingDescriptions);
        }
    }

    std::vector<VkVertexInputBindingDescription> VulkanMeshData::BindingDescriptions()
    {
        return _bindingDescriptions;
    }

    std::vector<VkVertexInputAttributeDescription> VulkanMeshData::AttributeDescriptions()
    {
        return _attributeDescriptions;
    }

    IMesh* VulkanMeshData::RawMesh() const noexcept
    {
        return _mesh;
    }

    vector<VulkanBuffer>& VulkanMeshData::Buffers() noexcept
    {
        return _buffers;
    }

    vector<VulkanImage>& VulkanMeshData::Images() noexcept {
        return _images;
    }

    vector<VulkanBuffer>& VulkanMeshData::PerObjectBuffersInfo()
    {
        return _perObjectBuffers;
    }

    void VulkanMeshData::Draw(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, uint32_t firstBinding, uint32_t bindingCount) noexcept
    {
        VkDeviceSize offsets[1] = {0};
        int indicesIndex = 0;

        for (auto &&constantBuffer : _perObjectBuffers)
        {
            vkCmdPushConstants(commandBuffer, pipelineLayout, constantBuffer.DescriptorBindingInfo().stageFlags, 0,
                               constantBuffer.Size(), constantBuffer.DataLocation());
        }
        vkCmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, &_vertexBuffer.Buffer(), offsets);
        if (_indexed)
        {
            vkCmdBindIndexBuffer(commandBuffer, _indices.Buffer(), 0, VK_INDEX_TYPE_UINT32);
            vkCmdDrawIndexed(commandBuffer, _indicesSize, 1, 0, 0, 0);
            indicesIndex++;
        }
        else
        {
            vkCmdDraw(commandBuffer, _vertexCount, 1, 0, 0);
        }
    }
}
