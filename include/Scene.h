#ifndef OYUN_SCENE_H__
#define OYUN_SCENE_H__

#include <vector>
#include <string>
#include "Entity.h"

#define EngineExport   __declspec( dllexport )

namespace Oyun
{

	struct EngineExport Scene
	{
		std::vector<Entity*> EntityList;
	};


}

#endif //OYUN_SCENE_H__