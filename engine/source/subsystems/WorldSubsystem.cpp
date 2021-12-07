#include <cassert>
#include "subsystems/WorldSubsystem.h"
#include "subsystems\LogSubsystem.h"
#include "Scene.h"

namespace Oyun
{

	WorldSubsystem::WorldSubsystem()
		:EngineSubsytem(),mEngine(nullptr)
	{
		mScene = new Scene();
	}

	WorldSubsystem::~WorldSubsystem()
	{
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

	void WorldSubsystem::SetEngine(Engine* engine)
	{
		mEngine = engine;
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
