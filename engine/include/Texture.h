#ifndef OYUN_TEXTURE_H__
#define OYUN_TEXTURE_H__

#include <string>
#include <map>

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

namespace Oyun
{

	struct OYUN_API Texture
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


	class OYUN_API TextureStore
	{
		std::map<uint32_t, Texture*> mTextureMap;
	public:
		TextureStore();

		Texture* Load(const char* path, uint32_t hash);
		Texture* Load(const char* path,  unsigned char* buffer, size_t size, uint32_t hash);

		Texture* GetTextureByPath(const char* path);
		Texture* GetTexture(uint32_t hash);

		static TextureStore& Get();
	};
}

#endif //OYUN_TEXTURE_H__