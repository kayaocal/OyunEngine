#ifndef OYUN_TRANSFORM_COMPONENT_H__
#define OYUN_TRANSFORM_COMPONENT_H__

#include "components/Component.h"
#include <glm/glm.hpp>
#include "cereal/archives/json.hpp"
#include "cereal/types/tuple.hpp"

namespace Oyun
{
	class Entity;

	class OYUN_API TransformComponent : public Component
	{
		glm::mat4 mModelMatrix;

	public:


		TransformComponent(Entity*);

		TransformComponent(const TransformComponent&);

		TransformComponent& operator=(const TransformComponent& other);

		glm::vec3 Position;
		glm::vec3 EulerRotation;
		glm::vec3 Scale;


		glm::mat4& GetModelMatrix();



		template<class Archive>
		void serialize(Archive& archive) const
		{
			auto pos = std::tuple<float, float, float>(this->Position.x, this->Position.y, this->Position.z);
			auto rot = std::tuple<float, float, float>(EulerRotation.x, EulerRotation.y, EulerRotation.z);
			auto scale = std::tuple<float, float, float>(Scale.x, Scale.y, Scale.z);
			
			archive(cereal::make_nvp("Position", pos),
					cereal::make_nvp("Rotation", rot),
					cereal::make_nvp("Scale", scale));
		}

		// Inherited via Component
		virtual void DrawAtEditorProps() override;

	};
}

#endif // OYUN_TRANSFORM_COMPONENT_H__