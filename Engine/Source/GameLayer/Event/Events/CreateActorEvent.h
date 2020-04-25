#pragma once
// \file CreateActorEvent.h 
// TODO: File Purpose 
// Created by Dali Yi

#include "..\IEvent.h"

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class CreateActorEvent 
	// TODO: Class Purpose 
	class CreateActorEvent
		: public IEvent
	{
	public:
		// Non-incremental ids (GUID)
		static const EventID m_kEventID;

		enum class OwningViewType
		{
			kNone,
			kPlayer,
			kEnemy
		};

		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		CreateActorEvent(const char* pFilename, OwningViewType type);

		// Default Destructor 
		virtual ~CreateActorEvent();

		virtual EventID GetEventID() const final override { return m_kEventID; }
		virtual const char* GetEventName() const final override { return "CreateActorEvent"; }

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		const char* m_pFilename;
		OwningViewType m_type;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		const char* GetFilename() const { return m_pFilename; }
		OwningViewType GetViewType() const { return m_type; }
	};
}