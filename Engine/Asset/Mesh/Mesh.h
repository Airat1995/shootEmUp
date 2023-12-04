
#pragma once
#include <utility>

#include "IMesh.h"
#include "IVertexDescriptor.h"

template
<
	typename Vertex,
	typename VertexDataT,
	typename = enable_if<is_base_of_v<VertexData, VertexDataT>>,
	typename = enable_if<is_base_of_v<IVertexDescriptor<VertexDataT>, Vertex>>
>
class Mesh : public IMesh
{
public:
	Mesh(const Mesh&) = default;               // Copy constructor
	Mesh(Mesh&&) = default;                    // Move constructor
	Mesh& operator=(const Mesh&) = delete;  // Copy assignment operator
	Mesh& operator=(Mesh&&) = delete;       // Move assignment operator
	virtual ~Mesh() = default;

	Mesh(vector<Vertex>& vertices, IMaterial* material) : IMesh(), _vertices(vertices), _material(material)
	{
		FillVertexDatas();
	}

	Mesh(vector<Vertex>& vertices, std::vector<uint16_t> indexes, IMaterial* material) : IMesh(), _vertices(vertices),
	                                                            _indexes(std::move(indexes)), _material(material), _indexed(true)
	{
		FillVertexDatas();
	}

	Mesh(): IMesh(), _material(nullptr)
	{
		_vertices = vector<Vertex>();
	}

	void FillVertexDatas()
	{
		_vertexDatas = vector<VertexDataT>();
		for (size_t index = 0; index < _vertices.size(); ++index)
		{
			_vertexDatas.push_back(_vertices[index].GetVertexData());
		}
	}

	const void* VerticesData() override
	{
		return _vertexDatas.data();
	}

	int VertexCount() override
	{
		return _vertices.size();
	}

	void const* IndicesData() override
	{
		return _indexes.data();
	}

	int RequiredBufferSize() override
	{
		return _vertices[0].VertexSize() * _vertexDatas.size();
	}

	int VertexSize() override
	{
		return sizeof(Vertex);
	}

	int IndexSize() override
	{
		return _indexes.size();
	}

	vector<VertexAttributeInfo> VertexInfo() override
	{
		return _vertices.at(0).GetVertexInfo();
	}

	vector<VertexBindingInfo> GetVertexBindingInfo() override
	{
		return _vertices.at(0).GetBindingInfo();
	}

	map<ShaderType, IShader>& Shaders() override
	{
		return _material->MaterialShaders();
	}

	IMaterial* Material() override
	{
		return _material;
	}

	void AddPerObjectBuffer(IBuffer* buffer) override
	{
		_perObjectBuffers.push_back(buffer);
	}

	vector<IBuffer*>& PerObjectBuffers() override
	{
		return _perObjectBuffers;
	}

	vector<vec4>* VertexPositions() override
	{
		if(_positions == nullptr)
		{
			_positions = new vector<vec4>();
			for (size_t vertexIndex = 0; vertexIndex < _vertices.size(); vertexIndex++)
			{
				_positions->push_back(_vertices.at(vertexIndex).VertexPosition());
			}
		}
				
		return _positions;
	}
	
protected:

	vector<Vertex> _vertices;

	vector<uint16_t> _indexes;

	vector<IBuffer*> _perObjectBuffers;

	vector<vec4>* _positions = nullptr;

private:
	bool _indexed = false;

	vector<VertexDataT> _vertexDatas;

	IMaterial* _material;
};

