#include "..\include\Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <iostream>

namespace Engine
{
	Texture::Texture(const std::string& path, int width, int height, int nrChannel, unsigned char* data)
	:Width(width), Height(height), NrChannels(nrChannel), Data(data)
{
	GLenum format;
	if (NrChannels == 1)
		format = GL_RED;
	else if (NrChannels == 3)
		format = GL_RGB;
	else if (NrChannels == 4)
		format = GL_RGBA;

	glGenTextures(1, &Id);
	glBindTexture(GL_TEXTURE_2D, Id);
	glTexImage2D(GL_TEXTURE_2D, 0, format, Width, Height, 0, format, GL_UNSIGNED_BYTE, Data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

	Texture::~Texture()
	{
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
