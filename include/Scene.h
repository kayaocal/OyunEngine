#pragma once

#include <vector>
#include <string>

#define EngineExport   __declspec( dllexport )

namespace Oyun
{

	struct EngineExport Scene
	{
		class Entity* Entity;

		Scene* Parent;
		std::vector<Scene*> Child;
	};


}