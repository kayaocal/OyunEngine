#pragma once

#include "App.h"

class EditorApp : public App
{
public:
	EditorApp(const char* name, const char* title, int width, int height);

	virtual void OnDrawImGui() override;

	virtual bool Loop() override;

	void DrawMenuBar();

	void DrawMainFrame();
};