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


    struct Window
    {
        Window() : width(1366), height(768), posx(300), 
            posy(300), window(nullptr), 
            windowShuldClose(false), windowFocused(true),
            runWindowUnFocused(false), title(""), windowIndex(0)
        {
            srand(time(NULL));

            R = rand() % 255;
            R /= 255.0f;
            G = rand() % 255;
            G /= 255.0f;
            B = rand() % 255;
            B /= 255.0f;
        
        }

        int width, height, posx, posy;
        GLFWwindow* window;
        bool windowShuldClose;
        bool windowFocused;
        std::string title;
        unsigned int windowIndex;

        bool runWindowUnFocused;

        float R, G, B;
    };


    void TerminateWindow(Window* wnd);
    void TerminateRenderer(Window*);
    
    class Camera;
    class Scene;
    OYUN_API void PollWindowEvents();
    void RenderStart(Window*);
    void Render(Window*, Camera*, Scene*);
    void RenderEnd(Window*);
    OYUN_API void InitializeRenderer();


    extern const char* gGlslVersion;
   
}

#endif //OYUN_ENGINE_GLFW_HANDLER_H__