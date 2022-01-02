#include "Components/TransformComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "Entity.h"
#include "Jsones.h"

namespace Oyun
{

	TransformComponent::TransformComponent(Entity* ent)
		:Component(ent), mModelMatrix(glm::mat4(1.0f)), 
		Position(glm::vec3(0.0f)), EulerRotation(glm::vec3(0.0f)), 
		Scale(glm::vec3(1.0f))
	{
	}

	TransformComponent::TransformComponent(const TransformComponent& c)
		: Component(c.mEntity)
	{
		Position = c.Position;
		EulerRotation = c.EulerRotation;
		Scale = c.Scale;
	}

	TransformComponent& TransformComponent::operator=(const TransformComponent& other)
	{
		Position = other.Position;
		EulerRotation = other.EulerRotation;
		Scale = other.Scale;
		mEntity = other.mEntity;
		return *this;
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

	Jsones::JObj* TransformComponent::ConvertToJson()
	{
		using namespace Jsones;

		JObj* obj = new JObj{
			JPair("Name", "TransformComponent"),
			JPair("Position", JObj{
				JPair("X", Position.x),
				JPair("Y", Position.y),
				JPair("Z", Position.z)
				}),
			JPair("Rotation", JObj{
				JPair("X", EulerRotation.x),
				JPair("Y", EulerRotation.y),
				JPair("Z", EulerRotation.z)
				}),
			JPair("Scale", JObj{
				JPair("X", Scale.x),
				JPair("Y", Scale.y),
				JPair("Z", Scale.z)
				}),
		};

		return obj;
	}

	

}