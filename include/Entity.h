#pragma once
#include <map>
#include <memory>
#include <typeindex>

#define EngineExport   __declspec( dllexport )
namespace Oyun
{
	class Component;
	class TransformComponent;

	class EngineExport Entity
	{


	public:

		Entity();


		std::map<std::type_index, Oyun::Component*> componentList;

		template <typename T>
		void AddComponent(Oyun::Component* component);


		template <typename T>
		T* GetComponent();
		
		TransformComponent* GetTransform();
		
		bool isVisible;

	};
	
	template<typename T>
	inline void Entity::AddComponent(Oyun::Component* component)
	{
		componentList.insert(std::pair < std::type_index, Oyun::Component*>(typeid(T),
			component));
	}

	template<typename T>
	inline T* Entity::GetComponent()
	{
		auto comp = componentList.find(typeid(T));
		if (comp != componentList.end())
		{
			return dynamic_cast<T*>(comp->second);
		}
		return nullptr;
	}
}