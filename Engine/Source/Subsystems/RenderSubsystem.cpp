#include "Subsystems\RenderSubsystem.h"
#include "Subsystems\LogSubsystem.h"
#include <CameraManager.h>

#include "Engine.h"
#include "Subsystems/WorldSubsystem.h"
#include "Scene.h"
#define USE_GLFW

#ifdef USE_GLFW
#include "EngineGlfwHandler.h"
#endif
#include <GLFW/glfw3.h>
#include <EngineImGui.h>

namespace Oyun
{

	RenderSubsystem::RenderSubsystem(int width, int height)
		:EngineSubsytem(), mEngine(nullptr), mWindow(new Oyun::Window()), mImGui( new Oyun::EngineImGui())
	{
		mWindow->width = width;
		mWindow->height = height;
		mWindow->title = "Test Title";
		mWindow->posx = 300;
		mWindow->posy = 300;
		mWindow->renderSubsystem = this;
	}

	RenderSubsystem::~RenderSubsystem()
	{
		delete mImGui;
		delete mWindow;
	}


	void SetupRenderer(Oyun::Window* wnd, Oyun::Window* shared);

	void RenderSubsystem::StartUp()
	{
		LOG<<"RenderSubsystem Startup";
		SetupRenderer(mWindow, mShareWindow);
		mImGui->Init(mWindow->window, gGlslVersion);
	}

	void RenderSubsystem::ShutDown()
	{
		LOG << "RenderSubsystem Shutdown";
		DeleteAllCameramans(mWindow);
		TerminateWindow(mWindow);
		delete this;
	}

	void RenderSubsystem::SetEngine(Engine* engine, Window* baseWindow)
	{
		mEngine = engine;
		mShareWindow = baseWindow;
	}

	Engine*  RenderSubsystem::GetEngine()
	{
		return mEngine;
	}

	void PollWindowEvents();
	void RenderSubsystem::RenderLoop()
	{
		//if (!mWindow->runWindowUnFocused && !mWindow->windowFocused)
		//{
		//	PollWindowEvents();
		//	return;
		//}

		if (mWindow->windowShuldClose)
		{
			mEngine->Close();
		}

		RenderStart(mWindow);

		for (auto cam : CameramanList)
		{
			if (cam->wnd->window == mWindow->window)
			{
				Render(mWindow, cam->camera, mEngine->GetWorldSubsystem()->GetScene());
			}
		}

		mImGui->Draw();
		RenderEnd(mWindow);
	}

	Window* RenderSubsystem::GetWindow() const
	{
		return mWindow;
	}

	EngineImGui* RenderSubsystem::GetImGui() const
	{
		return mImGui;
	}



}