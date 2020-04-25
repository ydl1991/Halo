#pragma once
// \file IGraphics.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <memory>
#include <Utils/Color/Color.h>
#include <Utils/Math/Shapes/Shapes.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class IWindow;
	class ITexture;
	class IResource;

	// \class IGraphics 
	// TODO: Class Purpose 
	class IGraphics
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		enum class Flip : uint8_t
		{
			kNoFlip = 0,
			kHorizontalFlip,
			kVerticalFlip
		};

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		IGraphics();

		// Default Destructor 
		virtual ~IGraphics();

		// Pure Virtuals
		virtual bool Init(IWindow* pWindow) = 0;
		virtual bool RenderBegin(Color color) = 0;
		virtual void RenderShow() = 0;
		virtual std::shared_ptr<ITexture> LoadTexture(IResource* pResource) = 0;

		// Draw
		virtual bool DrawTexture(ITexture* pTexture) = 0;
		virtual bool DrawTexture(ITexture* pTexture, Rect* pDestRect, float rotate = 0) = 0;
		virtual bool DrawTexture(ITexture* pTexture, Rect* pSrcRect, Rect* pDestRect, float rotate = 0) = 0;
		virtual bool DrawTexture(ITexture* pTexture, Rect* pSrcRect, Rect* pDestRect, float rotate, Point* pPoint, Flip flip) = 0;
		
		virtual bool TintTexture(ITexture* pTexture, Color color) = 0;
		virtual bool SetTextureTransparency(ITexture* pTexture, uint8_t alpha) = 0;
		virtual bool DrawRectangle(Rect rect, Color color) = 0;

		// Create IGraphics Unique Pointer
		static std::unique_ptr<IGraphics> Create();

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //


	};
}