#pragma once

#define EngineExport   __declspec( dllexport )

class EngineExport Texture
{
public:
	unsigned char* Data;
	int Width;
	int Height;
	int NrChannels;

	Texture(const char* textureName);
	~Texture();
};