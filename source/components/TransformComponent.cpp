#include "Components/TransformComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Oyun
{

	TransformComponent::TransformComponent()
		:Component(), mModelMatrix(glm::mat4(1.0f)), 
		Position(glm::vec3(0.0f)), EulerRotation(glm::vec3(0.0f)), 
		Scale(glm::vec3(1.0f))
	{
	}

	const glm::mat4& TransformComponent::GetModelMatrix()
	{
		mModelMatrix = glm::mat4(1.0f);

		mModelMatrix = glm::translate(mModelMatrix, Position);
		mModelMatrix = glm::rotate(mModelMatrix, glm::radians(EulerRotation.x), glm::vec3(1.0, 0.0, 0.0));
		mModelMatrix = glm::rotate(mModelMatrix, glm::radians(EulerRotation.y), glm::vec3(0.0, 1.0, 0.0));
		mModelMatrix = glm::rotate(mModelMatrix, glm::radians(EulerRotation.z), glm::vec3(0.0, 0.0, 1.0));

		mModelMatrix = glm::scale(mModelMatrix, Scale);

		return mModelMatrix;
	}

}