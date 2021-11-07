#include "App.h"
#include "Renderer.h"

#include <iostream>
#include "imgui.h"

App::App(const char* name, const char* title)
{
	_Name = name;
	_Title = title;
	std::cout << "Application " << _Name << "Started!" << std::endl;

    _Renderer = new GlfWRenderer(this);
}

App::~App()
{
}

void App::OnDrawImGui()
{
    std::cout << "App::OnDrawImGui()" << std::endl;
    static bool show_demo_window = true;
    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

   
    bool show_another_window = true;
    // 3. Show another simple window.
    ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
        show_another_window = false;
    ImGui::End();
}

std::string& App::GetTitle()
{
    return _Title;
}

bool App::Loop()
{
    if (!_Renderer->RenderLoop())
    {
        return false;
    }

    return true;
}
