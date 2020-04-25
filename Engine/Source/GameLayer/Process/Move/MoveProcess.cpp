#include "MoveProcess.h"

// Engine Library
#include <ApplicationLayer/ApplicationLayer.h>
#include <GameLayer/GameUnit/GameUnit.h>
#include <GameLayer/Components/TransformComponent/TransformComponent.h>
#include <GameLayer/IGameLayer.h>
#include <Utils/Log.h>

using halo::MoveProcess;

halo::MoveProcess::MoveProcess(std::weak_ptr<halo::GameUnit> pUnit, float destX, float destY, float time)
	: IProcess{ pUnit }
	, m_pTransform{ nullptr }
	, m_xDest{ destX }
	, m_yDest{ destY }
	, m_time{ time }
	, m_xSpeed{ 0.0f }
	, m_ySpeed{ 0.0f }
{

}

MoveProcess::MoveProcess(std::weak_ptr<halo::GameUnit> pUnit)
	: IProcess{ pUnit }
	, m_pTransform{ nullptr }
	, m_xDest{ 0.0f }
	, m_yDest{ 0.0f }
	, m_xSpeed{ 0.0f }
	, m_ySpeed{ 0.0f }
	, m_time{ 0.0f }
{
	
}

MoveProcess::~MoveProcess()
{
	
}

bool halo::MoveProcess::Init(tinyxml2::XMLElement* pData)
{
	// Load Destination
	auto pElement = pData->FirstChildElement("Destination");

	if (pElement)
	{
		m_xDest = pElement->FloatAttribute("x");
		m_yDest = pElement->FloatAttribute("y");
		m_time = pElement->FloatAttribute("duration");

		LOG_DISPLAY("Loaded move process to move to destination (x: %f, y: %f) in %f seconds", m_xDest, m_yDest, m_time);
	}

	return true;
}

bool halo::MoveProcess::PostInit()
{
	auto pUnit = GetOwner();
	if (!pUnit)
	{
		LOG_ERROR("Failed to get game unit");
		return false;
	}

	// Get Transform
	m_pTransform = pUnit->GetComponent<TransformComponent>();
	if (m_pTransform == nullptr)
	{
		LOG_ERROR("Failed to get game unit's transformation component");
		return false;
	}

	// Update facing and rotation
	m_pTransform->UpdateFacing(m_xDest, m_yDest);

	// Update moving speed
	m_xSpeed = (m_xDest - m_pTransform->GetX()) / m_time;
	m_ySpeed = (m_yDest - m_pTransform->GetY()) / m_time;

	return true;
}

void halo::MoveProcess::Update(float deltaSeconds)
{
	IProcess::Update(deltaSeconds);

	if (IsAlive())
	{
		if (m_time <= deltaSeconds)
		{
			m_pTransform->SetX(m_xDest);
			m_pTransform->SetY(m_yDest);
			Succeed();
		}
		else
		{
			// Moving from Lua
			if (auto pLuaScripter = ApplicationLayer::Get()->GetGameLayer()->GetScripter<LuaScripter>(); pLuaScripter)
			{
				float dx = m_xSpeed * deltaSeconds, dy = m_ySpeed * deltaSeconds;
				pLuaScripter->StartFunction("Move");
				pLuaScripter->PushInt(GetOwner()->GetID());
				pLuaScripter->PushNumber(dx);
				pLuaScripter->PushNumber(dy);
				pLuaScripter->CallFunction(0);
				m_time -= deltaSeconds;
			}
		}
	}
}
