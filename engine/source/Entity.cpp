#include "Entity.h"
#include "components/TransformComponent.h"
#include "components/StaticMeshComponent.h"
#include "subsystems/LogSubsystem.h"
#include "ModelStore.h"
namespace Oyun
{

	StaticMeshEntity::StaticMeshEntity(Model* mdl)
		:Entity()
	{
		mStaticMesh = AddComponent<StaticMeshComponent>(new StaticMeshComponent(mdl));
	}


	Entity::Entity()
		:isVisible(true), mEntityUniqueId(0)
	{
		mTransformComponent = AddComponent<TransformComponent>(new TransformComponent());
		SetTickEnabled(false);
	}

	TransformComponent* Entity::GetTransform()
	{
		if(mTransformComponent != nullptr)
			return mTransformComponent;

		return GetComponent<TransformComponent>();
	}

	void Entity::BeginPlay()
	{
		LOG << "Entity::BeginPlay" << END;
	}

	void Entity::EndPlay()
	{
		LOG << "Entity::EndPlay" << END;
	}

	void Entity::Tick(float deltaTime)
	{
		LOG << "Entity::Tick" << END;
	}

	void Entity::SetTickEnabled(bool)
	{
	}

	const unsigned int Entity::GetUniqueId() const
	{
		return mEntityUniqueId;
	}


	
}
