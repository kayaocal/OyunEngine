#ifndef OYUN_RESOURCE_SUBSYSTEM_H__
#define OYUN_RESOURCE_SUBSYSTEM_H__

#include "EngineSubsytem.h"
#include <string>
#include <memory>

namespace Oyun
{

	class Texture;
	class TextureStore;

	class EngineExport ResourceSubsystem : public EngineSubsytem<ResourceSubsystem>
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

	private:
		std::unique_ptr<TextureStore> mTextureStore;

	};

}

#endif //OYUN_RESOURCE_SUBSYSTEM_H__