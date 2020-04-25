#include "GraphicsSDL.h"


#include <SDL/SDL_image.h>
#include <cassert>

#include <ApplicationLayer/Window/IWindow.h>
#include <ApplicationLayer/Texture/TextureSDL.h>
#include <ApplicationLayer/Texture/ITexture.h>
#include <GameLayer/Resource/IResource.h>
#include <Utils/Log.h>

using halo::GraphicsSDL;

GraphicsSDL::GraphicsSDL()
	: m_pSDLGraphics{nullptr, nullptr}
{
	
}

GraphicsSDL::~GraphicsSDL()
{
	
}

bool halo::GraphicsSDL::Init(IWindow* pWindow)
{
	SDL_Window* pSDLWindow = reinterpret_cast<SDL_Window*>(pWindow->GetNativeWindow());

	// Create the Graphic Renderer
	m_pSDLGraphics = UniqueGraphics(SDL_CreateRenderer(pSDLWindow, 
													   -1, 
													   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
									&SDL_DestroyRenderer);
	if (!m_pSDLGraphics)
	{
		LOG_ERROR("Failed to Create SDL Graphic Renderer.");
		return false;
	}

	return true;
}

bool halo::GraphicsSDL::RenderBegin(Color color)
{
	// Set the background color
	SDL_SetRenderDrawColor(m_pSDLGraphics.get(), color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_pSDLGraphics.get());
	return true;
}

void halo::GraphicsSDL::RenderShow()
{
	SDL_RenderPresent(m_pSDLGraphics.get());
}

std::shared_ptr<halo::ITexture> halo::GraphicsSDL::LoadTexture(IResource* pResource)
{
	const char* filename = pResource->GetFilepath().c_str();

	if (!m_pSDLGraphics)
	{
		return nullptr;
	}

	// Create object form raw data in memory
	SDL_RWops* pOps = SDL_RWFromConstMem(pResource->GetData().data(), (int)pResource->GetData().size());
	// read surface from memory
	SDL_Surface* pSurface = IMG_Load_RW(pOps, 0);

	// create surface
	if (!pSurface)
	{
		LOG_ERROR("Failed to load image.");
		return nullptr;
	}

	// create texture instance using shared pointer because it can be used by multiple objects
	TextureSDL* pTexture = new TextureSDL(pResource);
	// init texture from the surface
	if (!pTexture->Init(m_pSDLGraphics.get(), pSurface))
	{
		SDL_FreeSurface(pSurface);
		delete pTexture;
		return nullptr;
	}

	SDL_FreeSurface(pSurface);
	return std::shared_ptr<TextureSDL>(pTexture);
}

//------------------------------------------//
//				Draw BackGround
//------------------------------------------//
bool halo::GraphicsSDL::DrawTexture(ITexture* pTexture)
{
	// cast texture and rects
	SDL_Texture* pSDLTexture = reinterpret_cast<SDL_Texture*>(pTexture->GetNativeTexture());

	// Draw Texture
	if (SDL_RenderCopy(m_pSDLGraphics.get(), pSDLTexture, nullptr, nullptr))
	{
		LOG_ERROR("Failed to draw texture.");
		return false;
	}
	return true;
}

//------------------------------------------//
//			Draw Entire Image
//------------------------------------------//
bool halo::GraphicsSDL::DrawTexture(ITexture* pTexture, Rect* pDestRect, float rotate)
{
	// Assert paramater to be non-null
	assert(((void)"Cannot Have Null Ptr Rect", pDestRect));

	// cast texture and rects
	SDL_Texture* pSDLTexture = reinterpret_cast<SDL_Texture*>(pTexture->GetNativeTexture());
	SDL_Rect SDLDestRect = RectCaster(pDestRect);

	// Draw Texture
	if (SDL_RenderCopyEx(m_pSDLGraphics.get(), pSDLTexture, nullptr, &SDLDestRect, rotate, nullptr, SDL_RendererFlip::SDL_FLIP_NONE))
	{
		LOG_ERROR("Failed to draw texture.");
		return false;
	}
	return true;
}

//------------------------------------------//
//	Draw Texture Spritesheet with Rotation
//------------------------------------------//
bool halo::GraphicsSDL::DrawTexture(ITexture* pTexture, Rect* pSrcRect, Rect* pDestRect, float rotate)
{
	// Assert paramater to be non-null
	assert(((void)"Cannot Have Null Ptr Rect", pSrcRect));
	assert(((void)"Cannot Have Null Ptr Rect", pDestRect));

	// cast texture and rects
	SDL_Texture* pSDLTexture = reinterpret_cast<SDL_Texture*>(pTexture->GetNativeTexture());
	SDL_Rect SDLSrcRect = RectCaster(pSrcRect);
	SDL_Rect SDLDestRect = RectCaster(pDestRect);

	// Draw Texture
	if (SDL_RenderCopyEx(m_pSDLGraphics.get(), pSDLTexture, &SDLSrcRect, &SDLDestRect, rotate, nullptr, SDL_RendererFlip::SDL_FLIP_NONE))
	{
		LOG_ERROR("Failed to draw texture.");
		return false;
	}
	return true;
}

//------------------------------------------//
//	Draw Texture with rotation and flip
//------------------------------------------//
bool halo::GraphicsSDL::DrawTexture(ITexture* pTexture, Rect* pSrcRect, Rect* pDestRect, float rotate, Point* pPoint, Flip flip)
{
	// Assert paramater to be non-null
	assert(((void)"Cannot Have Null Ptr Rect", pSrcRect));
	assert(((void)"Cannot Have Null Ptr Rect", pDestRect));
	assert(((void)"Cannot Have Null Ptr Point", pPoint));

	// cast texture and rects
	SDL_Texture* pSDLTexture = reinterpret_cast<SDL_Texture*>(pTexture->GetNativeTexture());
	SDL_Rect SDLSrcRect = RectCaster(pSrcRect);
	SDL_Rect SDLDestRect = RectCaster(pDestRect);
	SDL_Point SDLPoint = PointCaster(pPoint);
	SDL_RendererFlip sdlFlip = SDL_FLIP_NONE;

	// Check Flip
	switch (flip)
	{
	case Flip::kHorizontalFlip:
		sdlFlip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;
		break;
	case Flip::kVerticalFlip:
		sdlFlip = SDL_RendererFlip::SDL_FLIP_VERTICAL;
		break;
	default:
		break;
	}

	// Draw Texture
	if (SDL_RenderCopyEx(m_pSDLGraphics.get(), pSDLTexture, &SDLSrcRect, &SDLDestRect, rotate, &SDLPoint, sdlFlip))
	{
		LOG_ERROR("Failed to draw texture.");
		return false;
	}
	return true;
}

//------------------------------------------//
//		Tint Texture
//------------------------------------------//
bool halo::GraphicsSDL::TintTexture(ITexture* pTexture, Color color)
{
	// call SDL function
	if (SDL_SetTextureColorMod(reinterpret_cast<SDL_Texture*>(pTexture->GetNativeTexture()), color.r, color.g, color.b) == -1)
	{
		LOG_ERROR("Failed to Tint texture.");
		return false;
	}

	return true;
}

//------------------------------------------//
//		Set Texture Transparency
//------------------------------------------//
bool halo::GraphicsSDL::SetTextureTransparency(ITexture* pTexture, uint8_t alpha)
{
	// call SDL function
	if (SDL_SetTextureAlphaMod(reinterpret_cast<SDL_Texture*>(pTexture->GetNativeTexture()), alpha) == -1)
	{
		LOG_ERROR("Failed to set texture transparency.");
		return false;
	}

	return true;
}

//------------------------------------------//
//		Render a Simple Rectangle
//------------------------------------------//
bool halo::GraphicsSDL::DrawRectangle(Rect rect, Color color)
{
	SDL_Rect SDLrect = { rect.x, rect.y, rect.w, rect.h };
	SDL_SetRenderDrawColor(m_pSDLGraphics.get(), color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(m_pSDLGraphics.get(), &SDLrect);
	return true;
}

//------------------------------------------//
//		Cast Rect to SDL Rect
//------------------------------------------//
SDL_Rect halo::GraphicsSDL::RectCaster(Rect* pRect)
{
	SDL_Rect rect;
	rect.x = pRect->x;
	rect.y = pRect->y;
	rect.w = pRect->w;
	rect.h = pRect->h;

	return rect;
}

//------------------------------------------//
//		Cast Point to SDL Point
//------------------------------------------//
SDL_Point halo::GraphicsSDL::PointCaster(Point* pPoint)
{
	SDL_Point point;
	point.x = pPoint->x;
	point.y = pPoint->y;

	return point;
}
