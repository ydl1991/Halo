#pragma once
// \file AudioSDL.h 
// TODO: File Purpose 
// Created by Dali Yi

#include ".\IAudio.h"

#include <SDL/SDL_mixer.h>
#include <unordered_map>
//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class AudioSDL 
	// TODO: Class Purpose 
	class AudioSDL final
		: public IAudio
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		AudioSDL();

		// Default Destructor 
		~AudioSDL();

		// Getters

		// Inherited via IAudio
		virtual bool Init() final override;
		virtual void Update() final override;
		virtual bool PlayMusic(const char* pFileName) final override;
		virtual bool PlaySound(const char* pFileName) final override;
		virtual void PauseCurrentMusic() final override;
		virtual void ResumeMusic() final override;
		virtual void SetVolumeForAll(int deltaVolume) final override;
		virtual int SetMusicVolume(int deltaVolume) final override;
		virtual void FadingSongTransition(const char* pFileName) final override;
		virtual std::shared_ptr<IMusic> LoadMusic(IResource* pResource) final override;
		virtual std::shared_ptr<ISoundChunk> LoadSoundChunk(IResource* pResource) final override;

		// Chunk Related
		int SetChunkVolume(const char* chunkName, int deltaVolume);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		bool m_initialized;
		bool m_isTransitionDirty;

		// static member for next song to play
		static std::string s_nextSong;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //

	};
}