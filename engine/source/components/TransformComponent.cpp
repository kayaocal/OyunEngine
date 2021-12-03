#include "Components/TransformComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "Entity.h"

namespace Oyun
{

	TransformComponent::TransformComponent(Entity* ent)
		:Component(ent), mModelMatrix(glm::mat4(1.0f)), 
		Position(glm::vec3(0.0f)), EulerRotation(glm::vec3(0.0f)), 
		Scale(glm::vec3(1.0f))
	{
	}

	glm::mat4& TransformComponent::GetModelMatrix()
	{
		mModelMatrix = glm::mat4(1.0f);

		mModelMatrix = glm::translate(mModelMatrix, Position);
		mModelMatrix = glm::rotate(mModelMatrix, glm::radians(EulerRotation.x), glm::vec3(1.0, 0.0, 0.0));
		mModelMatrix = glm::rotate(mModelMatrix, glm::radians(EulerRotation.y), glm::vec3(0.0, 1.0, 0.0));
		mModelMatrix = glm::rotate(mModelMatrix, glm::radians(EulerRotation.z), glm::vec3(0.0, 0.0, 1.0));

		mModelMatrix = glm::scale(mModelMatrix, Scale);

		return mModelMatrix;
	}

	float transformPos[3];
	float transformRot[3];
	float transformScale[3];
	void TransformComponent::DrawAtEditorProps()
	{
		if (ImGui::CollapsingHeader("Transform"))
		{
			transformPos[0] = Position.x;
			transformPos[1] = Position.y;
			transformPos[2] = Position.z;

			transformRot[0] = EulerRotation.x;
			transformRot[1] = EulerRotation.y;
			transformRot[2] = EulerRotation.z;

			transformScale[0] = Scale.x;
			transformScale[1] = Scale.y;
			transformScale[2] = Scale.z;

			ImGui::DragFloat3("Position: ", transformPos, 0.01f, -FLT_MAX, FLT_MAX);
			ImGui::DragFloat3("Rotation: ", transformRot, 0.01f, -FLT_MAX, FLT_MAX);
			ImGui::DragFloat3("Scale: ", transformScale, 0.01f, -FLT_MAX, FLT_MAX);

			Position.x = transformPos[0];
			Position.y = transformPos[1];
			Position.z = transformPos[2];

			EulerRotation.x = transformRot[0];
			EulerRotation.y = transformRot[1];
			EulerRotation.z = transformRot[2];

			Scale.x = transformScale[0];
			Scale.y = transformScale[1];
			Scale.z = transformScale[2];
		}
	}

}