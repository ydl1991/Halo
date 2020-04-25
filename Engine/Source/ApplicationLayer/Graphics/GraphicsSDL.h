#pragma once
// \file GraphicSDL.h 
// TODO: File Purpose 
// Created by Dali Yi

#include ".\IGraphics.h"
#include <SDL/SDL_render.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class ITexture;
	struct Rect;
	struct Point;

	// \class GraphicsSDL 
	// TODO: Class Purpose 
	class GraphicsSDL final
		: public IGraphics
	{
	public:
		// Alias 
		using UniqueGraphics = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		GraphicsSDL();

		// Default Destructor 
		~GraphicsSDL();

		// Inherited via IGraphics
		bool Init(IWindow* pWindow) final override;
		bool RenderBegin(Color color) final override;
		void RenderShow() final override;

		virtual std::shared_ptr<ITexture> LoadTexture(IResource* pResource) final override;

		// Draw Override
		bool DrawTexture(ITexture* pTexture) final override;
		bool DrawTexture(ITexture* pTexture, Rect* pDestRect, float rotate = 0) final override;
		bool DrawTexture(ITexture* pTexture, Rect* pSrcRect, Rect* pDestRect, float rotate = 0) final override;
		bool DrawTexture(ITexture* pTexture, Rect* pSrcRect, Rect* pDestRect, float rotate, Point* pPoint, Flip flip) final override;

		bool TintTexture(ITexture* pTexture, Color color) final override;
		bool SetTextureTransparency(ITexture* pTexture, uint8_t alpha) final override;
		bool DrawRectangle(Rect rect, Color color) final override;

		// static function
		static SDL_Rect RectCaster(Rect* pRect);
		static SDL_Point PointCaster(Point* pPoint);
	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		UniqueGraphics m_pSDLGraphics;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:

		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
	};
}