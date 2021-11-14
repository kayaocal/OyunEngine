#include "..\include\Renderer.h"
#include <iostream>
#include <Texture.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>

#include "Shader.h"
#include "App.h"
#include <components/TransformComponent.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "Mesh.h"
#include "Model.h"
#include "Camera.h"

GlfWRenderer* _Renderer;

const char* glsl_version = "#version 420";

Engine::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
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

    if (!SetupImgui())
    {
        std::cout << "Can not setup Imgui!" << std::endl;
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
    
    glEnable(GL_DEPTH_TEST);
	return true;
}

bool GlfWRenderer::SetupImgui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(_Window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return true;
}

void GlfWRenderer::TerminateRenderer()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    _App->OnDrawImGui();

    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(_Window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.5f, 0.5f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Update and Render additional Platform Windows
  // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
  //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }


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
    TestModel->Draw(*ShaderManager::Get().GetShaderByName("simple_shader"));

    //{
    //    float vertices[] = {
    //    -0.5f, -0.5f, 0.0f, // left  
    //     0.5f, -0.5f, 0.0f, // right 
    //     0.0f,  0.5f, 0.0f  // top   
    //    };

    //    unsigned int VBO, VAO;
    //    glGenVertexArrays(1, &VAO);
    //    glGenBuffers(1, &VBO);
    //    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    //    glBindVertexArray(VAO);

    //    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //    glEnableVertexAttribArray(0);

    //    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    //    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //    glBindVertexArray(0);
    //    glUseProgram(ShaderManager::Get().GetShaderByName("simple_shader")->ProgramId);
    //    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    //    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    //    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    //    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //    glDrawArrays(GL_TRIANGLES, 0, 3);

    //    // glBindVertexArray(0); // no need to unbind it every time 
    //}

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
