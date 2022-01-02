#include "Engine.h"
#include "subsystems\RenderSubsystem.h"
#include "subsystems\LogSubsystem.h"
#include "subsystems\GameSubsystem.h"
#include "subsystems\WorldSubsystem.h"
#include "subsystems\ResourceSubsystem.h"
#include "subsystems\InputSubsystem.h"
#include <iostream>
#include <chrono>


namespace Oyun
{
	const char* EngineName = "Oyun Engine";
	const char* EngineVersion = "v0.0.0.1d";
	const char* EngineDescription = "Designed to make good games.";
	int gFrameCount = 0;

	Engine::Engine(GameSubsystem* game, RenderSubsystem* renderer, WorldSubsystem* world, Window* baseWindow)
		:mGameSubsystem(game), mRenderSubsystem(renderer), mWorldSubsystem(world), mInputSubsystem(new InputSubsystem()), engineRunning(true),
		fps(0), deltaTime(0.0f), mFpsSum(0), mFpsTimer(0.0), frameCount(0), instantFps(0), lastRenderTime(0)
	{
		mGameSubsystem->SetEngine(this);
		mRenderSubsystem->SetEngine(this, baseWindow);
		mWorldSubsystem->SetEngine(this);
		mInputSubsystem->SetEngine(this);
	}

	Engine::~Engine()
	{
		//delete mGameSubsystem;
		delete mInputSubsystem;
		delete mRenderSubsystem;
		delete mWorldSubsystem;
	}

	GameSubsystem* Engine::GetGameSubsystem() const
	{
		return mGameSubsystem;
	}

	RenderSubsystem* Engine::GetRenderSubsystem() const
	{
		return mRenderSubsystem;
	}

	WorldSubsystem* Engine::GetWorldSubsystem() const
	{
		return mWorldSubsystem;
	}

	InputSubsystem* Engine::GetInputSubsystem() const
	{
		return mInputSubsystem;
	}

	void Engine::StartUp()
	{
		mWorldSubsystem->StartUp();		
		mRenderSubsystem->StartUp();
		mInputSubsystem->StartUp();
		mGameSubsystem->StartUp();
	}

	void Engine::ShutDown()
	{
		mWorldSubsystem->ShutDown();
		mRenderSubsystem->ShutDown();
		mInputSubsystem->ShutDown();
		mGameSubsystem->ShutDown();
	}

	void Engine::Loop()
	{
		using namespace std::chrono;

		auto gameLoopStart = high_resolution_clock::now();
		mGameSubsystem->GameLoop(deltaTime);
		auto gameLoopEnd = high_resolution_clock::now();
		mRenderSubsystem->RenderLoop();
		auto renderEnd = high_resolution_clock::now();


		frameCount++;
		double gameTime = static_cast<double>(duration_cast<microseconds>(gameLoopEnd - gameLoopStart).count()) / 1000000.0;
		double renderTime = static_cast<double>(duration_cast<microseconds>(renderEnd - gameLoopEnd).count()) / 1000000.0;
		deltaTime = static_cast<float>(renderTime + gameTime);
		instantFps = (deltaTime > 0.0) ? (1.0 / deltaTime) : 0.0;

		
		mFpsSum += 1;
		mFpsTimer+=deltaTime;
		if (mFpsTimer >= 1.0)
		{
			fps = mFpsSum;
			mFpsSum = 0;
			mFpsTimer = 0;
		}

		gFrameCount++;
	}

	void Engine::Close()
	{
		engineRunning = false;
	}

}