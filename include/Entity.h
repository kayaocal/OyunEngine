#pragma once
#include "Components/TransformComponent.h"

#define EngineExport   __declspec( dllexport )


class EngineExport Entity
{

public:

	Entity();

	TransformComponent Transform;

	bool Visible;

};