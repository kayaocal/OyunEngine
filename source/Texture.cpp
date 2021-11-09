#include "..\include\Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* textureName)
{
	stbi_set_flip_vertically_on_load(true);
	Data = stbi_load("container.jpg", &Width, &Height, &NrChannels, 0);
}

Texture::~Texture()
{
	stbi_image_free(Data);
}
