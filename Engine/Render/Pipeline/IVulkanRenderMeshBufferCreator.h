#pragma once
#include "Asset/Mesh/IMesh.h"
#include "Render/Buffer/VulkanBuffer.h"

class IVulkanRenderMeshBufferCreator
{
public:
	virtual void AddMesh(IMesh* mesh, vector<VulkanBuffer> perObjectBuffers) = 0;
};
