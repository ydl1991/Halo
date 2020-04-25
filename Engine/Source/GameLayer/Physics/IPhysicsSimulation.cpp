#include "IPhysicsSimulation.h"

#include <GameLayer/Physics/Box2DPhysics.h>
using halo::IPhysicsSimulation;

IPhysicsSimulation::IPhysicsSimulation()
{
	
}

IPhysicsSimulation::~IPhysicsSimulation()
{
	
}

std::unique_ptr<IPhysicsSimulation> halo::IPhysicsSimulation::Create(Vector2D gravity)
{
	return std::make_unique<Box2DPhysics>(gravity);
}
