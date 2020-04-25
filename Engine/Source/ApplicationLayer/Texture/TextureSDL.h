#pragma once
// \file TextureSDL.h 
// TODO: File Purpose 
// Created by Dali Yi
#include ".\ITexture.h"

#include <memory>

#include <SDL/SDL_render.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class TextureSDL 
	// TODO: Class Purpose 
	class TextureSDL final
		: public ITexture
	{
	public:
		// Alias
		using UniqueTexture = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		TextureSDL(IResource* pResource);

		// Default Destructor 
		virtual ~TextureSDL();

		// Init
		bool Init(SDL_Renderer* pRenderer, SDL_Surface* pSurface);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		UniqueTexture m_pTexture;
		int m_width;
		int m_height;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		// Inherited via ITexture
		virtual void* GetNativeTexture() const final override;
		// Get width and height
		int GetTextureWidth() const final override { return m_width; }
		int GetTextureHeight() const final override { return m_height; }
	};
}