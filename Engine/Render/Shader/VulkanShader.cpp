#include "VulkanShader.h"

namespace Engine::Render::Shader
{
    VulkanShader::VulkanShader(const VkDevice device, IShader &basicShader, const ShaderType shaderType) :
            _device(device) {
        const bool isShaderCreated = CreateShaderModule(device, basicShader.ShaderData(), basicShader.ShaderSize());
        if (isShaderCreated)
            CreatePipelineShaderStageCreateInfo(shaderType, basicShader.Name());
        else
            std::cerr << "Unable to create shader module. Shader location: " << basicShader.ShaderData() << std::endl;

    }

    VulkanShader::~VulkanShader() {
        _shaderModule = nullptr;

    }

    void VulkanShader::DestroyShader() const {
        vkDestroyShaderModule(_device, _shaderModule, nullptr);
    }


    VkPipelineShaderStageCreateInfo VulkanShader::GetShaderStageInfo() const noexcept {
        return _pipelineShader;
    }

    void VulkanShader::CreatePipelineShaderStageCreateInfo(ShaderType shaderType, const std::string &moduleName) {
        _pipelineShader.flags = 0;
        _pipelineShader.pNext = nullptr;
        _pipelineShader.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        _pipelineShader.stage = static_cast<VkShaderStageFlagBits>(static_cast<int32_t>(shaderType));
        _pipelineShader.module = _shaderModule;
        _pipelineShader.pSpecializationInfo = nullptr;
        _pipelineShader.pName = moduleName.c_str();
    }

    bool VulkanShader::CreateShaderModule(VkDevice device, const char *fileData, unsigned long size) {
        VkShaderModuleCreateInfo createInfo;
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = size;
        createInfo.pCode = reinterpret_cast<const uint32_t *>(fileData);
        createInfo.pNext = nullptr;
        createInfo.flags = 0;

        const VkResult result = vkCreateShaderModule(device, &createInfo, nullptr, &_shaderModule);
        return result == VK_SUCCESS;
    }
}
