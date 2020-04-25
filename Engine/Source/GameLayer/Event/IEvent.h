#pragma once
// \file IEvent.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <string>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	using EventID = size_t;

	// \class IEvent 
	// TODO: Class Purpose 
	class IEvent
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		IEvent();

		// Default Destructor 
		virtual ~IEvent();

		virtual EventID GetEventID() const = 0;
		virtual const char* GetEventName() const = 0;

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