#ifndef OYUN_WORLD_SUBSYSTEM_H__
#define OYUN_WORLD_SUBSYSTEM_H__

#include "EngineSubsytem.h"
#include <memory>

namespace Oyun
{
	struct Scene;
	class Entity;
	struct Engine;

	class OYUN_API WorldSubsystem : public EngineSubsytem<WorldSubsystem>
	{
	public:
		
		WorldSubsystem();
		~WorldSubsystem();


		virtual void StartUp() override;
		virtual void ShutDown() override;

		void SetEngine(Engine*);
			
		void AddEntityToScene(Entity* ent);
		Entity* GetEntityByUniqueId(unsigned int id);

		Scene* GetScene() const;

	private:
		Scene* mScene;

		Engine* mEngine;

	};
}

#endif //OYUN_WORLD_SUBSYSTEM_H__