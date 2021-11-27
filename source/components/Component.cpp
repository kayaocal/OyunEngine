#include "Components\Component.h"

Oyun::Component::Component(const char* cName)
	:name( cName )
{
}

Oyun::Component::~Component()
{
}

const char* Oyun::Component::GetComponentName() const
{
	return name;
}
