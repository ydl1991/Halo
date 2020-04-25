#include "IComponent.h"

#include <GameLayer/GameUnit/GameUnit.h>

using halo::IComponent;

IComponent::IComponent(std::weak_ptr<halo::GameUnit> pOwner, const char* pName)
	: m_pOwner{ pOwner }
	, m_name{ pName }
{
	
}

IComponent::~IComponent()
{
	
}