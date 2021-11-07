#pragma once


#define EngineExport   __declspec( dllexport )

class EngineExport Renderer
{
protected:
	class App* _App;

public:

	Renderer(class App* app, int width, int height);
	
	virtual bool SetupRenderer() = 0;
	virtual bool SetupImgui() = 0;
	virtual void TerminateRenderer() = 0;
	virtual bool RenderLoop() = 0;

	virtual int GetWindowWidth() = 0;
	virtual int GetWindowHeight() = 0;
	virtual int GetWindowPosX() = 0;
	virtual int GetWindowPosY() = 0;

	
protected:

	
	int _Width;		//! Window width
	int _Heigth;	//! Window height
	int _PosX;		//! Window position
	int _PosY;		//! Window position
};

class EngineExport GlfWRenderer : public Renderer
{
	struct GLFWwindow* _Window;

	
	public:

	GlfWRenderer(class App* app, int width, int height);
	virtual bool SetupRenderer() override;
	virtual bool SetupImgui() override;

	virtual void TerminateRenderer() override;
	virtual bool RenderLoop() override;
	virtual int GetWindowWidth() override;
	virtual int GetWindowHeight() override;
	virtual int GetWindowPosX() override;
	virtual int GetWindowPosY() override;

	void SetWindowWidth(int);
	void SetWindowHeight(int);

	void SetWindowPosX(int);
	void SetWindowPosY(int);

};