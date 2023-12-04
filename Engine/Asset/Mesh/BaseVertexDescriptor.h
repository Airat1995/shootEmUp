#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "IVertexDescriptor.h"

class BaseVertexDescriptor : public IVertexDescriptor<VertexData>
{
public:
	BaseVertexDescriptor(VertexData& vertexData) : _vertexData(vertexData)
	{
		BaseVertexDescriptor::FillVertexInfo();
	}

	void FillVertexInfo() override
	{
		_vertexInfo = new vector<VertexAttributeInfo>();
		VertexAttributeInfo position{};
		position.Location = 0;
		position.Offset = 0;
		position.Format = Format::Vector4F;
		_vertexInfo->push_back(position);

		_bindingInfo = new vector<VertexBindingInfo>();
		VertexBindingInfo firstBindingInfo{};
		firstBindingInfo.BindId = 0;
		firstBindingInfo.Size = sizeof(VertexData);
		firstBindingInfo.Instanced = false;
		_bindingInfo->push_back(firstBindingInfo);
	}

	vector<VertexAttributeInfo>& GetVertexInfo() override
	{
		return *_vertexInfo;
	}

	vector<VertexBindingInfo>& GetBindingInfo() override
	{
		return *_bindingInfo;
	}

	int VertexSize() override
	{
		return sizeof(VertexData);
	}

	VertexData& GetVertexData() override
	{
		return _vertexData;
	}

	glm::vec4 VertexPosition() override
	{
		return vec4(_vertexData.position.x, _vertexData.position.y, _vertexData.position.z, _vertexData.position.w);
	}

protected:
	VertexData& _vertexData;

	vector<VertexAttributeInfo>* _vertexInfo = nullptr;

	vector<VertexBindingInfo>* _bindingInfo = nullptr;
};
