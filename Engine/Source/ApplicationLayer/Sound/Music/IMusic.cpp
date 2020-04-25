#include "IMusic.h"

using halo::IMusic;

IMusic::IMusic(IResource* pResource)
	: IResource(pResource->GetFilepath(), pResource->GetData())
{
	
}

IMusic::~IMusic()
{
	
}