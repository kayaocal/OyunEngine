#include "..\include\SimpleRenderApp.h"
#include "App.h"
#include <iostream>
#include "Vector.h"
#include "Shader.h"

const char* vertexShaderSource = "#version 330 core\n" 
"layout (location = 0) in vec3 aPos;\n" 
"layout (location = 1) in vec3 aNormal;\n" 
"layout (location = 2) in vec2 aTexCoords;\n" 
"out vec2 TexCoords;\n" 
"uniform mat4 model;\n" 
"uniform mat4 view;\n" 
"uniform mat4 projection;\n" 
"void main()\n" 
"{\n" 
"    TexCoords = aTexCoords;    \n" 
"    gl_Position = projection * view * model * vec4(aPos, 1.0);\n" 
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoords;\n"
"uniform sampler2D texture_diffuse1;\n"
"void main()\n"
"{    \n"
"    FragColor = texture(texture_diffuse1, TexCoords);\n"
"}\0";


SimpleRenderApp::SimpleRenderApp(const char* name, const char* title, int width, int height)
    :App(name, title, width, height)
{
    using namespace Engine;
    ShaderManager::Get().CompileShader("basic_shader", vertexShaderSource, fragmentShaderSource);
}


bool SimpleRenderApp::Loop()
{
    return App::Loop();
}