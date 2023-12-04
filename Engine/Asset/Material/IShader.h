#pragma once
#include "Common/IO/FileReader.h"

enum class ShaderType
{
	Vertex = 0x00000001,
	TesselationControl = 0x00000002,
	TesselationEvaluation = 0x00000004,
	Geometry = 0x00000008,
	Fragment = 0x00000010,
	Compute = 0x00000020,
	Raygen = 0x00000100,
	AnyHit = 0x00000200,
	ClosetHit = 0x00000400,
	Mesh = 0x00000080,
};

class IShader
{
public:

	explicit IShader(string& location, string& name): _shaderLocation(location), _name(name)
	{
		FileReader reader = FileReader();
		_shaderData = reader.Read(location);		
	}

	vector<char>& ShaderData()
	{
		return _shaderData;
	}


	string& Name()
	{
		return _name;
	}

	string& ShaderLocation()
	{
		return _shaderLocation;
	}
	
protected:

	string _shaderLocation;

	string _name;

	vector<char> _shaderData;
};

