#include "IScripter.h"

// C++ Library
#include <assert.h>

// Engine Library
#include <GameLayer/Script/LuaScripter.h>
#include <GameLayer/Resource/IResource.h>
#include <Utils/Log.h>

using halo::IScripter;

IScripter::IScripter()
{
	
}

IScripter::~IScripter()
{
	
}

std::unique_ptr<IScripter> halo::IScripter::Create()
{
	return std::make_unique<LuaScripter>();
}