#pragma once

#include "Asset/Mesh/Mesh.h"

class MainDescriptorVertexDescriptor : public BaseVertexDescriptor {
public: 
	MainDescriptorVertexDescriptor() {
		_vertexInfo = vector<VertexAttributeInfo>();
		VertexAttributeInfo position{};
		position.Location = 0;
		position.Offset = 0;
		position.Format = Format::Vector4SF;
		_vertexInfo.push_back(position);


		_bindingInfo = vector<VertexBindingInfo>();
		VertexBindingInfo bindingInfo{};
		bindingInfo.BindId = 0;
		bindingInfo.Size = 16;
		bindingInfo.Instanced = false;
		_bindingInfo.push_back(bindingInfo);
	}
};