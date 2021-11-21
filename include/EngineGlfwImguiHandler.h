#pragma once

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