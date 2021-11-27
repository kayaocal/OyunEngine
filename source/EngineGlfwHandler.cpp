#include "EngineGlfwHandler.h"
#include "LogSubsystem.h"
#include "Engine.h"
#include "Camera.h"
#include <cassert>

namespace Oyun
{

    GLFWwindow* gWindow = nullptr;

    int gWindowWidth = 0;
    int gWindowHeight = 0;
    int gWindowPosX = 0;
    int gWindowPosY = 0;
    const char* gGlslVersion = "#version 420";

    void SetupRenderer(int width, int height, const char* title)
    {
        LOG << "GlfwRenderer::SetupRenderer" << END;

        gWindowWidth = width;
        gWindowHeight = height;
        gWindowPosX = 300;
        gWindowPosY = 300;

        glfwSetErrorCallback(glfw_error_callback);
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create window with graphics context
        gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, title, NULL, NULL);
        assert(gWindow != NULL);

        glfwSetWindowPos(gWindow, gWindowPosX, gWindowPosY);
        glfwSetWindowSizeCallback(gWindow, glfw_window_size_changed);
        glfwSetWindowCloseCallback(gWindow, glfw_window_close_callback);
        glfwSetWindowPosCallback(gWindow, glfw_window_pos_changed);
        glfwSetWindowMaximizeCallback(gWindow, glfw_window_maximized_callback);
        glfwSetWindowFocusCallback(gWindow, glfw_window_focus_callback);

        glfwMakeContextCurrent(gWindow);

       /* if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }*/
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            assert(false);
        }
       //assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

        glfwSwapInterval(0); // Enable vsync

    }

    void Render(Camera* cam)
    {
        assert(cam != nullptr, "Render without camera is not possible");

        glfwPollEvents();

        if (cam->RenderTexture)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, cam->FrameBuffer);
            glViewport(0, 0, cam->RenderTexture->width, cam->RenderTexture->height);
        }
        else
        {
            glfwGetFramebufferSize(gWindow, &gWindowWidth, &gWindowHeight);
            glViewport(0, 0, gWindowWidth, gWindowHeight);
        }


        glEnable(GL_DEPTH_TEST);
        glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void RenderEnd()
    {
        glfwSwapBuffers(gWindow);
    }

    void TerminateRenderer()
    {
        // Cleanup

        glfwDestroyWindow(gWindow);
        glfwTerminate();
    }

    //********************************************************************************************************
    //********************************************************************************************************
    //********************************************************************************************************

    void glfw_error_callback(int error, const char* description)
    {
        fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    }

    void glfw_window_size_changed(GLFWwindow* wnd, int width, int height)
    {
        LOG << "Window size changed! ( " << width << " , " << height << " )" << END;
        gWindowWidth = width;
        gWindowHeight = height;
    }

    void glfw_window_pos_changed(GLFWwindow* wnd, int x, int y)
    {
        LOG << "Window position changed! ( " << x << " , " << y << " )" << END;
        gWindowPosX = x;
        gWindowPosY = y;
    }

    void glfw_window_close_callback(GLFWwindow* wnd)
    {
        LOG << "Close window!" << END;
        ShutdownEngine();
    }

    void glfw_window_focus_callback(GLFWwindow* window, int focused)
    {
        if (focused == GLFW_FALSE)
        {
            LOG << "Window focus lost!" << END;
        }
        else
        {
            LOG << "Window focus gained!" << END;
        }
    }

    void glfw_window_maximized_callback(GLFWwindow* window, int maximized)
    {
        if (maximized == GLFW_FALSE)
        {
            LOG << "Window unmaximized!" << END;
        }
        else
        {
            LOG << "Window maximized!" << END;
        }
    }
}
