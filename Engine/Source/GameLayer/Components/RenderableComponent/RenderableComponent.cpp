#include "RenderableComponent.h"

// Component
#include <GameLayer/Components/BoxComponent/BoxComponent.h>
// Game Unit
#include <GameLayer/GameUnit/GameUnit.h>
// Log
#include <Utils/Log.h>
// Graphics
#include <ApplicationLayer/Texture/ITexture.h>
// App
#include <ApplicationLayer/ApplicationLayer.h>
// Resource
#include <GameLayer/Resource/ResourceCache.h>

halo::IComponent::ID const halo::RenderableComponent::m_sComponentID = halo::IOpSys::GUIDGenerator();

using halo::RenderableComponent;

RenderableComponent::RenderableComponent(std::weak_ptr<halo::GameUnit> pOwner, const char* pName)
	: IComponent{ pOwner, pName }
	, m_color{ 0, 0, 0, 0 }
	, m_currentFrameTransformOnSheet{ }
	, m_pTexture{ nullptr }
{
	
}

RenderableComponent::~RenderableComponent()
{

}

bool halo::RenderableComponent::Init(tinyxml2::XMLElement* pData)
{
	// Load Color
	auto pElement = pData->FirstChildElement("Color");
	if (pElement)
	{
		m_color.r = pElement->UnsignedAttribute("r");
		m_color.g = pElement->UnsignedAttribute("g");
		m_color.b = pElement->UnsignedAttribute("b");

		LOG_DISPLAY("Loaded color from file: (R: %d, G: %d, B: %d)", m_color.r, m_color.g, m_color.b);
	}

	pElement = pElement->NextSiblingElement("Sprite");
	if (pElement)
	{
		const char* src = pElement->Attribute("src");
		m_pTexture = ResourceCache::Get().AcquireResource<ITexture>(src);
		if (!m_pTexture)
		{
			LOG_ERROR("Failed to Load Object Texture!");
			return false;
		}
	}
	return true;
}

void halo::RenderableComponent::Render(IGraphics* pGraphics)
{
	// Testing Drawing with Rect
	auto pUnit = GetOwner();

	if (!pUnit)
	{
		LOG_ERROR("Failed to Load Game Object for Drawing!");
		return;
	}

	BoxComponent* pBox = pUnit->GetComponent<BoxComponent>();

	if (!pBox)
	{
		LOG_ERROR("Failed to Load Player Box Component for Drawing!");
		return;
	}

	Rect rect((int)pBox->GetX(), (int)pBox->GetY(), (int)pBox->GetWidth(), (int)pBox->GetHeight());
	
	if(m_pTexture)
		pGraphics->DrawTexture(m_pTexture.get(), &m_currentFrameTransformOnSheet, &rect, GetOwner()->GetComponent<TransformComponent>()->GetRotation());
	else
		pGraphics->DrawRectangle(rect, m_color);
}

halo::IComponent::ID halo::RenderableComponent::GetID() const
{
	return m_sComponentID;
}
