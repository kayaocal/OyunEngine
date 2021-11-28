#ifndef OYUN_SCENE_H__
#define OYUN_SCENE_H__

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

#endif //OYUN_SCENE_H__