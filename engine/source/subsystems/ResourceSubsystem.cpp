#include <cassert>
#include "subsystems/ResourceSubsystem.h"
#include "subsystems/LogSubsystem.h"
#include "ModelStore.h"
#include "Shader.h"
#include "lookup3.h"
#include "Texture.h"
#include "FileIO.h"

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
		mShaderStore = std::make_unique<ShaderStore>();

	}

	void ResourceSubsystem::ShutDown()
	{
		LOG << "ResourceSubsystem Shutdown" << END;
		delete this;
	}


	Texture* ResourceSubsystem::LoadTexture(const char* path)
	{
		uint32_t hash = GetHash(path);
		Texture* texture = mTextureStore->GetTexture(hash);
		if (texture != nullptr)
		{
			return texture;
		}

		size_t size = 0;
		unsigned char* buffer = Oyun::ReadFile<unsigned char>(path, &size);
		return mTextureStore->Load(path, buffer, size, hash);
		delete[] buffer;
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
		uint32_t hash = GetHash(path);
		Model* model = mModelStore->GetModel(hash);
		if (model != nullptr)
		{
			return model;
		}

		size_t size = 0;
		char* buffer = Oyun::ReadFile<char>(path, &size);
		model = mModelStore->Load(path, buffer, size, hash);
		delete[] buffer;
		return model;
	}

	Shader* ResourceSubsystem::LoadShader(const char* path, const char* vertexPath, const char* fragPath)
	{
		uint32_t shaderCode = GetHash(path);
		Shader* shader = mShaderStore->GetShader(shaderCode);
		
		if (shader != nullptr)
		{
			return shader;
		}

		size_t vertexSize = 0;
		char* vertexShaderBuffer = Oyun::ReadFile<char>(vertexPath, &vertexSize);
		
		size_t fragmentSize = 0;
		char* fragmentShaderBuffer = Oyun::ReadFile<char>(fragPath, &fragmentSize);
		shader = mShaderStore->CompileShader(shaderCode, vertexShaderBuffer, fragmentShaderBuffer);

		delete[] fragmentShaderBuffer;
		delete[] vertexShaderBuffer;
		return shader;
	}

	Shader* ResourceSubsystem::LoadShader(const char* path)
	{
		return nullptr;
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
