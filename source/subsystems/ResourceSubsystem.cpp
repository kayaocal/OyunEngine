#include <cassert>
#include "subsystems/ResourceSubsystem.h"
#include "subsystems/LogSubsystem.h"
#include "ModelStore.h"

#include "lookup3.h"
#include "Texture.h"

namespace Oyun
{
	ResourceSubsystem* ResourceSubsystem::system = nullptr;
	

	ResourceSubsystem::ResourceSubsystem()
		:EngineSubsytem()
	{
	}

	ResourceSubsystem::~ResourceSubsystem()
	{
		system = nullptr;
	}

	ResourceSubsystem* ResourceSubsystem::GetPtr()
	{
		return system;
	}

	ResourceSubsystem& ResourceSubsystem::Get()
	{
		return *system;
	}

	ResourceSubsystem& ResourceSubsystem::Instantiate()
	{
		assert(system == nullptr);
		system = new ResourceSubsystem();
		return *system;
	}


	void ResourceSubsystem::StartUp()
	{
		LOG << "ResourceSubsystem Startup" << END;

		mTextureStore = std::make_unique<TextureStore>();
		mModelStore = std::make_unique<ModelStore>();
	}

	void ResourceSubsystem::ShutDown()
	{
		LOG << "ResourceSubsystem Shutdown" << END;
		delete this;
	}


	Texture* ResourceSubsystem::LoadTexture(const char* path)
	{
		return mTextureStore->Load(path, GetHash(path));
	}

	Texture* ResourceSubsystem::GetTexture(const char* path)
	{
		return mTextureStore->GetTexture(GetHash(path));
	}

	Texture* ResourceSubsystem::GetTexture(uint32_t hash)
	{
		return mTextureStore->GetTexture(hash);
	}

	Model* ResourceSubsystem::LoadModel(const char* path)
	{
		return mModelStore->Load(path, GetHash(path));
	}

	uint32_t ResourceSubsystem::GetHash(const char* chr)
	{
		uint32_t hash = hashlittle(chr, strlen(chr), 0);
		return hash;
	}

	uint32_t ResourceSubsystem::GetHash(const std::string& str)
	{
		uint32_t hash = hashlittle(str.c_str(), str.length(), 0);
		return hash;
	}
}
