#ifndef OYUN_RENDER_SUBSYSTEM_H__
#define OYUN_RENDER_SUBSYSTEM_H__

#include "EngineSubsytem.h"

#define USE_GLFW

namespace Oyun
{



	class OYUN_API RenderSubsystem : public EngineSubsytem<RenderSubsystem>
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

#endif //OYUN_RENDER_SUBSYSTEM_H__