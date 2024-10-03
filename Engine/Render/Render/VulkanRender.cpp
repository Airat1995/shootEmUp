#include "VulkanRender.h"

namespace Engine::Render::Render
{
    VulkanRender::VulkanRender() {}

    void VulkanRender::Init(vector<const char *> *extensions)
    {
        const VkApplicationInfo appInfo = CreateAppInfo();
        std::vector<const char *> layers = GetLayers();
#if ENGINE_DEBUG
        extensions->push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        extensions->push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
        extensions->push_back("VK_EXT_debug_report");
        extensions->push_back("VK_KHR_get_physical_device_properties2");
        // extensions->push_back("GL_KHR_vulkan_glsl ");
        if (filesystem::exists(DEBUG_FILENAME.c_str()))
            remove(DEBUG_FILENAME.c_str());
#endif
        CreateInstanceCreateInfo(appInfo, extensions, &layers);
        EnumeratePhysicalDevices();
        SetupDebugMessenger();
    }

    VulkanRender::~VulkanRender()
    {
        vkDestroySurfaceKHR(_instance, _surface, nullptr);
        vkDestroyDevice(_device, nullptr);
        vkDestroyInstance(_instance, nullptr);
    }

    void VulkanRender::InitSurface(int screenWidth, int screenHeight)
    {
        InitDevice();
        CreateCommandPool(_queueInfo.queueFamilyIndex);
        VkSurfaceCapabilitiesKHR surfaceCapabilities;
        VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_gpus.at(0), _surface, &surfaceCapabilities);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("unable to get surface capabilities!");
        }

        uint32_t presentModeCount;
        result = vkGetPhysicalDeviceSurfacePresentModesKHR(_gpus.at(0), _surface, &presentModeCount, nullptr);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("unable to get physical device present modes count!");
        }

        VkPresentModeKHR *presentModes = new VkPresentModeKHR[presentModeCount];
        result = vkGetPhysicalDeviceSurfacePresentModesKHR(_gpus.at(0), _surface, &presentModeCount, presentModes);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("unable to get physical device present modes!");
        }

        if (surfaceCapabilities.currentExtent.width == INCORRECT_WIDTH)
        {
            _swapchainExtent.width = screenWidth;
            _swapchainExtent.height = screenHeight;

            if (_swapchainExtent.width < surfaceCapabilities.minImageExtent.width)
                _swapchainExtent.width = surfaceCapabilities.minImageExtent.width;
            else if (_swapchainExtent.width > surfaceCapabilities.maxImageExtent.width)
                _swapchainExtent.width = surfaceCapabilities.maxImageExtent.width;

            if (_swapchainExtent.height < surfaceCapabilities.minImageExtent.height)
                _swapchainExtent.height = surfaceCapabilities.minImageExtent.height;
            else if (_swapchainExtent.height > surfaceCapabilities.maxImageExtent.height)
                _swapchainExtent.height = surfaceCapabilities.maxImageExtent.height;
        }
        else
            _swapchainExtent = surfaceCapabilities.currentExtent;
        _width = _swapchainExtent.width;
        _height = _swapchainExtent.height;
        _swapchain = new ISwapchain(_device, _swapchainExtent, surfaceCapabilities, _surface, _gpus,
                                    _graphicsQueueFamilyIndex, _presentQueueFamilyIndex);
        for (auto swapchain : _swapchain->SwapchainBuffers())
            _commandPool->AddCommandBuffer();

        _depthBuffer = new VulkanDepthBuffer(_device, _gpus[0], _width, _height);
        _renderpass = new VulkanRenderpass(_device, _swapchain->SwapchainInfo().imageFormat, _depthBuffer->Format());

        // First init with empty pipelines
        _pipelines = map<int, vector<VulkanPipeline*>>();


        _framebuffer = new VulkanFramebuffer(_device, _graphicsQueueFamilyIndex, _presentQueueFamilyIndex, *_swapchain,
                                             *_renderpass, *_commandPool, *_depthBuffer);
        vector<VulkanMeshData> meshData = vector<VulkanMeshData>();

        _frameBuffersCount = _framebuffer->FramebufferCount();
        _currentDrawFramebuffer = 0;
    }

    VkInstance VulkanRender::GetInstance() const { return _instance; }

    VkSurfaceKHR *VulkanRender::GetSurface() { return &_surface; }

    void VulkanRender::DrawFrame() {
        VulkanCommandBuffer vulkanCommandBuffer = _commandPool->CommandBuffer(_currentDrawFramebuffer);
        VkFramebuffer framebuffer = _framebuffer->Framebuffer(_currentDrawFramebuffer);
        VkCommandBuffer commandbuffer = vulkanCommandBuffer.CommandBuffer();
        vulkanCommandBuffer.BeginCommandBuffer();
                
        _renderpass->BeginRenderPass(_width, _height, framebuffer, commandbuffer);

        for (auto &&renderQueuePipelines : _pipelines) {
            for (auto &&renderPipeline : renderQueuePipelines.second) {
                renderPipeline->BindPipeline(commandbuffer);
                renderPipeline->BuildCommandbuffer(commandbuffer);
            }
        }

        _renderpass->EndRenderPass(commandbuffer);
        vulkanCommandBuffer.EndCommandBuffer();
        _framebuffer->SubmitFramebuffer(_currentDrawFramebuffer);
        vkDeviceWaitIdle(_device);
        _commandPool->ResetCommandBuffers();
        _currentDrawFramebuffer++;
        _currentDrawFramebuffer = _currentDrawFramebuffer % _frameBuffersCount;
    }

    void VulkanRender::AddMesh(IMesh *mesh)
    {
        VulkanMeshData meshData {mesh, _device, _gpus[0], _commandPool, _graphicsQueueFamilyIndex};
        uint32_t shaderHash = 0;
        auto& meshShaders = mesh->Shaders();
        for (auto&& shader: meshShaders)
        {
            shaderHash += shader.second.GetResourceId();
        }

        int renderQueue = mesh->Material()->GetRenderQueue();
        auto pipelineIter = _pipelines.find(renderQueue);
        
        bool foundRenderQueue = false;
        for (auto &&pipelineInfo : _pipelines)
        {
            if(pipelineInfo.first != renderQueue)
            {
                continue;
            }
            for (auto &&pipeline : pipelineInfo.second)
            {
               if(pipeline->ShouldUseThisPipeline(meshData))
               {
                   pipeline->AddMesh(meshData);
                   foundRenderQueue = true;
                   break;
               }
            }

            if(foundRenderQueue)
            {
                break;
            }

            VulkanPipeline* pipeline = new VulkanPipeline(_device, _gpus[0], *_renderpass, meshData, _swapchain->SwapchainInfo().imageExtent);
            pipelineInfo.second.insert(pipelineInfo.second.end(), pipeline);
            pipeline->AddMesh(std::move(meshData));
            foundRenderQueue = true;
            break;
        }

        if(!foundRenderQueue)
        {
            vector<VulkanPipeline*> emptyPipelines;
            VulkanPipeline* pipeline = new VulkanPipeline(_device, _gpus[0], *_renderpass, meshData, _swapchain->SwapchainInfo().imageExtent);
            pipeline->AddMesh(std::move(meshData));
            emptyPipelines.insert(emptyPipelines.end(), pipeline);
           _pipelines.insert(pair(renderQueue, emptyPipelines));
        }
    }

    void VulkanRender::RemoveMesh(IMesh *mesh)
    {

        for (auto &&pipelineInfo : _pipelines)
        {
            for (auto &&pipeline : pipelineInfo.second)
            {
               if(pipeline->TryRemoveMesh(mesh))
               {
                    return;
               }
            }
            
        }
//        int foundIndex = -1;
//        for (int index = 0; index < _meshDataCollection.size(); index++)
//        {
//            if(!_meshDataCollection[index]->ContainsMesh(mesh)) continue;
//            foundIndex = index;
//            break;
//        }
//        if(foundIndex == -1) return;
//        _meshDataCollection[foundIndex]->RemoveMesh(mesh);
//        delete _meshDataCollection[foundIndex];
//        _meshDataCollection.erase(_meshDataCollection.begin() + foundIndex);
    }

    VkDevice &VulkanRender::Device() { return _device; }

    glm::uint32 VulkanRender::GraphicsQueueFamilyIndex() { return _graphicsQueueFamilyIndex; }

    uint32_t VulkanRender::PresentQueueFamilyIndex() { return _presentQueueFamilyIndex; }

    VkPhysicalDevice VulkanRender::Physical() { return _gpus[0]; }

    vector<const char *> VulkanRender::GetLayers()
    {
        std::vector<const char *> layers;
        layers.push_back("VK_LAYER_KHRONOS_validation");
        return layers;
    }

    VkApplicationInfo VulkanRender::CreateAppInfo()
    {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pNext = nullptr;
        appInfo.pApplicationName = "App example";
        appInfo.applicationVersion = 1;
        appInfo.pEngineName = "";
        appInfo.engineVersion = 1;
        appInfo.apiVersion = VK_API_VERSION_1_3;

        return appInfo;
    }

    void VulkanRender::CreateInstanceCreateInfo(VkApplicationInfo appInfo, vector<const char *> *extensions,
                                                vector<const char *> *layers)
    {
        VkInstanceCreateInfo instInfo = {};
        instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instInfo.pNext = nullptr;
        instInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
        instInfo.pApplicationInfo = &appInfo;
        instInfo.enabledExtensionCount = extensions->size();
        instInfo.ppEnabledExtensionNames = extensions->data();
        instInfo.enabledLayerCount = layers->size();
        instInfo.ppEnabledLayerNames = layers->data();
#if ENGINE_DEBUG
        VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;
        instInfo.pNext = static_cast<VkDebugUtilsMessengerCreateInfoEXT *>(&createInfo);
#else
        instInfo.enabledLayerCount = 0;
        instInfo.pNext = nullptr;
#endif

        const VkResult createResult = vkCreateInstance(&instInfo, nullptr, &_instance);
        if (createResult != VK_SUCCESS)
        {
            throw std::runtime_error("Unable to create vulkan instance");
        }
    }

    void VulkanRender::CreateCommandPool(int queueFamilyIndex)
    {
        _commandPool = new VulkanCommandPool(_device, queueFamilyIndex);
    }

    bool VulkanRender::IsDeviceSuitable(VkPhysicalDevice device)
    {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ||
            deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU;
    }

    void VulkanRender::EnumeratePhysicalDevices()
    {
        uint32_t gpu_count = 1;
        VkResult result = vkEnumeratePhysicalDevices(_instance, &gpu_count, nullptr);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Unable to enumerate physical devices!");
        }
        vector<VkPhysicalDevice> *suitableGpus = new vector<VkPhysicalDevice>(gpu_count);
        result = vkEnumeratePhysicalDevices(_instance, &gpu_count, suitableGpus->data());
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Unable to get physical devices!");
        }
        _gpus = vector<VkPhysicalDevice>();
        for (auto &suitableGpu : *suitableGpus)
        {
            if (IsDeviceSuitable(suitableGpu))
            {
                _gpus.push_back(suitableGpu);
            }
        }
    }

    VkBool32 *VulkanRender::GetQueuesSupportPresenting(uint32_t queueFamilyCount) const
    {
        auto pSupportsPresent = new VkBool32[queueFamilyCount];
        for (uint32_t i = 0; i < queueFamilyCount; i++)
        {
            vkGetPhysicalDeviceSurfaceSupportKHR(_gpus.at(0), i, _surface, &pSupportsPresent[i]);
        }
        return pSupportsPresent;
    }

    bool VulkanRender::GetGraphicsAndPresentQueue(uint32_t queueFamilyCount, vector<VkQueueFamilyProperties> queueProps)
    {
        VkBool32 *pSupportsPresent = new VkBool32[queueFamilyCount];
        for (uint32_t i = 0; i < queueFamilyCount; i++)
        {
            vkGetPhysicalDeviceSurfaceSupportKHR(_gpus.at(0), i, _surface, &pSupportsPresent[i]);
        }

        bool found = false;
        for (unsigned int i = 0; i < queueFamilyCount; i++)
        {
            if ((queueProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) == 0)
                continue;

            if (_graphicsQueueFamilyIndex == UINT32_MAX)
                _queueInfo.queueFamilyIndex = i;

            if (pSupportsPresent[i] == VK_TRUE)
            {
                _graphicsQueueFamilyIndex = i;
                _presentQueueFamilyIndex = i;
                break;
            }

            found = true;
            break;
        }
        return found;
    }

    void VulkanRender::SetupDebugMessenger()
    {
#ifndef ENGINE_DEBUG
        return;
#else
        VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = nullptr;
        createInfo.pNext = nullptr;
        createInfo.flags = 0;

        if (CreateDebugUtilsMessengerEXT(_instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to set up debug messenger!");
        }
#endif
    }

    void VulkanRender::InitDevice()
    {
        _queueInfo = {};

        uint32_t queueFamilyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(_gpus.at(0), &queueFamilyCount, nullptr);

        vector<VkQueueFamilyProperties> queueProps(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(_gpus.at(0), &queueFamilyCount, queueProps.data());

        bool found = GetGraphicsAndPresentQueue(queueFamilyCount, queueProps);

        float queue_priorities[1] = {0.0};
        _queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        _queueInfo.pNext = nullptr;
        _queueInfo.flags = 0;
        _queueInfo.queueCount = 1;
        _queueInfo.pQueuePriorities = queue_priorities;

        _extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
        _extensions.push_back("VK_KHR_portability_subset");

        VkDeviceCreateInfo device_info = {};
        device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        device_info.pNext = nullptr;
        device_info.flags = 0;
        device_info.queueCreateInfoCount = 1;
        device_info.pQueueCreateInfos = &_queueInfo;
        device_info.enabledExtensionCount = _extensions.size();
        device_info.ppEnabledExtensionNames = _extensions.data();
        device_info.pEnabledFeatures = nullptr;

        const VkResult result = vkCreateDevice(_gpus.at(0), &device_info, nullptr, &_device);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("Unable to create physical device!");
        }
    }
}
