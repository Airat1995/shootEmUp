#pragma once
#include <map>
#include "IPipeline.h"
#include "IVulkanRenderMeshBufferCreator.h"
#include "Render/Shader/VulkanShader.h"
#include "Render/Render/VulkanRenderpass.h"
#include "Render/Buffer/VertexBuffer.h"
#include "Render/Buffer/VulkanBuffer.h"
#include "Render/AssetWrapper/VulkanMeshData.h"

namespace Engine::Render::Pipeline
{
    using namespace std;
    using namespace Engine::Render::AssetWrapper;
    using namespace Engine::Render::Render;
    using namespace Engine::Render::Shader;

    class VulkanPipeline : public IPipeline
    {
    public:
        explicit VulkanPipeline(VkDevice device, VkPhysicalDevice physical, VulkanRenderpass& renderpass,
            VulkanMeshData& vulkanMeshData, VkExtent2D extent);

        
        VulkanPipeline(const VulkanPipeline& copy) noexcept
            : _pipelineLayout(copy._pipelineLayout), _device(copy._device), 
              _physical(copy._physical), _descriptorPool(copy._descriptorPool),
              _descriptorSets(copy._descriptorSets), _descriptorSetLayout(copy._descriptorSetLayout), _renderPass(copy._renderPass),
              _drawMeshes(std::move(copy._drawMeshes)), _firstBinding(copy._firstBinding), _bindingCount(copy._bindingCount)
        {
        }

        virtual VulkanPipeline& operator=(const VulkanPipeline& copy)
        {
            if (this == &copy)
                return *this;
            VulkanPipeline temp(copy);
            return *this;
        }
        
        VulkanPipeline(VulkanPipeline&& move) noexcept
            : _pipelineLayout(move._pipelineLayout), _device(move._device), 
              _physical(move._physical), _descriptorPool(move._descriptorPool),
              _descriptorSets(move._descriptorSets), _descriptorSetLayout(move._descriptorSetLayout), _renderPass(move._renderPass),
              _drawMeshes(std::move(move._drawMeshes)), _firstBinding(move._firstBinding), _bindingCount(move._bindingCount)
        {
        }

        virtual VulkanPipeline& operator=(VulkanPipeline&& move) noexcept
        {
            VulkanPipeline temp(std::move(move));
            return temp;
        }

        virtual ~VulkanPipeline();

        VkPipeline Pipeline();

        VkPipelineLayout PipelineLayout();

        void DestroyPipeline() const;

        void BindPipeline(VkCommandBuffer commandBuffer);

        void BuildCommandbuffer(VkCommandBuffer commandBuffer);

        void AddMesh(VulkanMeshData mesh);

        bool TryRemoveMesh(IMesh* mesh);

        bool ShouldUseThisPipeline(VulkanMeshData& meshData);

    private:

        vector<VulkanShader> BaseShadersToVulkanShader(VkDevice device, std::unordered_map<const ShaderType, IShader>& shaders);

        VkDynamicState _dynamicStates[2] = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_LINE_WIDTH
        };

        VkPipelineLayout _pipelineLayout{};

        VkDevice _device{};

        VkPhysicalDevice _physical;

        VkPipeline _pipeline{};

        VkDescriptorPool _descriptorPool;

        VkDescriptorSet _descriptorSets;

        VkDescriptorSetLayout _descriptorSetLayout;

        VulkanRenderpass& _renderPass;

        vector<VulkanMeshData> _drawMeshes;

        vector<uint32_t> _drawMeshIds;

        uint32_t _pipelineShaderId;

        uint32_t _firstBinding;

        size_t _bindingCount;
    };
}