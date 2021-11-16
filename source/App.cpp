#include "App.h"
#include "Renderer.h"

#include <iostream>
#include "imgui.h"
#include "Shader.h"

App::App(const char* name, const char* title, int width, int height)
{
    _Name = name;
    _Title= title;
	std::cout << "Application " << _Name << "Started!" << std::endl;

    _Renderer = new GlfWRenderer(this, width, height);
}

App::~App()
{
}


std::string& App::GetTitle()
{
    return _Title;
}

int App::GetWidth()
{
    return _Renderer->GetWindowWidth();
}


int App::GetHeight()
{
    return _Renderer->GetWindowHeight();
}

int App::GetWindowPosX()
{
    return _Renderer->GetWindowPosX();
}

int App::GetWindowPosY()
{
    return _Renderer->GetWindowPosY();
}

bool App::Loop()
{
    if (!_Renderer->RenderLoop())
    {
        return false;
    }

    return true;
}
