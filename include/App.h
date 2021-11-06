#pragma once
#include <string>


#define EngineExport  __declspec( dllexport )

class EngineExport App
{

	std::string _Name;
	std::string _Title;

	class GlfWRenderer* _Renderer;
public:

	App(const char* name, const char* title);
	~App();


	virtual void OnDrawImGui();

	virtual bool Loop();

	std::string& GetTitle();

};