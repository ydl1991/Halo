#pragma once
// \file Box2DPhysics.h
// TODO: File Purpose
// Created by Dali Yi

#include ".\IPhysicsSimulation.h"
#include <Box2d/box2d.h>
#include <vector>

//! \namespace halo Contains all Halo Engine code
namespace halo
{

	class DebugDrawPhysics : public b2Draw
	{

	private:

		// Reusable array of points for drawing circles
		std::vector<Vector2D> m_points;

	public:

		// Inherited via b2Draw
		virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
		virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override;
		virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;
		virtual void DrawTransform(const b2Transform& xf) override;
		virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override;
		virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
		virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override;

		// Accessor / Mutators
	};

	class ContactListener;

	// \class Box2DPhysics
	// TODO: Class Purpose
	class Box2DPhysics
		: public IPhysicsSimulation
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		static constexpr int kVelocityIterations = 8;
		static constexpr int kPositionIterations = 3;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor
		Box2DPhysics(Vector2D gravity);

		// Default Destructor
		~Box2DPhysics();

		// Inherited via IPhysicsSimulation
		bool Init() final override;
		void Update(float delta) final override;
		void DrawDebug() final override;
		void SetContactListener(ContactListener* pListener) final override;

		// Convert Helper
		static b2Vec2 ConvertToB2Vec2(Vector2D v) { return b2Vec2(v.m_x, v.m_y); }

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		static constexpr float kPhysicsStep = 1.f / 60.f;
		b2World m_world;
		float m_accumulator;
		DebugDrawPhysics m_debugDraw;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		b2World* GetWorld() { return &m_world; }
	};
}