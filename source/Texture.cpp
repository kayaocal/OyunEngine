#include "..\include\Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>

namespace Oyun
{
	Texture::Texture(int width, int height)
		:width(width), height(height)
	{
		nrChannels = 3;

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	Texture::Texture(const std::string& path, int width, int height, int nrChannel, unsigned char* data)
	:width(width), height(height), nrChannels(nrChannel)
{
	GLenum format;
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

	Texture::~Texture()
	{
		glDeleteTextures(1, &id);
	}

	TextureStore& TextureStore::Get()
	{
		static TextureStore store;
		return store;
	}

	Texture* TextureStore::Load(const char* path)
	{
		Texture* tex = GetTextureByName(path);
		if (tex == nullptr)
		{
			int width, height, nrChannels;
			stbi_set_flip_vertically_on_load(true);
			unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
			if (data == nullptr)
			{
				std::cout << "Texture failed to load at path : "<< path << std::endl;
				return nullptr;
			}

			std::cout << "Texture succesfull to load at path : "<< path << std::endl;
			tex = new Texture{ path, width, height, nrChannels, data };
			stbi_image_free(data);
			_TextureMap.insert(std::pair<std::string, Texture*>(path, tex));
			return tex;
		}

		return tex;
	}

	Texture* TextureStore::GetTextureByName(const char* path)
{
	auto program = _TextureMap.find(path);
	if (program != _TextureMap.end())
	{
		return program->second;
	}

	return nullptr;
}

	TextureStore::TextureStore()
	{

	}
}
