#include "Engine.h"
#include "FloatingCubesGameSubsystem.h"
#include <subsystems/RenderSubsystem.h>
#include <subsystems/WorldSubsystem.h>
#include <subsystems/LogSubsystem.h>
#include <subsystems/ResourceSubsystem.h>

#include <EngineGlfwHandler.h>

Oyun::Engine* gEngine;

int main()
{
	using namespace Oyun;


	Oyun::LogSubsystem::Instantiate().StartUp();
	Oyun::ResourceSubsystem::Instantiate().StartUp();

	Oyun::InitializeRenderer();
	
	
	gEngine = new Oyun::Engine(new Cubes::FloatingCubesGameSubsystem(),
		new Oyun::RenderSubsystem(1366, 768), new Oyun::WorldSubsystem());

	
	gEngine->StartUp();

	while(gEngine->engineRunning)
	{
		gEngine->Loop();
		PollWindowEvents();
	}



	gEngine->ShutDown();
	Oyun::ResourceSubsystem::Get().ShutDown();
	Oyun::LogSubsystem::Get().ShutDown();
	
	return 0;
}