#ifndef OYUN_WORLD_SUBSYSTEM_H__
#define OYUN_WORLD_SUBSYSTEM_H__

#include "EngineSubsytem.h"
#include <memory>

namespace Oyun
{
	class Scene;
	class Entity;

	class OYUN_API WorldSubsystem : public EngineSubsytem<WorldSubsystem>
	{
		WorldSubsystem(int width, int height);
		~WorldSubsystem();

		Scene* mScene;

	public:

		static WorldSubsystem* system;

		static WorldSubsystem* GetPtr();
		static WorldSubsystem& Get();
		static WorldSubsystem& Instantiate(int width = 800, int height = 600);

		virtual void StartUp() override;
		virtual void ShutDown() override;

		
		void AddEntityToScene(Entity* ent);
		Entity* GetEntityByUniqueId(unsigned int id);

		Scene* GetScene() const;


	};

}

#endif //OYUN_WORLD_SUBSYSTEM_H__