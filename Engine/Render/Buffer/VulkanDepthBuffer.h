#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include <stdexcept>

#include "IDepthBuffer.h"
#include "Render/AssetWrapper/VulkanImage.h"

class VulkanDepthBuffer :
    public IDepthBuffer
{
public:
	VulkanDepthBuffer(VkDevice device, VkPhysicalDevice gpu, int width, int height, bool useAsSampler = false);

	void Destroy();

	VkFormat Format();

	VkImageView View();

protected:

	VkImage _image;

	VkDeviceMemory _memory;

	VkImageView _view;

	VkDevice _device;

	VkPhysicalDevice _gpu;

	VkAttachmentDescription _depthAttachment;

	VkFormat _depthFormat;

	int _width;

	int _height;

	bool _useAsSampler;

private:
	VkFormat FindSupportedFormat(std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	static bool HasStencilComponent(VkFormat format);

	void CreateImage(VkFormat format);

	void BindImage();
	
	void CreateView(VkFormat format);
};

