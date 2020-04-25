#include "Box2DPhysics.h"

#include <Utils/Log.h>
#include <GameLayer/Physics/ContactListener.h>

using halo::Box2DPhysics;

Box2DPhysics::Box2DPhysics(halo::Vector2D gravity)
	: m_world(ConvertToB2Vec2(gravity))
{
	//
}

Box2DPhysics::~Box2DPhysics()
{
	
}

bool halo::Box2DPhysics::Init()
{
	m_world.SetDebugDraw(&m_debugDraw);

	// This has to be set, otherwise will draw nothing
	m_debugDraw.SetFlags(b2Draw::e_shapeBit);
	return false;
}

void halo::Box2DPhysics::Update(float delta)
{
	m_accumulator += delta;
	if (m_accumulator >= kPhysicsStep)
	{
		m_accumulator -= kPhysicsStep;
		m_world.Step(kPhysicsStep, kVelocityIterations, kPositionIterations);
	}
}

void halo::Box2DPhysics::DrawDebug()
{
	m_world.DebugDraw();
}

void halo::Box2DPhysics::SetContactListener(halo::ContactListener* pListener)
{
	m_world.SetContactListener(pListener);
}

void halo::DebugDrawPhysics::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
}

void halo::DebugDrawPhysics::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
}

void halo::DebugDrawPhysics::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
}

void halo::DebugDrawPhysics::DrawTransform(const b2Transform& xf)
{
}

void halo::DebugDrawPhysics::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
}

void halo::DebugDrawPhysics::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
}

void halo::DebugDrawPhysics::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
}
