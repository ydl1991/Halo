#pragma once
// \file GameUnit.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <stdint.h>
#include <memory>
#include <unordered_map>
#include <type_traits>

#include <GameLayer/Components/IComponent.h>
#include <Utils/TinyXml/tinyxml2.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class Box2DPhysicsComponent;

	// \class GameUnit 
	// TODO: Class Purpose 
	class GameUnit
	{
	public:
		// Alias
		using ID = uint32_t;
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		GameUnit(ID id);

		// Default Destructor 
		virtual ~GameUnit();

		bool Init(tinyxml2::XMLElement* pData);
		bool PostInit();
		void Update(float delta);
		void Destroy();

		// Lua 
		void RegisterWithScript();

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		// Properties
		ID m_id;
		std::string m_name;
		Box2DPhysicsComponent* m_pPhysics;

		// Components
		std::unordered_map<IComponent::ID, std::unique_ptr<IComponent>> m_components;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		// ID and Name
		const std::string& GetName() const { return m_name; }
		const ID GetID() const { return m_id; }

		// Components
		void AddComponent(std::unique_ptr<IComponent> pComponent);
		template <class Component>
		Component* GetComponent();
	};

	// boolean type struct for static assert to check if a class has member variable called m_sComponentID
	template <class T, class = int>
	struct HasComponentID : std::false_type { };
	template <class T>
	struct HasComponentID <T, decltype((void)T::m_sComponentID, 0)> : std::true_type { };

	// Get Component
	template<class Component>
	inline Component* GameUnit::GetComponent()
	{
		static_assert(HasComponentID<Component>::value, "Casting Type in GetComponent() must contain a component ID!");

		return dynamic_cast<Component*>(m_components[Component::m_sComponentID].get());
	}
}