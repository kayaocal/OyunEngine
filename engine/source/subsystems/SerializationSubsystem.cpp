#include "subsystems/SerializationSubsystem.h"
#include <map>
#include "OyunCore.h"
#include <assert.h>

namespace Oyun
{
	std::map<std::string, BaseStaticClass*> StaticClassMap;

	SerializationSubsystem* SerializationSubsystem::system = nullptr;


	SerializationSubsystem::SerializationSubsystem()
		:EngineSubsytem()
	{
	}

	SerializationSubsystem::~SerializationSubsystem()
	{
	}

	SerializationSubsystem* SerializationSubsystem::GetPtr()
	{
		if (system == nullptr)
		{
			system = new SerializationSubsystem();
		}

		return system;
	}

	SerializationSubsystem& SerializationSubsystem::Get()
	{
		if (system == nullptr)
		{
			system = new SerializationSubsystem();
		}

		return *system;
	}

	SerializationSubsystem& SerializationSubsystem::Instantiate()
	{
		if (system == nullptr)
		{
			system = new SerializationSubsystem();
		}

		return *system;
	}

	void SerializationSubsystem::StartUp()
	{
	}

	void SerializationSubsystem::ShutDown()
	{
	}

	void SerializationSubsystem::Assign(std::string str, BaseStaticClass* base)
	{
		auto it = StaticClassMap.find(str);
		assert(it == StaticClassMap.end(), "This class already assigned! Maybe you duplicate code!");
		
		StaticClassMap.insert(std::pair<std::string, BaseStaticClass*>(str, base));
	}

	BaseClass* SerializationSubsystem::ObjectFactory(const std::string& key)
	{
		auto it = StaticClassMap.find(key);
		assert(it != StaticClassMap.end(), "Cant find this class in StaticClassMap. Maybe you forgot to add INIT_CLASS");
		return it->second->Instantiator();
	}

}