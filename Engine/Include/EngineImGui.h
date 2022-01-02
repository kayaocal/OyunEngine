#ifndef OYUN_ENGINE_IMGUI_H__
#define OYUN_ENGINE_IMGUI_H__

#include <vector>
#include <string>
#include "ImLayer.h"

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif


struct GLFWwindow;
struct ImGuiContext;

namespace Oyun
{

	struct Engine;

	class OYUN_API TestImgui : public Oyun::Imgui::ImLayer
	{
	public:


		TestImgui(const std::string rName, Oyun::Engine* engine);

		virtual void Draw();

	};
	

	struct OYUN_API EngineImGui
	{
	public:
		std::vector<Imgui::ImLayer*> layers;

		void Init(GLFWwindow* wnd, const char* glslVersion);

		void ApplyDarkTheme();

		void Terminate();

		void AddLayer(Imgui::ImLayer* layer);

		//TO_DO: void RemoveLayer(EngineImLayer* layer);

		void Draw();

	private:
		ImGuiContext* Context;
		
	};

}

#endif //OYUN_ENGINE_IMGUI_H__
