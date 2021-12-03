#include "components/StaticMeshComponent.h"
#include <ModelStore.h>
#include "imgui.h"

namespace Oyun
{
	StaticMeshComponent::StaticMeshComponent(Entity* ent, Model* staticMesh)
		:Component(ent), mModel(staticMesh)
	{

	}

	void StaticMeshComponent::Draw(float* view, float* proj, float* transform)
	{
		mModel->Draw(view, proj, transform);
	}

	void StaticMeshComponent::DrawAtEditorProps()
	{
		if (ImGui::CollapsingHeader("StaticMesh"))
		{
			ImGui::Text(mModel->path.c_str());
		}
	}

}