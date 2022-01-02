#include "Subsystems/SerializationSubsystem.h"
#include "OyunCore.h"
#include <assert.h>

namespace Oyun
{

	SerializationSubsystem* SerializationSubsystem::system = nullptr;


	SerializationSubsystem::SerializationSubsystem()
		:EngineSubsytem()
	{
		std::cout<<"SerializationSubsystem";
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
		std::cout<<"inserting 0.." <<str<<std::endl;
		if(StaticClasses.size() > 0)
		{
			auto it = StaticClasses.find(str);
			std::cout<<"inserting 1.." <<str<<std::endl;
			assert(it == StaticClasses.end(), "This class already assigned! Maybe you duplicate code!");
			
		}
		std::cout<<"inserting.."<<std::endl;
		StaticClasses.insert(std::pair<std::string, BaseStaticClass*>(str, base));
	}

	BaseClass* SerializationSubsystem::ObjectFactory(const std::string& key)
	{
		auto it = StaticClasses.find(key);
		assert(it != StaticClasses.end(), "Cant find this class in StaticClasses. Maybe you forgot to add INIT_CLASS");
		return it->second->Instantiator();
	}

}