#include "..\include\SimpleRenderApp.h"
#include "App.h"
#include <iostream>
#include "Vector.h"
#include "Shader.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


SimpleRenderApp::SimpleRenderApp(const char* name, const char* title, int width, int height)
    :App(name, title, width, height)
{
    ShaderMan->CompileShader("basic_shader", vertexShaderSource, fragmentShaderSource);
}


bool SimpleRenderApp::Loop()
{
    return App::Loop();
}