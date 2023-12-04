#pragma once
#include "IShadowmap.h"
#include "Render/Buffer/VulkanDepthBuffer.h"
#include "Render/Pipeline/VulkanPipeline.h"
#include "Render/Render/VulkanRenderpass.h"
#include "Asset/Mesh/BaseVertexDescriptor.h"
#include "Asset/Mesh/IMesh.h"
#include "Render/Buffer/ShadowmapBuffer.h"
#include "Camera/CameraObject.h"
#include "Render/Swapchain/ISwapchain.h"
#include "Render/Buffer/VulkanFramebuffer.h"

class VulkanOmniShadowmap : public IShadowmap
{
public:

	VulkanOmniShadowmap(vec4* lightPosition, CameraObject* currentCamera, vector<VulkanMeshData*>* meshDataCollection, 
		VulkanCommandPool* commandPool, ISwapchain* swapchain, VkDevice device, VkPhysicalDevice gpu, int drawQueue, int presentQueue, int binding, int graphicsFamilyIndex, int width, int height);

	void Draw(ICommandBuffer* commandBuffer, int index) override;

	void Update(int indexFace);

	void Submit(int index);
		
protected:

	BufferlessVulkanImage* _image;

	VulkanDepthBuffer* _depthBuffer;

	VulkanRenderpass* _offscreenRenderpass;

	VulkanPipeline* _pipeline;
	
	ShadowmapBuffer _shadowmapBuffer;

	vec4* _lightPosition;

	CameraObject* _currentCamera;
	ISwapchain* _swapchain;

private:
		
	void CreateVulkanPipeline(IMesh* mesh);

	static void SetImageLayout(VkCommandBuffer cmdbuffer, VkImage image, VkImageLayout oldImageLayout,
	                           VkImageLayout newImageLayout, VkImageSubresourceRange subresourceRange,
	                           VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask);


	VulkanFramebuffer* _frameBuffer;

	VkDevice _device;

	VkPhysicalDevice _gpu;

	int _drawQueue;
	
	int _presentQueue;

	int _indexFace;
#pragma region constants

	string _vertexLoc = "C:\\Users\\airat\\OneDrive\\Documents\\DRawEngine\\omniShadowmapVert.spv";

	string _fragmentLoc = "C:\\Users\\airat\\OneDrive\\Documents\\DRawEngine\\omniShadowmapFrag.spv";

	string _shaderName = "main";
#pragma 
};
