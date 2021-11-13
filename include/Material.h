#pragma once
#include <map>

#define EngineExport   __declspec( dllexport )

namespace Engine
{
	enum class MaterialTextureType
	{
		NONE = 0,
		DIFFUSE = 1,
		SPECULAR = 2,
		AMBIENT = 3,
		EMISSIVE = 4,
		HEIGHT = 5,
		NORMAL = 6,
		SHININESS = 7,
		OPACITY = 8,
		DISPLACEMENT = 9,
		LIGHTMAP = 10,
		REFLECTION = 11,
		BASE_COLOR = 12,
		NORMAL_CAMERA = 13,
		EMISSION_COLOR = 14,
		METALNESS = 15,
		DIFFUSE_ROUGHNESS = 16,
		AMBIENT_OCCLUSION = 17,
		MAX
	};

	static const char* TextureTypeNames[]
	{
		"none",
		"texture_diffuse",
		"texture_specular",
		"texture_ambient",
		"texture_emissive",
		"texture_height"
		"texture_normal",
		"texture_shininess",
		"texture_opacity",
		"texture_displacement",
		"texture_lightmap",
		"texture_reflection",
		"texture_base_color",
		"texture_normal_camera",
		"texture_emission_color",
		"texture_metalness",
		"texture_diffuse_roughness",
		"texture_ambient_occlusion"
	};


	struct EngineExport Material
	{
		Material();

		std::map<struct Texture*, MaterialTextureType> Textures;
	};

}