#ifndef OYUN_ENGINE_IMGUI_H__
#define OYUN_ENGINE_IMGUI_H__

#include <vector>
#include <string>


#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif


struct GLFWwindow;

namespace Oyun
{
	class OYUN_API EngineImLayer
	{
	public:
		std::string name;

		EngineImLayer(const std::string rName);


		virtual void Draw() = 0;
	};

	struct OYUN_API EngineImGui
	{
	public:
		std::vector<EngineImLayer*> layers;

		void Init(GLFWwindow* wnd, const char* glslVersion);

		void ApplyDarkTheme();

		void Terminate();

		void AddLayer(EngineImLayer* layer);

		//TO_DO: void RemoveLayer(EngineImLayer* layer);

		void Draw();

		
	};

}

#endif //OYUN_ENGINE_IMGUI_H__
