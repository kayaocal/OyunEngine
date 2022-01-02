#ifndef OYUN_MATERIAL_H__
#define OYUN_MATERIAL_H__

#include <map>
#include <string>

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

namespace Oyun
{
	class Shader;
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

	extern const char* TextureTypeNames[];
	struct OYUN_API Material
	{
		Material();

		std::map<struct Texture*, MaterialTextureType> textures;


		void SetShader(Shader*);

		Shader* GetShader() const;

		void ApplyTexturesToShader() const;

		void UseShader();

		void ApplyShaderMatrix(float* view, float* proj, float* transform);
	private:
		Shader* mShader;

	};

}

#endif //OYUN_MATERIAL_H__