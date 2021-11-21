#include <functional>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#define EngineExport  __declspec( dllexport )


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
    void Render();
    void RenderEnd();

    extern GLFWwindow* gWindow;

    extern int gWindowWidth;
    extern int gWindowHeight;
    extern int gWindowPosX;
    extern int gWindowPosY;

    extern const char* gGlslVersion;
   
}