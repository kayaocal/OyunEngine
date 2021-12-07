#include "subsystems/GameSubsystem.h"
#include "subsystems/LogSubsystem.h"
#include <cassert>

namespace Oyun
{

	GameSubsystem::GameSubsystem()
		:EngineSubsytem()
	{
	}

	GameSubsystem::~GameSubsystem()
	{
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

	void GameSubsystem::SetEngine(Engine* engine)
	{
		mEngine = engine;
	}

	void GameSubsystem::GameLoop(float deltaTime)
	{
	
	}

}