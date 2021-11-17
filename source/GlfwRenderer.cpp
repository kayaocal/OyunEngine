#include "Renderer.h"
#include <iostream>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>


#include "Texture.h"
#include "Shader.h"
#include "App.h"
#include <components/TransformComponent.h>
#include "Mesh.h"
#include "Model.h"
#include "Camera.h"

#include "EngineImGui.h"

GlfWRenderer* _Renderer;

Engine::EngineImGui ImGui;

const char* glsl_version = "#version 420";

Engine::Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));
/*
*   GLFW Event Callbacks!
*/
void glfw_window_maximized_callback(GLFWwindow* window, int maximized);
void glfw_window_focus_callback(GLFWwindow* window, int focused);
void glfw_window_close_callback(GLFWwindow* wnd);
void glfw_window_pos_changed(GLFWwindow* wnd, int x, int y);
void glfw_window_size_changed(GLFWwindow* wnd, int width, int height);
void glfw_error_callback(int error, const char* description);

GlfWRenderer::GlfWRenderer(App* app, int width, int height)
    :Renderer(app, width, height)
{
    _Renderer = this;

    std::cout << "GlfWRenderer" << std::endl;
    if (!SetupRenderer())
    {
        std::cout << "Can not setup Renderer!" << std::endl;
    }


}
Engine::Texture* Tex;

TransformComponent Transform;

Engine::Model* TestModel;
bool GlfWRenderer::SetupRenderer()
{
	std::cout << "GlfwRenderer::SetupRenderer" <<std::endl;

    glfwSetErrorCallback(glfw_error_callback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window with graphics context
    _Window = glfwCreateWindow(_Width, _Heigth, _App->GetTitle().c_str(), NULL, NULL);
    if (_Window == NULL)
        return false;

    glfwSetWindowPos(_Window, _PosX, _PosY);
    glfwSetWindowSizeCallback(_Window, glfw_window_size_changed);
    glfwSetWindowCloseCallback(_Window, glfw_window_close_callback);
    glfwSetWindowPosCallback(_Window, glfw_window_pos_changed);
    glfwSetWindowMaximizeCallback(_Window, glfw_window_maximized_callback);
    glfwSetWindowFocusCallback(_Window, glfw_window_focus_callback);

    glfwMakeContextCurrent(_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glfwSwapInterval(1); // Enable vsync

    Tex = Engine::TextureStore::Get().Load( "test.png" );

    Transform.Position = glm::vec3(0.0f, 0.0f, -5.0f);
    Transform.EulerRotation = glm::vec3(0, 0, 0);
    Transform.Scale = glm::vec3(1.0f, 1.0f, 1.0f);

    TestModel = new Engine::Model("backpack.obj");
    
    ImGui.Init(_Window, glsl_version);
    glEnable(GL_DEPTH_TEST);

    MainCamera = &camera;
	return true;
}

void GlfWRenderer::TerminateRenderer()
{
    // Cleanup
   

    glfwDestroyWindow(_Window);
    glfwTerminate();
}

bool GlfWRenderer::RenderLoop()
{
    if (glfwWindowShouldClose(_Window))
    {
        return false;
    }
    // Poll and handle events (inputs, window resize, etc.)
       // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
       // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
       // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
       // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();

    // Start the Dear ImGui frame
   
    int display_w, display_h;
    if (MainCamera->RenderTexture)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, MainCamera->FrameBuffer);
        glViewport(0, 0, MainCamera->RenderTexture->Width, MainCamera->RenderTexture->Height);
    }
    else
    {
        glfwGetFramebufferSize(_Window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
    }
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rendering
    
    using namespace Engine;
    glUseProgram(ShaderManager::Get().GetShaderByName("basic_shader")->ProgramId);
   
    unsigned int modelLoc = glGetUniformLocation(ShaderManager::Get().GetShaderByName("basic_shader")->ProgramId, "model");
    unsigned int viewLoc = glGetUniformLocation(ShaderManager::Get().GetShaderByName("basic_shader")->ProgramId, "view");
    unsigned int projLoc = glGetUniformLocation(ShaderManager::Get().GetShaderByName("basic_shader")->ProgramId, "projection");

   // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)_App->GetWidth() / (float)_App->GetHeight(), 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        
    // render the loaded model
    Transform.EulerRotation.y++;

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(Transform.GetModelMatrix()));
    TestModel->Draw(*ShaderManager::Get().GetShaderByName("basic_shader"));

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ImGui.Draw();
    glfwSwapBuffers(_Window);

    return true;
}

int GlfWRenderer::GetWindowWidth()
{
    return _Width;
}

int GlfWRenderer::GetWindowHeight()
{
    return _Heigth;
}


void GlfWRenderer::SetWindowWidth(int w)
{
    _Width = w;
}

void GlfWRenderer::SetWindowHeight(int h)
{
    _Heigth = h;
}

void GlfWRenderer::SetWindowPosX(int x)
{
    _PosX = x;
}

void GlfWRenderer::SetWindowPosY(int y)
{
    _PosY = y;
}

void GlfWRenderer::AddImGuiWindow(Engine::EngineImLayer* s)
{
    ImGui.AddLayer(s);
}


int GlfWRenderer::GetWindowPosX()
{
    return _PosX;
}

int GlfWRenderer::GetWindowPosY()
{
    return _PosY;
}





//********************************************************************************************************
//********************************************************************************************************
//********************************************************************************************************

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void glfw_window_size_changed(GLFWwindow* wnd, int width, int height)
{
    //std::cout << "Window size changed! ( " << width << " , " << height << " )" << std::endl;
    _Renderer->SetWindowWidth(width);
    _Renderer->SetWindowHeight(height);
}

void glfw_window_pos_changed(GLFWwindow* wnd, int x, int y)
{
    //std::cout << "Window position changed! ( " << x << " , " << y << " )" << std::endl;
    _Renderer->SetWindowPosX(x);
    _Renderer->SetWindowPosY(y);
}

void glfw_window_close_callback(GLFWwindow* wnd)
{
    std::cout << "Window closed!" << std::endl;
}

void glfw_window_focus_callback(GLFWwindow* window, int focused)
{
    if (focused == GLFW_FALSE)
    {
        std::cout << "Window focus lost!" << std::endl;
    }
    else
    {
        std::cout << "Window focus gained!" << std::endl;
    }
}

void glfw_window_maximized_callback(GLFWwindow* window, int maximized)
{
    if (maximized == GLFW_FALSE)
    {
        std::cout << "Window unmaximized!" << std::endl;
    }
    else
    {
        std::cout << "Window maximized!" << std::endl;
    }
}
