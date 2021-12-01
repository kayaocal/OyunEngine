#ifndef OYUN_RESOURCE_SUBSYSTEM_H__
#define OYUN_RESOURCE_SUBSYSTEM_H__

#include "EngineSubsytem.h"
#include <string>
#include <memory>

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

namespace Oyun
{
	class Texture;
	class TextureStore;
	class Model;
	class ModelStore;

	class OYUN_API ResourceSubsystem : public EngineSubsytem<ResourceSubsystem>
	{
		ResourceSubsystem();
		~ResourceSubsystem();

	public:

		static ResourceSubsystem* system;

		static ResourceSubsystem* GetPtr();
		static ResourceSubsystem& Get();
		static ResourceSubsystem& Instantiate();

		virtual void StartUp() override;
		virtual void ShutDown() override;

		uint32_t GetHash(const std::string& str);
		uint32_t GetHash(const char* chr);

		Texture* LoadTexture(const char* path);
		Texture* GetTexture(const char* path);
		Texture* GetTexture(uint32_t hash);

		Model* LoadModel(const char* path);

	private:
		std::unique_ptr<TextureStore> mTextureStore;
		std::unique_ptr<ModelStore> mModelStore;
	};

}

#endif //OYUN_RESOURCE_SUBSYSTEM_H__