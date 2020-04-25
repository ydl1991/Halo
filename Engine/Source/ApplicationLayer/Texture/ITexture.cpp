#include "ITexture.h"

using halo::ITexture;

ITexture::ITexture(IResource* pResource)
	: IResource(pResource->GetFilepath(), pResource->GetData())
{
	
}

ITexture::~ITexture()
{
	
}