#pragma once

#include <vector>
#include <string>
#define EngineExport   __declspec( dllexport )

struct GLFWwindow;
class App;

namespace Engine
{
	class EngineExport EngineImLayer
	{
	public:
		std::string Name;
		App* MyApp;

		EngineImLayer(const std::string rName, App* app);


		virtual void Draw() = 0;
	};

	struct EngineExport EngineImGui
	{
	public:
		std::vector<EngineImLayer*> Layers;

		void Init(GLFWwindow* wnd, const char* glslVersion);

		void ApplyDarkTheme();

		void Terminate();

		void AddLayer(EngineImLayer* layer);

		//TO_DO: void RemoveLayer(EngineImLayer* layer);

		void Draw();

		
	};

}