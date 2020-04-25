#pragma once
// \file MusicSDL.h 
// TODO: File Purpose 
// Created by Dali Yi

#include ".\IMusic.h"

#include <memory>
#include <SDL/SDL_mixer.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class MusicSDL 
	// TODO: Class Purpose 
	class MusicSDL final : public IMusic
	{
	public:
		// Alias
		using UniqueMusic = std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)>;
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		MusicSDL(IResource* pResource);

		// Default Destructor 
		virtual ~MusicSDL();

		// Init
		bool Init(Mix_Music* pMusic);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		UniqueMusic m_pMusic;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		// Inherited via IMusic
		virtual void* GetNativeMusic() const final override;

	};
}