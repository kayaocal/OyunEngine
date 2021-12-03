#ifndef OYUN_TRANSFORM_COMPONENT_H__
#define OYUN_TRANSFORM_COMPONENT_H__

#include "components/Component.h"
#include <glm/glm.hpp>

namespace Oyun
{
	class Entity;

	class OYUN_API TransformComponent : public Component
	{
		glm::mat4 mModelMatrix;

	public:

		TransformComponent(Entity*);
		glm::vec3 Position;
		glm::vec3 EulerRotation;
		glm::vec3 Scale;


		glm::mat4& GetModelMatrix();


		// Inherited via Component
		virtual void DrawAtEditorProps() override;

	};
}
#endif // OYUN_TRANSFORM_COMPONENT_H__