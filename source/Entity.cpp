#include "Entity.h"
#include "components/TransformComponent.h"
namespace Oyun
{
	Entity::Entity()
		:isVisible(true)
	{
		AddComponent<TransformComponent>(new TransformComponent("Transform"));
	}

	TransformComponent* Entity::GetTransform()
	{
		return GetComponent<TransformComponent>();
	}
	
}
