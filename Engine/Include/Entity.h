#ifndef OYUN_ENTITY_H__
#define OYUN_ENTITY_H__

#include <map>
#include <memory>
#include <typeindex>
#include <cassert>
#include <string>
#include "Components/TransformComponent.h"
#include "Components/StaticMeshComponent.h"
#include "OyunCore.h"

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

namespace Jsones
{
	struct JObj;
}
namespace Oyun
{
	class Component;
	class StaticMeshComponent;

	
	
	/// @brief Base class that can be placed in scene.
	class OYUN_API Entity : public BaseClass
	{

	public:
		OYUNCLASS(Entity);

		Entity();


		template <typename T>
		T* AddComponent(Oyun::Component* component);

		template <typename T>
		T* GetComponent();

		TransformComponent* GetTransform();

		const TransformComponent& GetTransform() const;
		
		/// @brief Entity will be render if true
		bool IsVisible();

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

		std::string& GetName();

		void SetUniqueId(unsigned int id);

		/// @brief To draw entity specs at editor properties window
		virtual void DrawEntityProps();

		/// @brief To draw entity's owned components at editor properties window
		void DrawComponentProps();

		virtual Jsones::JObj* ConvertToJson();
	private:

		std::map<std::type_index, Oyun::Component*> mComponentList;

		unsigned int mEntityUniqueId;

		std::string mName;

		TransformComponent* mTransformComponent;

		bool mVisible;

		bool mStatic;
	};
	
	/// @brief Entiy can only have one for each type of components!
	/// Cant add component *If entity has already same type of component*
	/// @tparam T as type
	/// @param component pointer
	template<typename T>
	inline T* Entity::AddComponent(Oyun::Component* component)
	{
		auto find = mComponentList.find(typeid(T));
		assert(find == mComponentList.end());
		
		if (find == mComponentList.end())
		{
			mComponentList.insert(std::pair < std::type_index, Oyun::Component*>(typeid(T),
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
		auto comp = mComponentList.find(typeid(T));
		if (comp != mComponentList.end())
		{
			return dynamic_cast<T*>(comp->second);
		} 
		return nullptr;
	}

	///****************************************************************************
	///************************ STATIC MESH ENTITY ********************************
	///****************************************************************************

	class Model;

	class OYUN_API StaticMeshEntity : public Entity
	{
	public:
		
		OYUNCLASS(StaticMeshEntity);
		
		StaticMeshEntity();
		StaticMeshEntity(Model*);


	private:
		StaticMeshComponent* mStaticMesh;
	};
}

#endif // OYUN_ENTITY_H__