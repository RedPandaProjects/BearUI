#pragma once
namespace BearUIVertexManager
{
#pragma pack(push,4)

	struct Default
	{
		BearVector2<float> position;
		BearVector4<float> color;
		BearVector2<float> uv;
	};
	struct Color
	{
		BearVector2<float> position;
		BearVector4<float> color;
	};
#pragma pack(pop)
}