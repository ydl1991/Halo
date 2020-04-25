#include "DestroyActorEvent.h"

// OS
#include <ApplicationLayer/OS/IOpSys.h>

halo::EventID const halo::DestroyActorEvent::m_kEventID = halo::IOpSys::GUIDGenerator();

using halo::DestroyActorEvent;

DestroyActorEvent::DestroyActorEvent(halo::GameUnit::ID id)
	: m_id{ id }
{
	
}

DestroyActorEvent::~DestroyActorEvent()
{
	
}