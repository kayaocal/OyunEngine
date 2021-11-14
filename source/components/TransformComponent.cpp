#include "Components/TransformComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TransformComponent::TransformComponent()
{
	Position = glm::vec3(0.0f);
	EulerRotation = glm::vec3(0.0f);
	Scale = glm::vec3(0.0f);
}

const glm::mat4& TransformComponent::GetModelMatrix()
{
	_ModelMat = glm::mat4(1.0f);

	_ModelMat = glm::translate(_ModelMat, Position);
	_ModelMat = glm::rotate(_ModelMat, glm::radians(EulerRotation.x), glm::vec3(1.0, 0.0, 0.0));
	_ModelMat = glm::rotate(_ModelMat, glm::radians(EulerRotation.y), glm::vec3(0.0, 1.0, 0.0));
	_ModelMat = glm::rotate(_ModelMat, glm::radians(EulerRotation.z), glm::vec3(0.0, 0.0, 1.0));

	_ModelMat = glm::scale(_ModelMat, Scale);

	return _ModelMat;
}
