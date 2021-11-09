#pragma once

#include "Vector.h"

#define EngineExport   __declspec( dllexport )

class EngineExport TransformComponent
{
public:

	TransformComponent();
	Vec3 Position;
	Vec3 Rotation;
	Vec3 Scale;
};