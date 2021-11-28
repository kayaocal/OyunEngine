#pragma once

#include "EngineSubsytem.h"

#define USE_GLFW

namespace Oyun
{



	class EngineExport RenderSubsystem : public EngineSubsytem<RenderSubsystem>
	{
		RenderSubsystem(int width, int height);
		~RenderSubsystem();
	

	public:

		static RenderSubsystem* system;

		static RenderSubsystem* GetPtr();
		static RenderSubsystem& Get();
		static RenderSubsystem& Instantiate(int width = 800, int height = 600);
		
		virtual void StartUp() override;
		virtual void ShutDown() override;

		void RenderLoop();

	};

}