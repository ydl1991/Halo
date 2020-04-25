#include "IPhysicsComponent.h"

using halo::IPhysicsComponent;

IPhysicsComponent::IPhysicsComponent(std::weak_ptr<halo::GameUnit> pOwner, const char* pName)
	: IComponent{ pOwner, pName }
{
	
}

IPhysicsComponent::~IPhysicsComponent()
{
	
}

void halo::IPhysicsComponent::HanldeBeginOverlap(GameUnit* pOther)
{
}

void halo::IPhysicsComponent::HandleEndOverlap(GameUnit* pOther)
{
}

void halo::IPhysicsComponent::HanldeBeginCollision(GameUnit* pOther)
{
}

void halo::IPhysicsComponent::HandleEndCollision(GameUnit* pOther)
{
}
