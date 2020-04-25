#include "DelayProcess.h"

#include <Utils/Log.h>

using halo::DelayProcess;

halo::DelayProcess::DelayProcess(std::weak_ptr<halo::GameUnit> pOwner, float time)
	: IProcess{ pOwner }
	, m_timer{ 0.0f }
	, m_duration{ time }
{

}

DelayProcess::DelayProcess(std::weak_ptr<halo::GameUnit> pOwner)
	: IProcess{ pOwner }
	, m_timer{ 0.0f }
	, m_duration{ 0.0f }
{
	
}

DelayProcess::~DelayProcess()
{
}

void halo::DelayProcess::Update(float deltaSeconds)
{
	IProcess::Update(deltaSeconds);

	if (IsAlive())
	{
		m_timer -= deltaSeconds;

		if (m_timer < 0.f)
		{
			Succeed();
		}
	}
}

bool halo::DelayProcess::Init(tinyxml2::XMLElement* pData)
{
	// Load duration
	auto pElement = pData->FirstChildElement("Time");
	if (pElement)
	{
		m_duration = pElement->FloatAttribute("duration");

		LOG_DISPLAY("Loaded delay duration from file: %f seconds", m_duration);
	}

	return true;
}

bool halo::DelayProcess::PostInit()
{
	m_timer = m_duration;
	return true;
}

