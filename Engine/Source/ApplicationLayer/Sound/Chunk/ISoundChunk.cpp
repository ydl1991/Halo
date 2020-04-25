#include "ISoundChunk.h"

using halo::ISoundChunk;

ISoundChunk::ISoundChunk(IResource* pResource)
	: IResource(pResource->GetFilepath(), pResource->GetData())
{
	
}

ISoundChunk::~ISoundChunk()
{
	
}