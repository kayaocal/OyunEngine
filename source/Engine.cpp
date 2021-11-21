#include "Engine.h"
#include "RenderSubsystem.h"
#include "LogSubsystem.h"
#include "GameSubsystem.h"
#include <iostream>
#include <chrono>


namespace Oyun
{
	const char* EngineName = "Oyun Engine";
	const char* EngineVersion = "v0.0.0.1";
	const char* EngineDescription = "Designed to make good games.";

	bool gEngineRunning = false;

	unsigned long gFrameCount = 0;
	float gDeltaTime = 0;
	float gRenderTime = 0;
	float gGameTime = 0;
	float gInstantFps = 0;



	void StartEngine()
	{
		Oyun::LogSubsystem::Instantiate().StartUp();
		Oyun::RenderSubsystem::Instantiate(1366, 768).StartUp();
		Oyun::GameSubsystem::Instantiate().StartUp();
		 
		LOG << "Engine Started." << END;

		OnEngineStarted();

		gEngineRunning = true;
		while (gEngineRunning)
		{
			Loop();
		}

		Oyun::GameSubsystem::Get().ShutDown();
		Oyun::RenderSubsystem::Get().ShutDown();
		Oyun::LogSubsystem::Get().ShutDown();
	}

	void Loop()
	{
		using namespace std::chrono;

		auto gameLoopStart = high_resolution_clock::now();
		Oyun::GameSubsystem::Get().GameLoop(gDeltaTime);
		auto gameLoopEnd = high_resolution_clock::now();
		Oyun::RenderSubsystem::Get().RenderLoop();
		auto renderEnd = high_resolution_clock::now();


		gFrameCount++;
		gGameTime = static_cast<float>(duration_cast<microseconds>(gameLoopEnd - gameLoopStart).count()) / 1000000.0f;
		gRenderTime = static_cast<float>(duration_cast<microseconds>(renderEnd - gameLoopEnd).count()) / 1000000.0f;
		gDeltaTime = gRenderTime + gGameTime;
		gInstantFps = (gDeltaTime > 0.0f) ? (1.0f / gDeltaTime) : 0.0f;
	}

	void OnEngineStarted()
	{
		
	}

	void ShutdownEngine()
	{
		gEngineRunning = false;
	}

}