#include "RenderSubsystem.h"
#include <cassert>
#include "LogSubsystem.h"

#define USE_GLFW

#ifdef USE_GLFW
#include "EngineGlfwHandler.h"
#include "EngineGlfwImguiHandler.h"
#endif

namespace Oyun
{
	RenderSubsystem* RenderSubsystem::system = nullptr;

	RenderSubsystem::RenderSubsystem(int width, int height)
		:EngineSubsytem()
	{
		gWindowWidth = width;
		gWindowHeight = height;
	}

	RenderSubsystem::~RenderSubsystem()
	{
		system = nullptr;
	}

	RenderSubsystem* RenderSubsystem::GetPtr()
	{
		return system;
	}

	RenderSubsystem& RenderSubsystem::Get()
	{
		return *system;
	}

	RenderSubsystem& RenderSubsystem::Instantiate(int width, int height)
	{
		assert(system == nullptr);
		system = new RenderSubsystem(width, height);
		return *system;
	}

	void RenderSubsystem::StartUp()
	{
		LOG<<"RenderSubsystem Startup"<<END;
		SetupRenderer(gWindowWidth, gWindowHeight, "Test Window");
		Imgui::SetupImgui(gWindow, gGlslVersion);

	}

	void RenderSubsystem::ShutDown()
	{
		LOG << "RenderSubsystem Shutdown" << END;
		TerminateRenderer();
		delete this;
	}

	void RenderSubsystem::RenderLoop()
	{
		Render();
		Imgui::Draw();
		RenderEnd();
	}



}