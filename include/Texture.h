#pragma once
#include <string>
#include <map>
#define EngineExport   __declspec( dllexport )

namespace Engine
{

	struct EngineExport Texture
	{
	public:
		unsigned char* Data;
		int Width;
		int Height;
		int NrChannels;

		unsigned int Id;
		std::string Path;

		Texture(const std::string& path, int width, int height, int nrChannel, unsigned char* data);
		~Texture();
	};


	class EngineExport TextureStore
	{
	private:
		TextureStore();
		std::map<std::string, Texture*> _TextureMap;

	public:

		Texture* Load(const char* path);

		Texture* GetTextureByName(const char* path);

		static TextureStore& Get();
	};
}
