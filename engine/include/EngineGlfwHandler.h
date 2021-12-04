#ifndef OYUN_ENGINE_GLFW_HANDLER_H__
#define OYUN_ENGINE_GLFW_HANDLER_H__

#include <iostream>



#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

struct GLFWwindow;

namespace Oyun
{
    void glfw_window_maximized_callback(GLFWwindow* window, int maximized);
    void glfw_window_focus_callback(GLFWwindow* window, int focused);
    void glfw_window_close_callback(GLFWwindow* wnd);
    void glfw_window_pos_changed(GLFWwindow* wnd, int x, int y);
    void glfw_window_size_changed(GLFWwindow* wnd, int width, int height);
    void glfw_error_callback(int error, const char* description);

    void SetupRenderer(int width, int height, const char* title);
    void TerminateRenderer();
    
    class Camera;
    void Render(Camera*);
    void RenderEnd();

    extern GLFWwindow* gWindow;

    extern int gWindowWidth;
    extern int gWindowHeight;
    extern int gWindowPosX;
    extern int gWindowPosY;

    extern const char* gGlslVersion;
   
}

#endif //OYUN_ENGINE_GLFW_HANDLER_H__