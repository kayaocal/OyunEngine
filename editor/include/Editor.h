#ifndef OYUN_EDITOR_H__
#define OYUN_EDITOR_H__

#include <Engine.h>
#include <vector>

#ifdef OyunEditor_EXPORTS
#define EDITOR_API __declspec(dllexport)
#else
#define EDITOR_API __declspec(dllimport)
#endif

namespace Oyun
{
	class GameSubsystem;
	class RenderSubsystem;
	class WorldSubsystem;
}

namespace Editor
{
	struct EDITOR_API Editor : public Oyun::Engine
	{

		Editor(Oyun::GameSubsystem* game, Oyun::RenderSubsystem* renderer, Oyun::WorldSubsystem* world);


		std::vector<Engine*> subEngineInstances;


	};
}


#endif //OYUN_EDITOR_H__