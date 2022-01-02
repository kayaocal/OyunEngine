#ifndef OYUN_SERIALIZATION_SUBSYSTEM_H__
#define OYUN_SERIALIZATION_SUBSYSTEM_H__

#include "Subsystems/EngineSubsytem.h"
#include <string>
#include <map>

namespace Oyun
{
	class BaseClass;
	class BaseStaticClass;

	

	class OYUN_API SerializationSubsystem : public EngineSubsytem<SerializationSubsystem>
	{
		SerializationSubsystem();
		~SerializationSubsystem();
		std::map<std::string, BaseStaticClass*> StaticClasses;


	public:

		static SerializationSubsystem* system;

		static SerializationSubsystem* GetPtr();
		static SerializationSubsystem& Get();
		static SerializationSubsystem& Instantiate();

	
		virtual void StartUp() override;
		virtual void ShutDown() override;

		void Assign(std::string str, BaseStaticClass* base);
		BaseClass* ObjectFactory(const std::string& key);
	};

}

#endif //OYUN_SERIALIZATION_SUBSYSTEM_H__