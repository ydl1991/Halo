#pragma once
// \file Box2DPhysicsComponent.h
// TODO: File Purpose
// Created by Dali Yi

#include <GameLayer/Components/Physics/IPhysicsComponent.h>
#include <Box2d/box2d.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class GameUnit;
	class IPhysicsSimulation;
	class Box2DPhysics;
	class TransformComponent;

	// \class Box2DPhysicsComponent
	// TODO: Class Purpose
	class Box2DPhysicsComponent
		: public halo::IPhysicsComponent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //
		static const ID m_sComponentID;

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor
		Box2DPhysicsComponent(std::weak_ptr<halo::GameUnit> pOwner, IPhysicsSimulation* pPhysics);

		// Default Destructor
		~Box2DPhysicsComponent();

		// Inherited via IPhysicsComponent
		virtual bool Init(tinyxml2::XMLElement* pData) final override;
		virtual bool PostInit() final override;
		void Update(float delta) final override;
		virtual ID GetID() const override;
		virtual void SetLinearVeclocity(Vector2D velocity) final override;

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		b2World* m_pWorld;
		b2Body* m_pBody;
		b2Fixture* m_pFixture;
		float m_width;
		float m_height;

		// Shapes
		b2PolygonShape m_polyShape;
		//b2CircleShape m_circleShape;

		// Definitions
		b2BodyDef m_bodyDef;
		b2FixtureDef m_fixtureDef;
		b2BodyType m_bodyType;

		TransformComponent* m_pTransform;
		Box2DPhysics* m_pPhysics;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //



	};
}