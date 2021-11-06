#pragma once


#define EngineExport   __declspec( dllexport )

class EngineExport Renderer
{
protected:
	class App* _App;

public:

	Renderer(class App* app);
	
	virtual bool SetupRenderer() = 0;
	virtual bool SetupImgui() = 0;
	virtual void TerminateRenderer() = 0;
	virtual bool RenderLoop() = 0;
};

class EngineExport GlfWRenderer : public Renderer
{
	struct GLFWwindow* _Window;

	public:

	GlfWRenderer(class App* app);
	virtual bool SetupRenderer() override;
	virtual bool SetupImgui() override;

	virtual void TerminateRenderer() override;
	virtual bool RenderLoop() override;
};