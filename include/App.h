#pragma once
#include <string>


#define EngineExport  __declspec( dllexport )

namespace Engine
{
	class ShaderManager;
}

class EngineExport App
{
protected:
	std::string _Name;
	std::string _Title;

	class GlfWRenderer* _Renderer;
public:
	
	App(const char* name, const char* title, int width, int height);
	~App();


	virtual bool Loop();

	std::string& GetTitle();
	int GetWidth();
	int GetHeight();
	int GetWindowPosX();
	int GetWindowPosY();

	GlfWRenderer* GetRenderer();
};