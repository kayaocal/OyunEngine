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

namespace Oyun
{

    std::vector<Window*> windows;

    GLFWwindow* gWindow = nullptr;

    const char* gGlslVersion = "#version 420";

    void SetupRenderer(Window* wnd)
    {
        LOG << "GlfwRenderer::SetupRenderer" << END;

        glfwSetErrorCallback(glfw_error_callback);
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create window with graphics context
        wnd->window = glfwCreateWindow(wnd->width, wnd->height, wnd->title.c_str(), NULL, NULL);
        assert(wnd->window != NULL);

        glfwSetWindowPos(wnd->window, wnd->posx, wnd->posy);
        glfwSetWindowSizeCallback(wnd->window, glfw_window_size_changed);
        glfwSetWindowCloseCallback(wnd->window, glfw_window_close_callback);
        glfwSetWindowPosCallback(wnd->window, glfw_window_pos_changed);
        glfwSetWindowMaximizeCallback(wnd->window, glfw_window_maximized_callback);
        glfwSetWindowFocusCallback(wnd->window, glfw_window_focus_callback);

        glfwMakeContextCurrent(wnd->window);

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

        windows.push_back(wnd);
    }

    void PollWindowEvents()
    {
        glfwPollEvents();
    }

    void Render(Window* wnd, Camera* cam, Scene* scn)
    {
        assert(cam != nullptr, "Render without camera is not possible");

        PollWindowEvents();

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

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //// view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(cam->Zoom), (float)wnd->width / (float)wnd->height, 0.1f, 100.0f);
        glm::mat4 view = cam->GetViewMatrix();


        for (auto ent : scn->EntityList)
        {
            if (ent->IsVisible())
            {
                TransformComponent* transformComp = ent->GetComponent<TransformComponent>();
                StaticMeshComponent* staticMesh = ent->GetComponent<StaticMeshComponent>();
            
                staticMesh->Draw(glm::value_ptr(view), glm::value_ptr(projection), glm::value_ptr(transformComp->GetModelMatrix()));
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
        fprintf(stderr, "Glfw Error %d: %s\n", error, description);
    }

    void glfw_window_size_changed(GLFWwindow* window, int width, int height)
    {
        for (auto wnd : windows)
        {
            if (wnd->window == window)
            {
                LOG << "Window " << wnd->title <<" : "<<" size changed! ( " << width << " , " << height << " )" << END;
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
                LOG << "Window " << wnd->title << " : " << " position changed! ( " << x << " , " << y << " )" << END;
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
                LOG << "Close window : " << wnd->title << END;
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
                    LOG << "Window focus lost! " << wnd->title << END;
                    wnd->windowFocused = false;
                }
                else
                {
                    LOG << "Window focus gained!" << wnd->title << END;
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
                    LOG << "Window unmaximized!" << wnd->title << END;
                }
                else
                {
                    LOG << "Window maximized!" << wnd->title << END;
                }
                break;
            }
        }
    }
}
