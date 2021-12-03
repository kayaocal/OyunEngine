#include "Entity.h"
#include "components/TransformComponent.h"
#include "components/StaticMeshComponent.h"
#include "subsystems/LogSubsystem.h"
#include "ModelStore.h"
#include "imgui.h"

namespace Oyun
{

	StaticMeshEntity::StaticMeshEntity(Model* mdl)
		:Entity()
	{
		mStaticMesh = AddComponent<StaticMeshComponent>(new StaticMeshComponent(this, mdl));
	}


	Entity::Entity()
		: mEntityUniqueId(0), mName("entity_01"), mVisible(true)
	{
		mTransformComponent = AddComponent<TransformComponent>(new TransformComponent(this));
		SetTickEnabled(false);
	}

	TransformComponent* Entity::GetTransform()
	{
		if(mTransformComponent != nullptr)
			return mTransformComponent;

		return GetComponent<TransformComponent>();
	}

	bool Entity::IsVisible()
	{
		return mVisible;
	}

	void Entity::BeginPlay()
	{
		LOG << "Entity::BeginPlay" << END;
	}

	void Entity::EndPlay()
	{
		LOG << "Entity::EndPlay" << END;
	}

	void Entity::Tick(float deltaTime)
	{
		LOG << "Entity::Tick" << END;
	}

	void Entity::SetTickEnabled(bool)
	{
	}

	const unsigned int Entity::GetUniqueId() const
	{
		return mEntityUniqueId;
	}

	std::string& Entity::GetName()
	{
		return mName;
	}

	void Entity::SetUniqueId(unsigned int id)
	{
		mEntityUniqueId = id;
	}

	void Entity::DrawEntityProps()
	{
		ImGui::Text("EntityName: ");
		ImGui::SameLine();
		ImGui::Text(mName.c_str());
		ImGui::Checkbox("Visible", &mVisible);

		DrawComponentProps();
	}

	void Entity::DrawComponentProps()
	{
		for (auto comp : mComponentList)
		{
			comp.second->DrawAtEditorProps();
		}
	}

	
}
