#include "AnimationProcess.h"

// Engine Library
// Game Unit
#include <GameLayer/GameUnit/GameUnit.h>
// Component
#include <GameLayer/Components/AnimatorComponent/AnimatorComponent.h>
// Log
#include <Utils/Log.h>

using halo::AnimationProcess;

halo::AnimationProcess::AnimationProcess(std::weak_ptr<halo::GameUnit> pUnit, float frameRate, float nextFrameTime)
	: IProcess{ pUnit }
	, m_pAnimator{ nullptr }
	, m_frameRate{ frameRate }
	, m_nextFrameTime{ nextFrameTime }
{
}

AnimationProcess::AnimationProcess(std::weak_ptr<halo::GameUnit> pUnit)
	: IProcess{ pUnit }
	, m_pAnimator{ nullptr }
	, m_frameRate{ 0.0f }
	, m_nextFrameTime{ 0.0f }
{
	
}

AnimationProcess::~AnimationProcess()
{
	
}

bool halo::AnimationProcess::Init(tinyxml2::XMLElement* pData)
{
	// Load Destination
	auto pElement = pData->FirstChildElement("Frame");

	if (pElement)
	{
		m_frameRate = pElement->FloatAttribute("rate");

		LOG_DISPLAY("Loaded animation process with frame rate of %f frame per second", m_frameRate);
	}

	return true;
}

bool halo::AnimationProcess::PostInit()
{
	auto pUnit = GetOwner();
	if (!pUnit)
	{
		LOG_ERROR("Failed to get game unit");
		return false;
	}

	m_pAnimator = pUnit->GetComponent<AnimatorComponent>();
	if (!m_pAnimator)
	{
		LOG_ERROR("Failed to get AnimatorComponent for game unit -- %d", pUnit->GetID());
		return false;
	}

	ResetFrameTime();

	return true;
}

void halo::AnimationProcess::Update(float deltaSeconds)
{
	IProcess::Update(deltaSeconds);

	if (IsAlive())
	{
		// if not set frame number yet, exit
		if (m_pAnimator->CurrentFrame() == -1)
		{
			return;
		}

		bool isFrameDirty = false;

		// change frame number
		while (deltaSeconds > m_nextFrameTime)
		{
			deltaSeconds -= m_nextFrameTime;
			ResetFrameTime();

			isFrameDirty = true;

			m_pAnimator->UpdateFrameNumber();
		}

		m_nextFrameTime -= deltaSeconds;

		// update frame transform on sheet
		if (isFrameDirty)
		{
			m_pAnimator->UpdateSourceTransform();
		}
	}
}

void halo::AnimationProcess::ResetFrameTime()
{
	m_nextFrameTime = 1 / m_frameRate;
}
