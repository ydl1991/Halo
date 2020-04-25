#pragma once
// \file IPhysicsSimulation.h
// TODO: File Purpose
// Created by Dali Yi

#include <memory>

#include <Utils/Math/Vectors/Vector2D.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class ContactListener;

	// \class IPhysicsSimulation
	// TODO: Class Purpose
	class IPhysicsSimulation
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor
		IPhysicsSimulation();

		// Default Destructor
		virtual ~IPhysicsSimulation();

		virtual bool Init() = 0;
		virtual void Update(float delta) = 0;
		virtual void DrawDebug() = 0;
		virtual void SetContactListener(ContactListener* pListener) = 0;

		// Factory Method
		static std::unique_ptr<IPhysicsSimulation> Create(Vector2D gravity);

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //


	};
}