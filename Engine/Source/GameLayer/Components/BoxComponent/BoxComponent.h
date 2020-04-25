#pragma once
// \file BoxComponent.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <GameLayer/Components/IComponent.h>
#include <GameLayer/Components/TransformComponent/TransformComponent.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class IGameLayer;

	// \class BoxComponent 
	// TODO: Class Purpose 
	class BoxComponent :
		public halo::IComponent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		static const ID m_sComponentID;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		BoxComponent() = default;
		BoxComponent(std::weak_ptr<halo::GameUnit>, const char* pName);

		// Default Destructor 
		virtual ~BoxComponent();

		// Inherited via IComponent
		bool Init(tinyxml2::XMLElement* pData) final override;
		bool PostInit() final override;
		ID GetID() const final override;

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		float m_width;
		float m_height;
		TransformComponent* m_pTransform;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		float GetWidth() const { return m_width; }
		float GetHeight() const { return m_height; }
		float GetX() const { return m_pTransform->GetX(); }
		float GetY() const { return m_pTransform->GetY(); }
	};

}