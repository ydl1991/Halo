#include "GameUnit.h"

#include <string>
#include <algorithm>

#include <ApplicationLayer/ApplicationLayer.h>
#include <GameLayer/Components/Physics/Box2DPhysicsComponent.h>
#include <Utils/Log.h>

using halo::GameUnit;

halo::GameUnit::GameUnit(ID id)
	: m_id{id}
	, m_name{ "Unit #" + std::to_string(id) }
	, m_pPhysics{ nullptr }
{

}

GameUnit::~GameUnit()
{
	m_pPhysics = nullptr;
	// Remove and destruct all components associated with this unit
	m_components.clear();
}

bool halo::GameUnit::Init(tinyxml2::XMLElement* pData)
{
	std::string rootName = pData->Name();
	if (rootName != "GameUnit")
	{
		LOG_ERROR("GameUnit XML file must have a root element named 'GameUnit'");
		return false;
	}

	return true;
}

bool halo::GameUnit::PostInit()
{
	// Post Init Components
	for (const auto& componentPair : m_components)
	{
		if (!componentPair.second->PostInit())
		{
			return false;
		}
	}

	// Save Transform Component for update if there is any
	m_pPhysics = GetComponent<Box2DPhysicsComponent>();

	return true;
}

void halo::GameUnit::Update(float delta)
{
	// Update Tranform for Physics Change
	if (m_pPhysics)
		m_pPhysics->Update(delta);
}

void halo::GameUnit::Destroy()
{
	auto pGameLayer = ApplicationLayer::Get()->GetGameLayer();
	pGameLayer->DestroyGameUnit(m_id);
}

void halo::GameUnit::RegisterWithScript()
{
	for (auto& pair : m_components)
	{
		pair.second->RegisterWithScript();
	}
}

void halo::GameUnit::AddComponent(std::unique_ptr<IComponent> pComponent)
{
	if (pComponent)
	{
		m_components[pComponent->GetID()] = std::move(pComponent);
	}
	else
	{
		LOG_ERROR("Failed to add null component to Game Unit");
	}
}