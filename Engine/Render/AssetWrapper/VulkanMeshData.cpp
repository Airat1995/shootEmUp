#include "VulkanMeshData.h"

namespace Engine::Render::AssetWrapper
{
    VulkanMeshData::VulkanMeshData(IMesh* mesh, vector<VulkanBuffer>& buffers, vector<VulkanImage>& images, vector<VulkanBuffer>& perObjectBuffers)
        : _buffers(buffers), _images(images), _needRebuild(true), _perObjectBuffers(map<IMesh*, vector<VulkanBuffer>>())
    {
        _perObjectBuffers = map<IMesh*, vector<VulkanBuffer>>();
        _meshes = vector<IMesh*>();
        _meshes.push_back(mesh);

        _perObjectBuffers.insert({ mesh, perObjectBuffers });

        _bindingDescriptions = vector<VkVertexInputBindingDescription>();
        vector<VertexAttributeInfo> vertexAttributesBindings = mesh->VertexInfo();
        vector<VertexBindingInfo> vertexBindings = mesh->GetVertexBindingInfo();
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

    void VulkanMeshData::AddMesh(IMesh* mesh, vector<VulkanBuffer>& vulkanBuffers)
    {
        _needRebuild = true;
        _meshes.push_back(mesh);
        if(_bufferCreator == nullptr) return;
        _perObjectBuffers.insert({mesh, vulkanBuffers});
        const vector<VulkanBuffer> buffers = PerObjectBuffersInfo(mesh);
        _bufferCreator->AddMesh(mesh, buffers);
    }

    bool VulkanMeshData::MultipleMeshes() const noexcept { return _meshes.size() > 1; }

    bool VulkanMeshData::ContainsMesh(IMesh *mesh)
    {
        return std::find(_meshes.begin(), _meshes.end(), mesh) != _meshes.end();
    }

    void VulkanMeshData::RemoveMesh(IMesh* mesh)
    {
        _needRebuild = true;
        _meshes.erase(std::find(_meshes.begin(), _meshes.end(), mesh));
        _bufferCreator->RemoveMesh(mesh);
        _perObjectBuffers.erase(mesh);
    }

    vector<IMesh*>& VulkanMeshData::Meshes() noexcept
    {
        return _meshes;
    }

    vector<VulkanBuffer>& VulkanMeshData::Buffers() const noexcept
    {
        return _buffers;
    }

    vector<VulkanImage>& VulkanMeshData::Images() const noexcept {
        return _images;
    }

    vector<VulkanBuffer>& VulkanMeshData::PerObjectBuffersInfo()
    {
        return _perObjectBuffers.at(*_meshes.begin());
    }

    vector<VulkanBuffer>& VulkanMeshData::PerObjectBuffersInfo(IMesh* mesh)
    {
        return _perObjectBuffers.at(mesh);
    }

    void VulkanMeshData::SetBufferRecreateEventListener(IVulkanRenderMeshBufferCreator* bufferCreator)
    {
        _bufferCreator = bufferCreator;
    }

    bool VulkanMeshData::ShouldCombine(IMesh *mesh) const
    {
        bool sameShaders = true;
        map<ShaderType, IShader> shaders = _meshes[0]->Shaders();
        map<ShaderType, IShader> meshShaders = mesh->Shaders();

        if (shaders.size() != meshShaders.size())
            return false;
        const bool isBothSameStaticType = _meshes[0]->IsStatic() && mesh->IsStatic();
        for (auto &[shaderType, shader] : shaders)
        {
            if (const bool containsSameShader = meshShaders.count(shaderType) != 0; !containsSameShader)
            {
                sameShaders = false;
                break;
            }
            if (const bool sameShaderData = meshShaders.at(shaderType).ShaderData() == shader.ShaderData(); !sameShaderData)
            {
                sameShaders = false;
                break;
            }
        }

        return sameShaders && isBothSameStaticType;
    }
}