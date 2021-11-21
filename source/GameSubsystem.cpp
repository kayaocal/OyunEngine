#include "GameSubsystem.h"
#include "LogSubsystem.h"
#include <cassert>

namespace Oyun
{
	GameSubsystem* GameSubsystem::system = nullptr;

	GameSubsystem::GameSubsystem()
		:EngineSubsytem()
	{
	}

	GameSubsystem::~GameSubsystem()
	{
		system = nullptr;
	}

	GameSubsystem* GameSubsystem::GetPtr()
	{
		return system;
	}

	GameSubsystem& GameSubsystem::Get()
	{
		return *system;
	}

	GameSubsystem& GameSubsystem::Instantiate()
	{
		assert(system == nullptr);
		system = new GameSubsystem();
		return *system;
	}

	void GameSubsystem::StartUp()
	{
		LOG << "GameSubsystem Startup" << END;

	}

	void GameSubsystem::ShutDown()
	{
		LOG << "GameSubsystem Shutdown" << END;
		delete this;
	}

	void GameSubsystem::GameLoop(float deltaTime)
	{
	
	}

}