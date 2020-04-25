#include "EventDispatcher.h"

#include <Utils/Log.h>

using halo::EventDispatcher;

EventDispatcher::EventDispatcher()
{
	
}

EventDispatcher::~EventDispatcher()
{
	
}

EventDispatcher& halo::EventDispatcher::Get()
{
	// TODO: insert return statement here
	static EventDispatcher sDispatcher;
	return sDispatcher;
}

size_t halo::EventDispatcher::AddEventListener(EventID id, EventHandler pHandler)
{
	auto& listeners = m_eventListener[id];
	for (size_t index = 0; index < listeners.size(); ++index)
	{
		if (listeners[index] == nullptr)
		{
			listeners[index] = pHandler;
			return index;
		}
	}

	// if no room for it, emplace to the back
	listeners.emplace_back(pHandler);
	return listeners.size() - 1;
}

void halo::EventDispatcher::RemoveEventListener(EventID id, size_t index)
{
	auto mapItr = m_eventListener.find(id);
	if (mapItr == m_eventListener.end())
	{
		LOG_ERROR("No Event Registered: %d -- Cannot Remove", id);
		return;
	}

	auto& listeners = mapItr->second;
	if (index < listeners.size())
	{
		listeners[index] = nullptr;
	}
	else
	{
		LOG_ERROR("Failed to Remove Event Listener (%d). Index out of range", id);
	}

	//auto& listeners = mapItr->second;
	//if (index < listeners.size())
	//{
	//	// Update Indexes

	//	// Swap Elements
	//	std::swap(listeners[index], listeners.back());

	//	// remove elements
	//	listeners.pop_back();
	//}
	//else
	//{
	//	LOG_ERROR("Failed to Remove Event Listener (%d). Index out of range", id);
	//}
}

void halo::EventDispatcher::QueueEvent(std::unique_ptr<IEvent> pEvent)
{
	m_queue.emplace_back(std::move(pEvent));
}

void halo::EventDispatcher::ProcessEvents()
{
	// Move the entire queue to a local copy, so new events don't create a feedback loop
	auto queue = std::move(m_queue);

	for (auto& pEvent : queue)
	{
		// check for existence of events
		auto mapItr = m_eventListener.find(pEvent->GetEventID());
		if (mapItr == m_eventListener.end())
		{
			LOG_WARNING("No Listeners Found For: %s", pEvent->GetEventName());
			continue;
		}

		// Execute all handlers associated with that event
		auto& listeners = mapItr->second;
		for (auto& listener : listeners)
		{
			if (listener != nullptr)
			{
				listener(pEvent.get());
			}
		}
	}

}
