#pragma once

#include <vulkan/vulkan_core.h>
#include <iostream>
#include "Asset/Material/IShader.h"

namespace Engine::Render::Shader
{
    using namespace Engine::Assets::Material;

    class VulkanShader {
    public:
        VulkanShader(VkDevice device, IShader &basicShader, ShaderType shaderType);

        virtual ~VulkanShader();

        void DestroyShader() const;

        VkPipelineShaderStageCreateInfo GetShaderStageInfo() const noexcept;

    protected:
        VkShaderModule _shaderModule{};

        VkPipelineShaderStageCreateInfo _pipelineShader{};

        VkDevice _device;

    private:
        void CreatePipelineShaderStageCreateInfo(ShaderType shaderType, const std::string &moduleName);

        bool CreateShaderModule(VkDevice device, const char *fileData, unsigned long size);
    };
}