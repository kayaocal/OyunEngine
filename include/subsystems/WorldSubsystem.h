#ifndef OYUN_WORLD_SUBSYSTEM_H__
#define OYUN_WORLD_SUBSYSTEM_H__

#include "EngineSubsytem.h"

namespace Oyun
{
	class EngineExport WorldSubsystem : public EngineSubsytem<WorldSubsystem>
	{
		WorldSubsystem(int width, int height);
		~WorldSubsystem();


	public:

		static WorldSubsystem* system;

		static WorldSubsystem* GetPtr();
		static WorldSubsystem& Get();
		static WorldSubsystem& Instantiate(int width = 800, int height = 600);

		virtual void StartUp() override;
		virtual void ShutDown() override;

		

		


	};

}

#endif //OYUN_WORLD_SUBSYSTEM_H__