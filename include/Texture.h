#ifndef OYUN_TEXTURE_H__
#define OYUN_TEXTURE_H__

#include <string>
#include <map>
#define EngineExport   __declspec( dllexport )

namespace Oyun
{

	struct EngineExport Texture
	{
	public:
		int width;
		int height;
		int nrChannels;

		unsigned int id;
		std::string path;

		Texture(int width, int height);
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

#endif //OYUN_TEXTURE_H__