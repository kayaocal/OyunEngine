#pragma once

#include "EngineImGui.h"

class EditorImLayer : public Engine::EngineImLayer
{
public:


	EditorImLayer(const std::string rName, App* app);

	virtual void Draw();

	void DrawDockableWindow();
	void DrawMenuBar();
	void DrawViewPort();
};