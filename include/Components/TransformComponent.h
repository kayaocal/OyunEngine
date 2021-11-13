#pragma once

#include <glm/glm.hpp>
#define EngineExport   __declspec( dllexport )

class EngineExport TransformComponent
{
	glm::mat4 _ModelMat;

public:

	TransformComponent();
	glm::vec3 Position;
	glm::vec3 EulerRotation;
	glm::vec3 Scale;


	const glm::mat4& GetModelMatrix();
};