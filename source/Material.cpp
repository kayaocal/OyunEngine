#include "Material.h"
#include <iostream>

Oyun::Material::Material()
{
}

const char* Oyun::TextureTypeNames[] =
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