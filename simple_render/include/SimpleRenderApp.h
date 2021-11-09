#pragma once

#include "App.h"

/*
* 
*/
class SimpleRenderApp : public App
{
public:
	SimpleRenderApp(const char* name, const char* title, int width, int height);

	virtual bool Loop() override;

};