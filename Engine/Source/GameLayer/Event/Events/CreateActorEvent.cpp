#include "CreateActorEvent.h"

// OS
#include <ApplicationLayer/OS/IOpSys.h>

halo::EventID const halo::CreateActorEvent::m_kEventID = halo::IOpSys::GUIDGenerator();

using halo::CreateActorEvent;

CreateActorEvent::CreateActorEvent(const char* pFilename, OwningViewType type)
	: m_pFilename{ pFilename }
	, m_type{ type }
{
	
}

CreateActorEvent::~CreateActorEvent()
{
	
}