#pragma once
// \file SoundChunkSDL.h 
// TODO: File Purpose 
// Created by Dali Yi

#include ".\ISoundChunk.h"

#include <memory>
#include <SDL/SDL_mixer.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class SoundChunkSDL 
	// TODO: Class Purpose 
	class SoundChunkSDL final : public ISoundChunk
	{
	public:
		// Alias
		using UniqueChunk = std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)>;
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		SoundChunkSDL(IResource* pResource);

		// Default Destructor 
		virtual ~SoundChunkSDL();

		// Init
		bool Init(Mix_Chunk* pSoundChunk);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		UniqueChunk m_pSoundChunk;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		// Inherited via ISoundChunk
		virtual void* GetNativeSoundChunk() const final override;

	};
}