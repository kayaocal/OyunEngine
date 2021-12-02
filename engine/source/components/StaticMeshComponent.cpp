#include "components/StaticMeshComponent.h"
#include <ModelStore.h>

namespace Oyun
{
	StaticMeshComponent::StaticMeshComponent(Model* staticMesh)
		:Component(), mModel(staticMesh)
	{

	}

	void StaticMeshComponent::Draw(float* view, float* proj, float* transform)
	{
		mModel->Draw(view, proj, transform);
	}

}