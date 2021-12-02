#include <cassert>
#include "subsystems/WorldSubsystem.h"
#include "subsystems\LogSubsystem.h"
#include "Scene.h"

namespace Oyun
{
	WorldSubsystem* WorldSubsystem::system = nullptr;

	WorldSubsystem::WorldSubsystem(int width, int height)
		:EngineSubsytem()
	{
		mScene = new Scene();
	}

	WorldSubsystem::~WorldSubsystem()
	{
		system = nullptr;
	}

	WorldSubsystem* WorldSubsystem::GetPtr()
	{
		return system;
	}

	WorldSubsystem& WorldSubsystem::Get()
	{
		return *system;
	}

	WorldSubsystem& WorldSubsystem::Instantiate(int width, int height)
	{
		assert(system == nullptr);
		system = new WorldSubsystem(width, height);
		return *system;
	}


	void WorldSubsystem::StartUp()
	{
		LOG << "WorldSubsystem Startup" << END;

	}

	void WorldSubsystem::ShutDown()
	{
		LOG << "WorldSubsystem Shutdown" << END;
		delete this;
	}
	void WorldSubsystem::AddEntityToScene(Entity* ent)
	{
		mScene->EntityList.push_back(ent);
	}
	
	Entity* WorldSubsystem::GetEntityByUniqueId(unsigned int id)
	{
		for (auto ent : mScene->EntityList)
		{
			if (ent->GetUniqueId() == id)
			{
				return ent;
			}
		}
		return nullptr;
	}

	Scene* WorldSubsystem::GetScene() const
	{
		return mScene;
	}
}
