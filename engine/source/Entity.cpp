#include "Entity.h"
#include "subsystems/LogSubsystem.h"
#include "ModelStore.h"
#include "imgui.h"
#include "Jsones.h"
namespace Oyun
{
	StaticMeshEntity::StaticMeshEntity()
		:Entity()
	{
	}

	StaticMeshEntity::StaticMeshEntity(Model* mdl)
		:Entity()
	{
		mStaticMesh = AddComponent<StaticMeshComponent>(new StaticMeshComponent(this, mdl));
	}

	INIT_CLASS(StaticMeshEntity)
	INIT_CLASS(Entity)

	Entity::Entity()
		: mEntityUniqueId(0), mName("entity_01"), mVisible(true), mStatic(false)
	{
		mTransformComponent = AddComponent<TransformComponent>(new TransformComponent(this));
		SetTickEnabled(false);
	}

	const TransformComponent& Entity::GetTransform() const
	{
		return *mTransformComponent;
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
		LOG << "Entity::BeginPlay";
	}

	void Entity::EndPlay()
	{
		LOG << "Entity::EndPlay";
	}

	void Entity::Tick(float deltaTime)
	{
		LOG << "Entity::Tick";
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
		ImGui::Checkbox("Is Visible", &mVisible);
		ImGui::Checkbox("Is Static", &mStatic);

		DrawComponentProps();
	}

	void Entity::DrawComponentProps()
	{
		GetTransform()->DrawAtEditorProps();

		for (auto comp : mComponentList)
		{
			if (comp.first != typeid(TransformComponent))
			{
				comp.second->DrawAtEditorProps();
			}
		}
	}

	Jsones::JObj* Entity::ConvertToJson()
	{
		using namespace Jsones;

		JArr* arr = new JArr();
		for (auto it : mComponentList)
		{
			arr->Add(it.second->ConvertToJson());
		}

		JObj* obj = new JObj
		{
			JPair("Name", mName),
			JPair("IsVisible", mVisible),
			JPair("IsStatic", mStatic),
			JPair("Components", arr)
		};

		return obj;
	}

	
}
