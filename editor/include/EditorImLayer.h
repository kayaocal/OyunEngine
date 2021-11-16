#pragma once

#include "EngineImGui.h"

class EditorImLayer : public Engine::EngineImLayer
{
public:

	EditorImLayer(const std::string rName);

	virtual void Draw();

	void DrawDockableWindow();
	void DrawMenuBar();
};