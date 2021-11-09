#pragma once
#include <string>


#define EngineExport  __declspec( dllexport )

class EngineExport App
{

	std::string _Name;
	std::string _Title;

	class GlfWRenderer* _Renderer;
public:

	class ShaderManager* ShaderMan;

	App(const char* name, const char* title, int width, int height);
	~App();


	virtual void OnDrawImGui();

	virtual bool Loop();

	std::string& GetTitle();
	int GetWidth();
	int GetHeight();
	int GetWindowPosX();
	int GetWindowPosY();

};