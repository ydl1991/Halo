#pragma once
// \file RenderableComponent.h 
// TODO: File Purpose 
// Created by Dali Yi

#include "..\IComponent.h"
#include <memory>

#include <Utils/Color/Color.h>
#include <Utils/Math/Shapes/Shapes.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class IGameLayer;
	class ITexture;

	// \class RenderableComponent 
	// TODO: Class Purpose 
	class RenderableComponent
		: public IComponent
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
		RenderableComponent() = default;
		RenderableComponent(std::weak_ptr<halo::GameUnit>, const char* pName);

		// Default Destructor 
		virtual ~RenderableComponent();

		// Inherited via IComponent
		virtual bool Init(tinyxml2::XMLElement* pData) final override;
		ID GetID() const final override;

		// Function
		void Render(IGraphics* pGraphics);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		//------------------------------//
		//	   Normal Shape Property
		//------------------------------//
		Color m_color;

		//------------------------------//
		//		Animation Property
		//------------------------------//
		// Position and dimentions of the current frame of the sprite sheet
		Rect m_currentFrameTransformOnSheet;
		// Texture variable
		std::shared_ptr<ITexture> m_pTexture;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		Color GetColor() const { return m_color; }
		ITexture* GetTexture() const { return m_pTexture.get(); }
		Rect& GetRect() { return m_currentFrameTransformOnSheet; }
	};
}