#include "Engine.h"
#include "subsystems\RenderSubsystem.h"
#include "subsystems\LogSubsystem.h"
#include "subsystems\GameSubsystem.h"
#include <iostream>
#include <chrono>

namespace Oyun
{
	const char* EngineName = "Oyun Engine";
	const char* EngineVersion = "v0.0.0.1d";
	const char* EngineDescription = "Designed to make good games.";

	bool gEngineRunning = false;

	unsigned long gFrameCount = 0;
	double gDeltaTime = 0;
	double gRenderTime = 0;
	double gGameTime = 0;
	double gInstantFps = 0;
	int gFps = 0;


	RenderSubsystem* renderSubsystem;
	void StartEngine(Oyun::GameSubsystem* game)
	{
		Oyun::LogSubsystem::Instantiate().StartUp();
		Oyun::RenderSubsystem::Instantiate(1366, 768).StartUp();
		renderSubsystem = Oyun::RenderSubsystem::GetPtr();
		game->StartUp();
		LOG << "Engine Started." << END;

		gEngineRunning = true;
		while (gEngineRunning)
		{
			Loop(game);
		}
		game->ShutDown();
		Oyun::RenderSubsystem::Get().ShutDown();
		Oyun::LogSubsystem::Get().ShutDown();
	}


	void Loop(Oyun::GameSubsystem* game)
	{
		using namespace std::chrono;

		auto gameLoopStart = high_resolution_clock::now();
		game->GameLoop(gDeltaTime);
		auto gameLoopEnd = high_resolution_clock::now();
		renderSubsystem->RenderLoop();
		auto renderEnd = high_resolution_clock::now();


		gFrameCount++;
		gGameTime = static_cast<double>(duration_cast<microseconds>(gameLoopEnd - gameLoopStart).count()) / 1000000.0;
		gRenderTime = static_cast<double>(duration_cast<microseconds>(renderEnd - gameLoopEnd).count()) / 1000000.0;
		gDeltaTime = gRenderTime + gGameTime;
		gInstantFps = (gDeltaTime > 0.0) ? (1.0 / gDeltaTime) : 0.0;

		static double fpsTimer = 0;
		static int fpsSum = 0;
		fpsSum += 1;
		fpsTimer+=gDeltaTime;
		if (fpsTimer >= 1.0)
		{
			gFps = fpsSum;
			fpsSum = 0.0;
			fpsTimer = 0;
		}

	}


	void ShutdownEngine()
	{
		gEngineRunning = false;
	}

}