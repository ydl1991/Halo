#include "IProcess.h"

using halo::IProcess;

halo::IProcess::IProcess(std::weak_ptr<halo::GameUnit> pOwner)
	: m_pOwner{ pOwner }
	, m_state{ State::kUninitialized }
{
}

IProcess::~IProcess()
{
	
}

void halo::IProcess::Update(float deltaSeconds)
{
	if (m_pOwner.expired())
		Abort();
}

std::shared_ptr<IProcess> halo::IProcess::RemoveChild()
{
	auto pChild = m_pChild;
	m_pChild = nullptr;
	return pChild;
}
