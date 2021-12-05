#ifndef OYUN_SCENE_H__
#define OYUN_SCENE_H__

#include <vector>
#include <string>
#include "Entity.h"

namespace Oyun
{

	struct OYUN_API Scene
	{
		Scene();
		std::vector<Entity*> EntityList;

		int entityCounter;

	};


}

#endif //OYUN_SCENE_H__