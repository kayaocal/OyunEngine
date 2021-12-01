#include "Material.h"
#include "Shader.h"
#include "glad/glad.h"
#include "Texture.h"
#include <cassert>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

Oyun::Material::Material()
	:mShader(nullptr)
{
	
}

void Oyun::Material::SetShader(Shader* shd)
{
	mShader = shd;
}

Oyun::Shader* Oyun::Material::GetShader() const
{
	return mShader;
}

void Oyun::Material::ApplyTexturesToShader() const
{
	assert(mShader != nullptr);
	int counter[static_cast<int>(MaterialTextureType::MAX)] = { 0 };

	auto iterator = textures.begin();
	int i = 0;
	while (iterator != textures.end())
	{
		int textureType = static_cast<int>(iterator->second);
		std::string name{ Oyun::TextureTypeNames[textureType] };
		name = name + std::to_string(counter[++textureType]);

		Oyun::Texture* tex = iterator->first;

		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding

		// now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(mShader->ProgramId, name.c_str()), i);
		glBindTexture(GL_TEXTURE_2D, tex->id);

		iterator++;
		i++;
	}
}

void Oyun::Material::UseShader()
{
	assert(mShader != nullptr);
	glUseProgram(mShader->ProgramId);
}

void Oyun::Material::ApplyShaderMatrix(float* view, float* proj, float* transform)
{
    unsigned int modelLoc = glGetUniformLocation(mShader->ProgramId, "model");
    unsigned int viewLoc = glGetUniformLocation(mShader->ProgramId, "view");
    unsigned int projLoc = glGetUniformLocation(mShader->ProgramId, "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, proj);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, transform);
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