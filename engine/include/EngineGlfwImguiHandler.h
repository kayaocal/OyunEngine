#ifndef OYUN_ENGINE_GLFW_IMGUI_HANDLER_H__
#define OYUN_ENGINE_GLFW_IMGUI_HANDLER_H__

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

struct GLFWwindow;
namespace Oyun
{
	namespace Imgui
	{
		class ImLayer;
		void SetupImgui(GLFWwindow* wnd, const char* glslVersion);
		void TerminateImgui();
		void ApplyDarkTheme();

		void Draw();

		OYUN_API void AddLayer(ImLayer* layer);
	}
}

#endif //OYUN_ENGINE_GLFW_IMGUI_HANDLER_H__