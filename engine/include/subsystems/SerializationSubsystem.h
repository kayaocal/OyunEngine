#ifndef OYUN_SERIALIZATION_SUBSYSTEM_H__
#define OYUN_SERIALIZATION_SUBSYSTEM_H__

#include "EngineSubsytem.h"
#include <string>


namespace Oyun
{
	class BaseClass;
	class BaseStaticClass;

	

	class OYUN_API SerializationSubsystem : public EngineSubsytem<SerializationSubsystem>
	{
		SerializationSubsystem();
		~SerializationSubsystem();

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