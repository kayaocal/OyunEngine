#include "EditorApp.h"
#include <iostream>
#include "Vector.h"
#include "Shader.h"
#include "Renderer.h"
#include "EditorImLayer.h"

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

const char* simplefragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 TexCoords;\n"
"uniform sampler2D texture_diffuse0;\n"
"void main()\n"
"{    \n"
"    FragColor = texture(texture_diffuse0, TexCoords);\n"
"}\0";

const char* simplevertexShaderSource = "#version 330 core\n"
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

EditorApp::EditorApp(const char* name, const char* title, int width, int height)
    :App(name, title, width, height)
{
    using namespace Engine;
    ShaderManager::Get().CompileShader("basic_shader", vertexShaderSource, simplefragmentShaderSource);
    _Renderer->AddImGuiWindow(new EditorImLayer("EditorMain", this));
}



bool EditorApp::Loop()
{
    return App::Loop();
}

void EditorApp::DrawMenuBar()
{
    
}

void EditorApp::DrawMainFrame()
{
   

}
