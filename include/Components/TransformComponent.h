#ifndef OYUN_TRANSFORM_COMPONENT_H__
#define OYUN_TRANSFORM_COMPONENT_H__

#include "components/Component.h"
#include <glm/glm.hpp>

namespace Oyun
{

	class EngineExport TransformComponent : public Component
	{
		glm::mat4 mModelMatrix;

	public:

		TransformComponent();
		glm::vec3 Position;
		glm::vec3 EulerRotation;
		glm::vec3 Scale;


		const glm::mat4& GetModelMatrix();

	};
}
#endif // OYUN_TRANSFORM_COMPONENT_H__