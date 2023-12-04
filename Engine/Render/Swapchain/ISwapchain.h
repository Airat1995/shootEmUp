#pragma once
#include <vector>
#include "vulkan/vulkan.h"
#include <vector>
#include <iostream>

#include "SwapchainBuffer.h"

class ISwapchain
{
public:
	ISwapchain(VkDevice device, VkExtent2D swapchainExtent, VkSurfaceCapabilitiesKHR surfaceCapabilities,
	           VkSurfaceKHR surface, std::vector<VkPhysicalDevice>& gpus, uint32_t graphicsQueueFamilyIndex,
	           uint32_t presentQueueFamilyIndex);

	VkSwapchainCreateInfoKHR SwapchainInfo();

	std::vector<SwapchainBuffer>& SwapchainBuffers();

	~ISwapchain();

	VkSemaphore ImageAvailableSemaphore();

	VkSemaphore RenderFinishSemaphore();

	VkSwapchainKHR Swapchain();
		
	void RecreateSwapchain();

protected:

	void DestroySwapchain();

	void CreateSwapchainAndImages(VkDevice device, VkSwapchainCreateInfoKHR swapchainInfo);

	static VkSurfaceTransformFlagBitsKHR GetPresentMode(VkSurfaceCapabilitiesKHR surfaceCapabilities);

	static VkCompositeAlphaFlagBitsKHR GetCompositeAlpha(VkSurfaceCapabilitiesKHR surfaceCapabilities);

	static VkFormat GetSupportedFormat(std::vector<VkPhysicalDevice>& gpus, VkSurfaceKHR surface);

	void CreateSemaphore();

	std::vector<SwapchainBuffer> _swapchainBuffers;

	VkSwapchainKHR _swapChain{};

	VkSwapchainKHR _swapChainRebuild{};

	VkSwapchainCreateInfoKHR _swapchainInfo = {};

	VkDevice _device;

	VkSemaphore _imageAvailableSemaphore{};

	VkSemaphore _renderFinishSemaphore{};
	
};

