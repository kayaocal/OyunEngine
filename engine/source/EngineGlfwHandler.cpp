#include "EngineGlfwHandler.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "components/TransformComponent.h"
#include "subsystems\LogSubsystem.h"
#include "Engine.h"
#include "Camera.h"
#include <cassert>
#include "subsystems/WorldSubsystem.h"
#include "Scene.h"
#include "components/StaticMeshComponent.h"
#include <vector>
#include "ImLayer.h"

namespace Oyun
{

    std::vector<Window*> windows;

    GLFWwindow* gWindow = nullptr;

    const char* gGlslVersion = "#version 420";

    void InitializeRenderer()
    {
        glfwSetErrorCallback(glfw_error_callback);
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    }


    void SetupRenderer(Window* wnd, Window* base)
    {
        LOG << "GlfwRenderer::SetupRenderer";

        // Create window with graphics context

        GLFWwindow* sharedWindow = nullptr;
        if (base != nullptr)
        {
            sharedWindow = base->window;
        }
        wnd->window = glfwCreateWindow(wnd->width, wnd->height, wnd->title.c_str(), NULL, sharedWindow);
        static unsigned int windowIndex = 0;
        wnd->windowIndex = windowIndex;
        windowIndex++;
        assert(wnd->window != NULL);

        glfwSetWindowPos(wnd->window, wnd->posx, wnd->posy);
        glfwSetWindowSizeCallback(wnd->window, glfw_window_size_changed);
        glfwSetWindowCloseCallback(wnd->window, glfw_window_close_callback);
        glfwSetWindowPosCallback(wnd->window, glfw_window_pos_changed);
        glfwSetWindowMaximizeCallback(wnd->window, glfw_window_maximized_callback);
        glfwSetWindowFocusCallback(wnd->window, glfw_window_focus_callback);

        GLFWwindow* old = glfwGetCurrentContext();
        glfwMakeContextCurrent(wnd->window);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        glfwSwapInterval(1); // Enable/Disable vsync
       /* if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }*/

       //assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));


        windows.push_back(wnd);
        if (old != NULL)
        {
            glfwMakeContextCurrent(old);
        }
    }

    void PollWindowEvents()
    {
        glfwPollEvents();
    }

    void RenderStart(Window* wnd)
    {
        glfwMakeContextCurrent(wnd->window);
    }

    void Render(Window* wnd, Camera* cam, Scene* scn)
    {
        assert(cam != nullptr, "Render without camera is not possible");

        if (cam->RenderTexture)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, cam->FrameBuffer);
            glViewport(0, 0, cam->RenderTexture->width, cam->RenderTexture->height);
        }
        else
        {
            glfwGetFramebufferSize(wnd->window, &wnd->width, &wnd->height);
            glViewport(0, 0, wnd->width, wnd->height);
        }
       // 
        glEnable(GL_DEPTH_TEST);
        static float colorx = 0.5f;
        colorx += 0.0005;
        if (colorx > 1.0f) colorx = 0.0f;

        
        glClearColor(wnd->R, wnd->G, wnd->B, 1.0f);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //// view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(cam->Zoom), (float)wnd->width / (float)wnd->height, 0.1f, 100.0f);
        glm::mat4 view = cam->GetViewMatrix();


        for (auto ent : scn->EntityList)
        {
            if (ent->IsVisible())
            {
                TransformComponent* transformComp = ent->GetTransform();
                StaticMeshComponent* staticMesh = ent->GetComponent<StaticMeshComponent>();
                
                staticMesh->Draw(glm::value_ptr(view), glm::value_ptr(projection), glm::value_ptr(transformComp->GetModelMatrix()), wnd);
            }
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void RenderEnd(Window* wnd)
    {
        glfwSwapBuffers(wnd->window);
    }

    void TerminateWindow(Window* wnd)
    {
        glfwDestroyWindow(wnd->window);
    }

    void TerminateRenderer(Window* wnd)
    {
        // Cleanup
        for (auto wnd : windows)
        {
            TerminateWindow(wnd);
        }

        windows.clear();
        glfwTerminate();
    }

    //********************************************************************************************************
    //********************************************************************************************************
    //********************************************************************************************************

    void glfw_error_callback(int error, const char* description)
    {
        LOG_ERR << "Glfw :"<<error << " - "<< description;
    }

    void glfw_window_size_changed(GLFWwindow* window, int width, int height)
    {
        for (auto wnd : windows)
        {
            if (wnd->window == window)
            {
                LOG << "Window " << wnd->title <<" : "<<" size changed! ( " << width << " , " << height << " )";
                wnd->height = height;
                wnd->width = width;
                break;
            }
        }
    }

    void glfw_window_pos_changed(GLFWwindow* window, int x, int y)
    {
        for (auto wnd : windows)
        {
            if (wnd->window == window)
            {
                LOG << "Window " << wnd->title << " : " << " position changed! ( " << x << " , " << y << " )";
                wnd->posx = x;
                wnd->posy = y;
                break;
            }
        }
    }

    void glfw_window_close_callback(GLFWwindow* window)
    {
        for (auto wnd : windows)
        {
            if (wnd->window == window)
            {
                LOG << "Close window : " << wnd->title;
                wnd->windowShuldClose = true;
                break;
            }
        }
    }

    void glfw_window_focus_callback(GLFWwindow* window, int focused)
    {
        for (auto wnd : windows)
        {
            if (wnd->window == window)
            {
                if (focused == GLFW_FALSE)
                {
                    LOG << "Window focus lost! " << wnd->title;
                    wnd->windowFocused = false;
                }
                else
                {
                    LOG << "Window focus gained!" << wnd->title;
                    wnd->windowFocused = true;
                }
                break;
            }
        }
    }

    void glfw_window_maximized_callback(GLFWwindow* window, int maximized)
    {
        for (auto wnd : windows)
        {
            if (wnd->window == window)
            {
                if (maximized == GLFW_FALSE)
                {
                    LOG << "Window unmaximized!" << wnd->title;
                }
                else
                {
                    LOG << "Window maximized!" << wnd->title;
                }
                break;
            }
        }
    }
}
