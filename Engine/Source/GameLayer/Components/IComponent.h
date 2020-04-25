#pragma once
// \file IComponent.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <string>
#include <memory>

#include <Utils/TinyXml/tinyxml2.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \Enum Component Category 
	enum ComponentCategory : uint8_t
	{
		// Tranform Component 
		Transform = 0,

		// Box Component 
		Box,

		// Renderable Component 
		Renderable,

		// Total Num Category
		TotalNum,
	};

	class GameUnit;
	class IGraphics;
	class IGameLayer;

	// \class IComponent 
	// TODO: Class Purpose 
	class IComponent
	{
	public:
		// Alias
		using ID = size_t;

		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		IComponent() = default;
		IComponent(std::weak_ptr<halo::GameUnit> pOwner, const char* pName);

		// Default Destructor 
		virtual ~IComponent();

		// Virtuals Interface
		virtual bool Init(tinyxml2::XMLElement* pData) = 0;
		virtual bool PostInit() { return true;  }
		virtual void Update(float deltaSeconds) { }
		virtual void RegisterWithScript() { }
		virtual ID GetID() const = 0;

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		std::weak_ptr<halo::GameUnit> m_pOwner;
		std::string m_name;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		std::shared_ptr<GameUnit> GetOwner() { return m_pOwner.lock(); }
		const std::string& GetName() { return m_name; }
	};
}