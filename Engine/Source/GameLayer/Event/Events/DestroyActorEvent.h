#pragma once
// \file DestroyActorEvent.h 
// TODO: File Purpose 
// Created by Dali Yi

#include "..\IEvent.h"

// Game Unit
#include <GameLayer/GameUnit/GameUnit.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class GameUnit;

	// \class DestroyActorEvent 
	// TODO: Class Purpose 
	class DestroyActorEvent
		: public IEvent
	{
	public:
		// Non-incremental ids (GUID)
		static const EventID m_kEventID;

		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		DestroyActorEvent(GameUnit::ID id);

		// Default Destructor 
		virtual ~DestroyActorEvent();

		virtual EventID GetEventID() const final override { return m_kEventID; }
		virtual const char* GetEventName() const final override { return "DestroyActorEvent"; }
		GameUnit::ID GetID() const { return m_id; }
		
	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		GameUnit::ID m_id;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //


	};
}