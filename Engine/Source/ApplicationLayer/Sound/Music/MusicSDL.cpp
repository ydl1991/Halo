#include "MusicSDL.h"

#include <Utils/Log.h>


using halo::MusicSDL;

MusicSDL::MusicSDL(IResource* pResource)
	: IMusic(pResource)
	, m_pMusic{ nullptr, nullptr }
{
	
}

MusicSDL::~MusicSDL()
{
	
}

bool halo::MusicSDL::Init(Mix_Music* pMusic)
{
	m_pMusic = UniqueMusic(pMusic, &Mix_FreeMusic);

	if (!m_pMusic)
	{
		LOG_ERROR("Failed to Create SDL Music.");
		return false;
	}

	return true;
}

void* halo::MusicSDL::GetNativeMusic() const
{
	return m_pMusic.get();
}
