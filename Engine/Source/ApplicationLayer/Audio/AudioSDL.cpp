#include "AudioSDL.h"

#include <SDL/SDL.h>

// Log
#include <Utils/Log.h>
// Resource
#include <GameLayer/Resource/IResource.h>
#include <GameLayer/Resource/ResourceCache.h>
// Sound Chunk
#include <ApplicationLayer/Sound/Chunk/SoundChunkSDL.h>
#include <ApplicationLayer/Sound/Chunk/ISoundChunk.h>
// Music
#include <ApplicationLayer/Sound/Music/IMusic.h>
#include <ApplicationLayer/Sound/Music/MusicSDL.h>

using halo::AudioSDL;

//--------------------------------------//
//	Init Static Variable Next Song Path
//--------------------------------------//
std::string AudioSDL::s_nextSong = "";

AudioSDL::AudioSDL()
    : m_initialized{ false }
	, m_isTransitionDirty{ false }
{
	
}

AudioSDL::~AudioSDL()
{
    if (m_initialized)
    {
        Mix_CloseAudio();
        Mix_Quit();
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }
}

bool halo::AudioSDL::Init()
{
    if (SDL_InitSubSystem(SDL_INIT_AUDIO))
    {
        LOG_ERROR("Failed to init SDL Audio.");
        return false;
    }

    m_initialized = true;

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
        MIX_DEFAULT_CHANNELS, 1024))
    {
        LOG_ERROR("Failed to open SDL Mixer.");
        return false;
    }

    int mixFlags = MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;
    if (Mix_Init(mixFlags) != mixFlags)
    {
        LOG_ERROR("Failed to init SDL Mixer with all formats requested.");
        return false;
    }

    return true;

}

void halo::AudioSDL::Update()
{
	// fade out music to finish 3 seconds from now
	if (m_isTransitionDirty)
	{
		if (!Mix_PlayingMusic())
		{
			m_isTransitionDirty = false;
			PlayMusic(s_nextSong.c_str());
		}
	}
}

bool halo::AudioSDL::PlayMusic(const char* pFileName)
{
	auto pMusic = ResourceCache::Get().AcquireResource<IMusic>(pFileName);

    if (!pMusic)
    {
        LOG_ERROR("Failed to load music - ", pFileName);
        return false;
    }

    if (Mix_PlayMusic(reinterpret_cast<Mix_Music*>(pMusic->GetNativeMusic()), -1))
    {
        LOG_ERROR("Failed to play music - ", pFileName);
        return false;
    }

    return true;
}

bool halo::AudioSDL::PlaySound(const char* pFileName)
{
	auto pSoundChunk = ResourceCache::Get().AcquireResource<ISoundChunk>(pFileName);

	if (!pSoundChunk)
	{
		LOG_ERROR("Failed to Load Sound Chunk to Play! - %s", pFileName);
		return false;
	}

    Mix_PlayChannel(-1, reinterpret_cast<Mix_Chunk*>(pSoundChunk->GetNativeSoundChunk()), 0);
    return true;
}

void halo::AudioSDL::PauseCurrentMusic()
{
	Mix_PauseMusic();
}

void halo::AudioSDL::ResumeMusic()
{
	Mix_ResumeMusic();
}

//---------------------------------------------------------------------------------------------------//
//	Set specific volume to all channels
//	Param:
//		volume - SDL volume ranged between 0 and 128
//---------------------------------------------------------------------------------------------------//
void halo::AudioSDL::SetVolumeForAll(int deltaVolume)
{
	int cur = Mix_Volume(-1, -1);
	Mix_Volume(-1, cur + deltaVolume * m_volumeAdjMultiplier);
}

//---------------------------------------------------------------------------------------------------//
//	Set specific volume to current music
//	Param:
//		volume - SDL volume ranged between 0 and 128
//	Return:
//		previous volume of the music
//---------------------------------------------------------------------------------------------------//
int halo::AudioSDL::SetMusicVolume(int deltaVolume)
{
	int cur = Mix_VolumeMusic(-1);
	return Mix_VolumeMusic(cur + deltaVolume * m_volumeAdjMultiplier);
}

//---------------------------------------------------------------------------------------------------//
//	Set specific volume to specific chunk
//	Param:
//		chunkName - the name of the chunk that is gonna change volume to
//		volume - SDL volume ranged between 0 and 128
//	Return:
//		previous volume of the chunk, -1 if chunk does not exist
//---------------------------------------------------------------------------------------------------//
int halo::AudioSDL::SetChunkVolume(const char* pChunkFileName, int deltaVolume)
{
	auto pSoundChunk = ResourceCache::Get().AccessExistingResources<ISoundChunk>(pChunkFileName);
	if (!pSoundChunk)
	{
		LOG_ERROR("Chunk does not exist. Chunk path - ", pChunkFileName);
		return -1;
	}

	Mix_Chunk* pChunk = reinterpret_cast<Mix_Chunk*>(pSoundChunk->GetNativeSoundChunk());

	int cur = Mix_VolumeChunk(pChunk, -1);
	return Mix_VolumeChunk(pChunk, cur + deltaVolume * m_volumeAdjMultiplier);
}

//---------------------------------------------------------------------------------------------------//
// Activate Song Fading Trans
//	Param:
//		pFileName - the file name of the music that is gonna play next
//---------------------------------------------------------------------------------------------------//
void halo::AudioSDL::FadingSongTransition(const char* pFileName)
{
	Mix_FadeOutMusic(3000);
	m_isTransitionDirty = true;
	s_nextSong = pFileName;
}

//---------------------------------------------------------------------------------------------------//
// Load Music Files
//	Param:
//		pResources - a resource pack that stores the sound info
//---------------------------------------------------------------------------------------------------//
std::shared_ptr<halo::IMusic> halo::AudioSDL::LoadMusic(IResource* pResource)
{
	const char* filename = pResource->GetFilepath().c_str();

	// Create object form raw data in memory
	SDL_RWops* pOps = SDL_RWFromConstMem(pResource->GetData().data(), (int)pResource->GetData().size());
	// read Mix Music from memory
	Mix_Music* pMixMusic = Mix_LoadMUS_RW(pOps, 0);

	// create Music instance using shared pointer because it can be used by multiple objects
	MusicSDL* pMusic = new MusicSDL(pResource);
	// init texture from the surface
	if (!pMusic->Init(pMixMusic))
	{
		Mix_FreeMusic(pMixMusic);
		delete pMusic;
		return nullptr;
	}

	return std::shared_ptr<MusicSDL>(pMusic);
}

//---------------------------------------------------------------------------------------------------//
// Load Chunk Files
//	Param:
//		pResources - a resource pack that stores the sound info
//---------------------------------------------------------------------------------------------------//
std::shared_ptr<halo::ISoundChunk> halo::AudioSDL::LoadSoundChunk(IResource* pResource)
{
	const char* filename = pResource->GetFilepath().c_str();

	// Create object form raw data in memory
	SDL_RWops* pOps = SDL_RWFromConstMem(pResource->GetData().data(), (int)pResource->GetData().size());
	// read Mix Chunk from memory
	Mix_Chunk* pMixChunk = Mix_LoadWAV_RW(pOps, 0);

	// create Chunk instance using shared pointer because it can be used by multiple objects
	SoundChunkSDL* pChunk = new SoundChunkSDL(pResource);
	// init texture from the surface
	if (!pChunk->Init(pMixChunk))
	{
		Mix_FreeChunk(pMixChunk);
		delete pChunk;
		return nullptr;
	}

	return std::shared_ptr<ISoundChunk>(pChunk);
}