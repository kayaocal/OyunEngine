#ifndef OYUN_RENDER_SUBSYSTEM_H__
#define OYUN_RENDER_SUBSYSTEM_H__

#include "EngineSubsytem.h"

#define USE_GLFW

namespace Oyun
{
	struct Engine;
	struct Window;
	class EngineImGui;

	class OYUN_API RenderSubsystem : public EngineSubsytem<RenderSubsystem>
	{

	public:
		
		RenderSubsystem(int width, int height);
		~RenderSubsystem();

		virtual void StartUp() override;
		virtual void ShutDown() override;
		void SetEngine(Engine*, Window*);
		void RenderLoop();

		Window* GetWindow() const;
		Window* GetShareWindow() const;
		EngineImGui* GetImGui() const;
	private:
		Engine* mEngine;
		Window* mShareWindow;
		Window* mWindow;
		
		EngineImGui* mImGui;
	};

}

#endif //OYUN_RENDER_SUBSYSTEM_H__