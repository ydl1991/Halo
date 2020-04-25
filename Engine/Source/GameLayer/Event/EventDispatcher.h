#pragma once
// \file EventDispatcher.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <functional>
#include <vector>
#include <unordered_map>

#include <GameLayer/Event/IEvent.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class IEvent;

	// \class EventDispatcher 
	// TODO: Class Purpose 
	class EventDispatcher
	{
		using EventHandler = std::function<void(IEvent*)>;
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		static EventDispatcher& Get();

		size_t AddEventListener(EventID id, EventHandler pHandler);
		void RemoveEventListener(EventID id, size_t index);
		void QueueEvent(std::unique_ptr<IEvent> pEvent);
		void ProcessEvents();

		// Process Event Immediately
		// Prioritizing Events
		// Targeted Events

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		std::unordered_map<halo::EventID, std::vector<EventHandler>> m_eventListener;
		std::vector<std::unique_ptr<IEvent>> m_queue;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //
		// Singleton
		// Default Constructor 
		EventDispatcher();

		// Default Destructor 
		~EventDispatcher();

		EventDispatcher(const EventDispatcher& copy) = delete;
		EventDispatcher(EventDispatcher&& copy) = delete;
		EventDispatcher& operator=(const EventDispatcher& copy) = delete;
		EventDispatcher& operator=(EventDispatcher&& copy) = delete;

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //


	};
}