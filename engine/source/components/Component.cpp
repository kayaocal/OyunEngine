#include "components\Component.h"
#include "Entity.h"

namespace Oyun
{

	Component::Component(Entity* ent)
		:mEntity(ent)
	{
	}

	Component::~Component()
	{
	}

	void Component::BeginPlay()
	{
	}

	void Component::EndPlay()
	{
	}
}



