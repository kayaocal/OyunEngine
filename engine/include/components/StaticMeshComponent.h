#ifndef OYUN_STATIC_MESH_COMPONENT_H__
#define OYUN_STATIC_MESH_COMPONENT_H__

#include "components/Component.h"

namespace Oyun
{

	class Model;
	class OYUN_API StaticMeshComponent : public Component
	{
	public:
		StaticMeshComponent(Model*);

		void Draw(float* view, float* proj, float* transform);

	private:
		Model* mModel;

	};
}

#endif //OYUN_STATIC_MESH_COMPONENT_H__