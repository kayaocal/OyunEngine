#pragma once
#include <map>
#include <memory>
#include <typeindex>
#include <cassert>
#define EngineExport   __declspec( dllexport )
namespace Oyun
{
	class Component;
	class TransformComponent;
	
	/// @brief Base class that can be placed in scene.
	class EngineExport Entity
	{


	public:

		Entity();

		std::map<std::type_index, Oyun::Component*> componentList;

		template <typename T>
		T* AddComponent(Oyun::Component* component);

		template <typename T>
		T* GetComponent();

		TransformComponent* GetTransform();
		
		/// @brief Entity will be render if true
		bool isVisible;

		/// @brief will be called after spawned in world
		virtual void BeginPlay();

		/// @brief will be called before removing from world
		virtual void EndPlay();

		/// @brief Ticks only if SetTickEnabled is setted as true
		/// @param deltaTime 
		virtual void Tick(float deltaTime);

		/// @brief adds\removes entity to\from global tick list
		void SetTickEnabled(bool);

		const unsigned int GetUniqueId() const;
	private:

		const unsigned int mEntityUniqueId;

		TransformComponent* mTransformComponent;
	};
	
	/// @brief Entiy can only have one for each type of components!
	/// Cant add component *If entity has already same type of component*
	/// @tparam T as type
	/// @param component pointer
	template<typename T>
	inline T* Entity::AddComponent(Oyun::Component* component)
	{
		auto find = componentList.find(typeid(T));
		assert(find == componentList.end());
		
		if (find == componentList.end())
		{
			componentList.insert(std::pair < std::type_index, Oyun::Component*>(typeid(T),
				component));

			return dynamic_cast<T*>(component);
		}

		return nullptr;
	}

	
	/// @brief Returns requiested component's pointer
	/// @tparam Type of requisted component 
	/// @return can be nullptr!
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