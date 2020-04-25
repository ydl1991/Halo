#include "IAudio.h"

#include <ApplicationLayer/Audio/AudioSDL.h>

using halo::IAudio;

IAudio::IAudio()
	: m_volumeAdjMultiplier{ 10 }
{
	
}

IAudio::~IAudio()
{
	
}

std::unique_ptr<IAudio> halo::IAudio::Create()
{
	return std::make_unique<AudioSDL>();
}
