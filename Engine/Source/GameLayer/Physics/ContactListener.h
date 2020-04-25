#pragma once
// \file ContactListener.h
// TODO: File Purpose
// Created by Dali Yi

#include <Box2d/box2d.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class ContactListener
	// TODO: Class Purpose
	class ContactListener
		: public b2ContactListener
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor
		ContactListener();

		// Default Destructor
		~ContactListener();

		//void BeginContact();
		//void EndContact();

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