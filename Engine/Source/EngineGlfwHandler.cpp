#include "EngineGlfwHandler.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "Components/TransformComponent.h"
#include "Subsystems/LogSubsystem.h"
#include "Subsystems/InputSubsystem.h"
#include "Engine.h"
#include "Camera.h"
#include <cassert>
#include "Scene.h"
#include "Components/StaticMeshComponent.h"
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
        glfwSetKeyCallback(wnd->window, glfw_key_callback);
        glfwSetMouseButtonCallback(wnd->window, glfw_mouse_button_callback);
        glfwSetCursorPosCallback(wnd->window, glfw_cursor_position_callback);
        glfwSetScrollCallback(wnd->window, glfw_scroll_callback);

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
        colorx += 0.0005f;
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

    Oyun::KeyCode GlfwKeyToKeyCode(int key);
    Oyun::KeyState GlfwActionToKeyState(int action);
    void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
         for (auto wnd : windows)
         {
             if (wnd->window == window)
             {
                 wnd->renderSubsystem->GetEngine()->GetInputSubsystem()->UpdateKeyStatus(GlfwKeyToKeyCode(key), GlfwActionToKeyState(action));
             }
         }
    }

    Oyun::KeyCode GlfwMouseKeyToKeyCode(int key);
    void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
         for (auto wnd : windows)
         {
             if (wnd->window == window)
             {
                 wnd->renderSubsystem->GetEngine()->GetInputSubsystem()->UpdateKeyStatus(GlfwMouseKeyToKeyCode(button), GlfwActionToKeyState(action));
             }
         }
    }

    void glfw_cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
         for (auto wnd : windows)
         {
             if (wnd->window == window)
             {
                 wnd->renderSubsystem->GetEngine()->GetInputSubsystem()->SetMousePos(
                     static_cast<float>(xpos), static_cast<float>(ypos));
             }
         }
    }

    void glfw_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        for (auto wnd : windows)
         {
             if (wnd->window == window)
             {
                 wnd->renderSubsystem->GetEngine()->GetInputSubsystem()->SetMouseScroll(static_cast<float>(xoffset),
                     static_cast<float>(yoffset));
             }
         }
    }

    Oyun::KeyState GlfwActionToKeyState(int action)
    {
        switch (action)
        {
        case GLFW_RELEASE:
            return KeyState::RELEASED;
        default:
            return KeyState::PRESSED;
        }
    }

    Oyun::KeyCode GlfwMouseKeyToKeyCode(int key)
    {
        switch (key)
        {
        case GLFW_MOUSE_BUTTON_4:
        {
            return KeyCode::MOUSE_4;
        }
        case GLFW_MOUSE_BUTTON_5:
        {
            return KeyCode::MOUSE_5;
        }
        case GLFW_MOUSE_BUTTON_6:
        {
            return KeyCode::MOUSE_6;
        }
        case GLFW_MOUSE_BUTTON_7:
        {
            return KeyCode::MOUSE_7;
        }
        case GLFW_MOUSE_BUTTON_LEFT:
        {
            return  KeyCode::MOUSE_LEFT;
        }
        case GLFW_MOUSE_BUTTON_RIGHT:
        {
            return KeyCode::MOUSE_RIGHT;
        }
        case GLFW_MOUSE_BUTTON_MIDDLE:
        {
            return KeyCode::MOUSE_MIDDLE;
        }
        default:
            return KeyCode::COUNT;
        }
    }

    Oyun::KeyCode GlfwKeyToKeyCode(int key)
    {
        using namespace Oyun;
        switch (key)
        {
            case GLFW_KEY_SPACE:
            {
                return KeyCode::KEY_SPACE;
            }
            case GLFW_KEY_APOSTROPHE:
            {
                return KeyCode::KEY_APOSTROPHE;
            }
            case GLFW_KEY_COMMA:
            {
                return KeyCode::KEY_COMMA;
            }
            case GLFW_KEY_MINUS:
            {
                return KeyCode::KEY_MINUS;
            }
            case GLFW_KEY_PERIOD:
            {
                return KeyCode::KEY_PERIOD;
            }
            case GLFW_KEY_SLASH:
            {
                return KeyCode::KEY_SLASH;
            }
            case GLFW_KEY_0:
            {
                return KeyCode::KEY_0;
            }
            case GLFW_KEY_1:
            {
                return KeyCode::KEY_1;
            }
            case GLFW_KEY_2:
            {
                return KeyCode::KEY_2;
            }
            case GLFW_KEY_3:
            {
                return KeyCode::KEY_3;
            }
            case GLFW_KEY_4:
            {
                return KeyCode::KEY_4;
            }
            case GLFW_KEY_5:
            {
                return KeyCode::KEY_5;
            }
            case GLFW_KEY_6:
            {
                return KeyCode::KEY_6;
            }
            case GLFW_KEY_7:
            {
                return KeyCode::KEY_7;
            }
            case GLFW_KEY_8:
            {
                return KeyCode::KEY_8;
            }
            case GLFW_KEY_9:
            {
                return KeyCode::KEY_9;
            }
            case GLFW_KEY_SEMICOLON:
            {
                return KeyCode::KEY_SEMICOLON;
            }
            case GLFW_KEY_EQUAL:
            {
                return KeyCode::KEY_EQUAL;
            }
            case GLFW_KEY_A:
            {
                return KeyCode::KEY_A;
            }
            case GLFW_KEY_B:
            {
                return KeyCode::KEY_B;
            }
            case GLFW_KEY_C:
            {
                return KeyCode::KEY_C;
            }
            case GLFW_KEY_D:
            {
                return KeyCode::KEY_D;
            }
            case GLFW_KEY_E:
            {
                return KeyCode::KEY_E;
            }
            case GLFW_KEY_F:
            {
                return KeyCode::KEY_F;
            }
            case GLFW_KEY_G:
            {
                return KeyCode::KEY_G;
            }
            case GLFW_KEY_H:
            {
                return KeyCode::KEY_H;
            }
            case GLFW_KEY_I:
            {
                return KeyCode::KEY_I;
            }
            case GLFW_KEY_J:
            {
                return KeyCode::KEY_J;
            }
            case GLFW_KEY_K:
            {
                return KeyCode::KEY_K;
            }
            case GLFW_KEY_L:
            {
                return KeyCode::KEY_L;
            }
            case GLFW_KEY_M:
            {
                return KeyCode::KEY_M;
            }
            case GLFW_KEY_N:
            {
                return KeyCode::KEY_N;
            }
            case GLFW_KEY_O:
            {
                return KeyCode::KEY_O;
            }
            case GLFW_KEY_P:
            {
                return KeyCode::KEY_P;
            }
            case GLFW_KEY_Q:
            {
                return KeyCode::KEY_Q;
            }
            case GLFW_KEY_R:
            {
                return KeyCode::KEY_R;
            }
            case GLFW_KEY_S:
            {
                return KeyCode::KEY_S;
            }
            case GLFW_KEY_T:
            {
                return KeyCode::KEY_T;
            }
            case GLFW_KEY_U:
            {
                return KeyCode::KEY_U;
            }
            case GLFW_KEY_V:
            {
                return KeyCode::KEY_V;
            }
            case GLFW_KEY_W:
            {
                return KeyCode::KEY_W;
            }
            case GLFW_KEY_X:
            {
                return KeyCode::KEY_X;
            }
            case GLFW_KEY_Y:
            {
                return KeyCode::KEY_Y;
            }
            case GLFW_KEY_Z:
            {
                return KeyCode::KEY_Z;
            }
            case GLFW_KEY_LEFT_BRACKET:
            {
                return KeyCode::KEY_BRACKET_L;
            }
            case GLFW_KEY_BACKSLASH:
            {
                return KeyCode::KEY_BACK_SLASH;
            }
            case GLFW_KEY_RIGHT_BRACKET:
            {
                return KeyCode::KEY_BRACKET_R;
            }
            case GLFW_KEY_GRAVE_ACCENT:
            {
                return KeyCode::KEY_ACCENT;
            }
            case GLFW_KEY_ESCAPE:
            {
                return KeyCode::KEY_ESCAPE;
            }
            case GLFW_KEY_ENTER:
            {
                return KeyCode::KEY_ENTER;
            }
            case GLFW_KEY_TAB:
            {
                return KeyCode::KEY_TAB;
            }
            case GLFW_KEY_BACKSPACE:
            {
                return KeyCode::KEY_BACKSPACE;
            }
            case GLFW_KEY_INSERT:
            {
                return KeyCode::KEY_INSERT;
            }
            case GLFW_KEY_DELETE:
            {
                return KeyCode::KEY_DELETE;
            }
            case GLFW_KEY_RIGHT:
            {
                return KeyCode::KEY_RIGHT;
            }
            case GLFW_KEY_LEFT:
            {
                return KeyCode::KEY_LEFT;
            }
            case GLFW_KEY_DOWN:
            {
                return KeyCode::KEY_DOWN;
            }
            case GLFW_KEY_UP:
            {
                return KeyCode::KEY_UP;
            }
            case GLFW_KEY_PAGE_UP:
            {
                return KeyCode::KEY_PAGE_UP;
            }
            case GLFW_KEY_PAGE_DOWN:
            {
                return KeyCode::KEY_PAGE_DOWN;
            }
            case GLFW_KEY_HOME:
            {
                return KeyCode::KEY_HOME;
            }
            case GLFW_KEY_END:
            {
                return KeyCode::KEY_END;
            }
            case GLFW_KEY_CAPS_LOCK:
            {
                return KeyCode::KEY_CAPSLOCK;
            }
            case GLFW_KEY_SCROLL_LOCK:
            {
                return KeyCode::KEY_SCROLL_LOCK;
            }
            case GLFW_KEY_NUM_LOCK:
            {
                return KeyCode::KEY_NUMLOCK;
            }
            case GLFW_KEY_PRINT_SCREEN:
            {
                return KeyCode::KEY_PRINT_SCREEN;
            }
            case GLFW_KEY_PAUSE:
            {
                return KeyCode::KEY_PAUSE;
            }
            case GLFW_KEY_F1:
            {
                return KeyCode::KEY_F1;
            }
            case GLFW_KEY_F2:
            {
                return KeyCode::KEY_F2;
            }
            case GLFW_KEY_F3:
            {
                return KeyCode::KEY_F3;
            }
            case GLFW_KEY_F4:
            {
                return KeyCode::KEY_F4;
            }
            case GLFW_KEY_F5:
            {
                return KeyCode::KEY_F5;
            }
            case GLFW_KEY_F6:
            {
                return KeyCode::KEY_F6;
            }
            case GLFW_KEY_F7:
            {
                return KeyCode::KEY_F7;
            }
            case GLFW_KEY_F8:
            {
                return KeyCode::KEY_F8;
            }
            case GLFW_KEY_F9:
            {
                return KeyCode::KEY_F9;
            }
            case GLFW_KEY_F10:
            {
                return KeyCode::KEY_F10;
            }
            case GLFW_KEY_F11:
            {
                return KeyCode::KEY_F11;
            }
            case GLFW_KEY_F12:
            {
                return KeyCode::KEY_F12;
            }
            case GLFW_KEY_F13:
            {
                return KeyCode::KEY_F13;
            }
            case GLFW_KEY_F14:
            {
                return KeyCode::KEY_F14;
            }
            case GLFW_KEY_F15:
            {
                return KeyCode::KEY_F15;
            }
            case GLFW_KEY_F16:
            {
                return KeyCode::KEY_F16;
            }
            case GLFW_KEY_F17:
            {
                return KeyCode::KEY_F17;
            }
            case GLFW_KEY_F18:
            {
                return KeyCode::KEY_F18;
            }
            case GLFW_KEY_F19:
            {
                return KeyCode::KEY_F19;
            }
            case GLFW_KEY_F20:
            {
                return KeyCode::KEY_F20;
            }
            case GLFW_KEY_F21:
            {
                return KeyCode::KEY_F21;
            }
            case GLFW_KEY_F22:
            {
                return KeyCode::KEY_F22;
            }
            case GLFW_KEY_F23:
            {
                return KeyCode::KEY_F23;
            }
            case GLFW_KEY_F24:
            {
                return KeyCode::KEY_F24;
            }
            case GLFW_KEY_F25:
            {
                return KeyCode::KEY_F25;
            }
            case GLFW_KEY_KP_0:
            {
                return KeyCode::NUM_0;
            }
            case GLFW_KEY_KP_1:
            {
                return KeyCode::NUM_1;
            }
            case GLFW_KEY_KP_2:
            {
                return KeyCode::NUM_2;
            }
            case GLFW_KEY_KP_3:
            {
                return KeyCode::NUM_3;
            }
            case GLFW_KEY_KP_4:
            {
                return KeyCode::NUM_4;
            }
            case GLFW_KEY_KP_5:
            {
                return KeyCode::NUM_5;
            }
            case GLFW_KEY_KP_6:
            {
                return KeyCode::NUM_6;
            }
            case GLFW_KEY_KP_7:
            {
                return KeyCode::NUM_7;
            }
            case GLFW_KEY_KP_8:
            {
                return KeyCode::NUM_8;
            }
            case GLFW_KEY_KP_9:
            {
                return KeyCode::NUM_9;
            }
            case GLFW_KEY_KP_DIVIDE:
            {
                return KeyCode::NUM_FWD_SLASH;
            }
            case GLFW_KEY_KP_MULTIPLY:
            {
                return KeyCode::NUM_ASTERISK;
            }
            case GLFW_KEY_KP_SUBTRACT:
            {
                return KeyCode::NUM_MINUS;
            }
            case GLFW_KEY_KP_ADD:
            {
                return KeyCode::NUM_PLUS;
            }
            case GLFW_KEY_KP_ENTER:
            {
                return KeyCode::NUM_ENTER;
            }
            case GLFW_KEY_LEFT_SHIFT:
            {
                return KeyCode::KEY_SHIFT_L;
            }
            case GLFW_KEY_LEFT_CONTROL:
            {
                return KeyCode::KEY_CTRL_L;
            }
            case GLFW_KEY_LEFT_ALT:
            {
                return KeyCode::KEY_ALT_L;
            }
            case GLFW_KEY_RIGHT_SHIFT:
            {
                return KeyCode::KEY_SHIFT_R;
            }
            case GLFW_KEY_RIGHT_CONTROL:
            {
                return KeyCode::KEY_CTRL_R;
            }
            case GLFW_KEY_RIGHT_ALT:
            {
                return KeyCode::KEY_ALT_R;
            }
            default:
            {
                return KeyCode::COUNT;
            }
        }

    }


}
