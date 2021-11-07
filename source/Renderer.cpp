#include "..\include\Renderer.h"

Renderer::Renderer(App* app, int width, int height)
{
	_App = app;
	_Width = width;
	_Heigth = height;
	_PosX = 300;
	_PosY = 300;
}

