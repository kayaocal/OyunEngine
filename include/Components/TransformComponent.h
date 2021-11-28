#ifndef OYUN_TRANSFORM_COMPONENT_H__
#define OYUN_TRANSFORM_COMPONENT_H__

#include "components/Component.h"
#include <glm/glm.hpp>
#define EngineExport   __declspec( dllexport )

namespace Oyun
{

	class EngineExport TransformComponent : public Component
	{
		glm::mat4 mModelMatrix;

	public:

		TransformComponent(const char* name);
		glm::vec3 Position;
		glm::vec3 EulerRotation;
		glm::vec3 Scale;


		const glm::mat4& GetModelMatrix();

		// Inherited via Component
		virtual void BeginPlay() override;
		virtual void EndPlay() override;
	};
}
#endif // OYUN_TRANSFORM_COMPONENT_H__