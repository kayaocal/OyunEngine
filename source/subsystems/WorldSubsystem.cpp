#include "subsystems/WorldSubsystem.h"
#include <cassert>
#include "subsystems\LogSubsystem.h"

namespace Oyun
{
	WorldSubsystem* WorldSubsystem::system = nullptr;

	WorldSubsystem::WorldSubsystem(int width, int height)
		:EngineSubsytem()
	{
	}

	WorldSubsystem::~WorldSubsystem()
	{
		system = nullptr;
	}

	WorldSubsystem* WorldSubsystem::GetPtr()
	{
		return system;
	}

	WorldSubsystem& WorldSubsystem::Get()
	{
		return *system;
	}

	WorldSubsystem& WorldSubsystem::Instantiate(int width, int height)
	{
		assert(system == nullptr);
		system = new WorldSubsystem(width, height);
		return *system;
	}


	void WorldSubsystem::StartUp()
	{
		LOG << "WorldSubsystem Startup" << END;

	}

	void WorldSubsystem::ShutDown()
	{
		LOG << "WorldSubsystem Shutdown" << END;
		delete this;
	}
}
