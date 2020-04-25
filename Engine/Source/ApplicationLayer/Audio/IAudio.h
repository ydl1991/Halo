#pragma once
// \file IAudio.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <memory>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class IMusic;
	class ISoundChunk;
	class IResource;

	// \class IAudio 
	// TODO: Class Purpose 
	class IAudio
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		IAudio();

		// Default Destructor 
		virtual ~IAudio();

		// pure virtual
		virtual bool Init() = 0;
		virtual void Update() = 0;
		virtual bool PlayMusic(const char* pFileName) = 0;
		virtual bool PlaySound(const char* pFileName) = 0;
		virtual void PauseCurrentMusic() = 0;
		virtual void ResumeMusic() = 0;
		virtual void SetVolumeForAll(int deltaVolume) = 0;
		virtual int SetMusicVolume(int deltaVolume) = 0;
		virtual void FadingSongTransition(const char* pFileName) = 0;
		virtual std::shared_ptr<IMusic> LoadMusic(IResource* pResource) = 0;
		virtual std::shared_ptr<ISoundChunk> LoadSoundChunk(IResource* pResource) = 0;

		// create unique audio
		static std::unique_ptr<IAudio> Create();

	protected:
		// --------------------------------------------------------------------- //
		// Protected Member Variables
		// --------------------------------------------------------------------- //
		int m_volumeAdjMultiplier;

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