#include "BoxComponent.h"

#include <Utils/Log.h>
#include <GameLayer/IGameLayer.h>

halo::IComponent::ID const halo::BoxComponent::m_sComponentID = halo::IOpSys::GUIDGenerator();

halo::BoxComponent::BoxComponent(std::weak_ptr<halo::GameUnit> pOwner, const char* pName)
	: IComponent{ pOwner, pName }
	, m_width{ 0 }
	, m_height{ 0 }
	, m_pTransform{ nullptr }
{

}

halo::BoxComponent::~BoxComponent()
{
}

bool halo::BoxComponent::Init(tinyxml2::XMLElement* pData)
{
	auto pElement = pData->FirstChildElement("Dimensions");
	if (pElement)
	{
		m_width = pElement->FloatAttribute("width");
		m_height = pElement->FloatAttribute("height");

		LOG_DISPLAY("Loaded dimensions from file: (Width: %0.1f, Height: %0.1f)", m_width, m_height);
	}

	return true;
}

halo::IComponent::ID halo::BoxComponent::GetID() const
{
	return m_sComponentID;
}

bool halo::BoxComponent::PostInit()
{
	// Testing Drawing with Rect
	auto pUnit = GetOwner();

	if (!pUnit)
	{
		LOG_ERROR("Failed to Load Game Object for Drawing!");
		return false;
	}

	m_pTransform = pUnit->GetComponent<TransformComponent>();

	if (!m_pTransform)
	{
		LOG_ERROR("Unable to find TransformComponent on Game Unit! Failed to PostInit Component - %s", m_sComponentID);
		return false;
	}
	return true;
}
