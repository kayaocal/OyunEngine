#ifndef OYUN_ENGINE_GLFW_IMGUI_HANDLER_H__
#define OYUN_ENGINE_GLFW_IMGUI_HANDLER_H__

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

		void AddLayer(ImLayer* layer);
	}
}

#endif //OYUN_ENGINE_GLFW_IMGUI_HANDLER_H__