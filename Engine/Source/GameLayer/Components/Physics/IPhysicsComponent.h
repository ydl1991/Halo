#pragma once
// \file IPhysicsComponent.h
// TODO: File Purpose
// Created by Dali Yi

#include "..\IComponent.h"
#include <functional>

#include <Utils/Math/Vectors/Vector2D.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class IPhysicsComponent
	// TODO: Class Purpose
	class IPhysicsComponent
		: public IComponent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor
		IPhysicsComponent(std::weak_ptr<halo::GameUnit> pOwner, const char* pName);

		// Default Destructor
		~IPhysicsComponent();

		// all of your physics functions here
		virtual void SetLinearVeclocity(Vector2D velocity) = 0;

		void HanldeBeginOverlap(GameUnit* pOther);
		void HandleEndOverlap(GameUnit* pOther);
		void HanldeBeginCollision(GameUnit* pOther);
		void HandleEndCollision(GameUnit* pOther);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		using ColiisionHandler = std::function<void(GameUnit* pOther)>;

		ColiisionHandler m_beginOverlap;
		ColiisionHandler m_endOverlap;
		ColiisionHandler m_beginCollision;
		ColiisionHandler m_endCollision;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //

		// TODO: MUTATORS TO set collision handlers

	};
}