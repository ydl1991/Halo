#include "IGraphics.h"

#include <ApplicationLayer/Texture/ITexture.h>
#include <ApplicationLayer/Graphics/GraphicsSDL.h>

using halo::IGraphics;

IGraphics::IGraphics()
{
	
}

IGraphics::~IGraphics()
{
	
}

std::unique_ptr<IGraphics> halo::IGraphics::Create()
{
	return std::make_unique<GraphicsSDL>();
}
