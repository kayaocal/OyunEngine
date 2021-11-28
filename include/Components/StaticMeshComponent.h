#ifndef OYUN_STATIC_MESH_COMPONENT_H__
#define OYUN_STATIC_MESH_COMPONENT_H__
#include "components/Component.h"

namespace Oyun
{
	class EngineExport StaticMeshComponent : public Component
	{
	public:
		StaticMeshComponent(const char* model);
	};
}

#endif //OYUN_STATIC_MESH_COMPONENT_H__