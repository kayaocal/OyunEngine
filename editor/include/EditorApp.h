#pragma once

#include "App.h"

class EditorApp : public App
{
public:
	EditorApp(const char* name, const char* title);
	virtual void OnDrawImGui() override;

	virtual bool Loop() override;
};