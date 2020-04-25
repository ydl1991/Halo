#include "TextureSDL.h"

#include <Utils/Log.h>


using halo::TextureSDL;

TextureSDL::TextureSDL(IResource* pResource)
	: ITexture(pResource)
	, m_pTexture{nullptr, nullptr}
	, m_width{ }
	, m_height{ }
{
	
}

TextureSDL::~TextureSDL()
{
	
}

bool halo::TextureSDL::Init(SDL_Renderer* pRenderer, SDL_Surface* pSurface)
{
	// create SDL Texture from SDL Surface
	m_pTexture = UniqueTexture(SDL_CreateTextureFromSurface(pRenderer, pSurface), &SDL_DestroyTexture);

	if (!m_pTexture)
	{
		LOG_ERROR("Failed to Create SDL Texute.");
		return false;
	}

	// record texture width and height
	m_width = pSurface->w;
	m_height = pSurface->h;

	return true;
}

void* halo::TextureSDL::GetNativeTexture() const
{
	return m_pTexture.get();
}
