#pragma once

#include "ImLayer.h"

class EditorDockableWindowLayer : public Oyun::Imgui::ImLayer
{
public:


	EditorDockableWindowLayer(const std::string rName);

	virtual void Draw();

	void DrawDockableWindow();
	void DrawMenuBar();
	void DrawViewPort();
};

class EditorViewPortLayer : public Oyun::Imgui::ImLayer
{
public:
	EditorViewPortLayer(const std::string rName);

	virtual void Draw();
};