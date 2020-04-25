#include "SoundChunkSDL.h"

#include <Utils/Log.h>


using halo::SoundChunkSDL;

SoundChunkSDL::SoundChunkSDL(IResource* pResource)
	: ISoundChunk(pResource)
	, m_pSoundChunk{ nullptr, nullptr }
{
	
}

SoundChunkSDL::~SoundChunkSDL()
{
	
}

bool halo::SoundChunkSDL::Init(Mix_Chunk* pSoundChunk)
{
	m_pSoundChunk = UniqueChunk(pSoundChunk, &Mix_FreeChunk);

	if (!m_pSoundChunk)
	{
		LOG_ERROR("Failed to Create SDL Sound Chunk.");
		return false;
	}

	return true;
}

void* halo::SoundChunkSDL::GetNativeSoundChunk() const
{
	return m_pSoundChunk.get();
}
