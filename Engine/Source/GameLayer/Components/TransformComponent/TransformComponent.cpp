#include "TransformComponent.h"

// Log
#include <Utils/Log.h>
// Math helper
#include <Utils/Math/Math.h>
// Game Unit
#include <GameLayer/GameUnit/GameUnit.h>
// scripter
#include <GameLayer/Script/IScripter.h>
// Lua source code
#include "GameLayer/Components/TransformComponent/TransformComponent.gen"

halo::IComponent::ID const halo::TransformComponent::m_sComponentID = halo::IOpSys::GUIDGenerator();

using halo::TransformComponent;

TransformComponent::TransformComponent(std::weak_ptr<halo::GameUnit> pOwner, const char* pName)
	: IComponent{ pOwner, pName }
	, m_position{ 0, 0 }
	, m_rotation{ 0.f }
	, m_facing{ 0, 1 }
{
	
}

TransformComponent::~TransformComponent()
{
	
}

bool halo::TransformComponent::Init(tinyxml2::XMLElement* pData)
{
	tinyxml2::XMLElement* pPosition = pData->FirstChildElement("Position");

	if (pPosition)
	{
		m_position.m_x = pPosition->FloatAttribute("x");
		m_position.m_y = pPosition->FloatAttribute("y");

		LOG_DISPLAY("Loaded position from file: (%.3f, %.3f)", m_position.m_x, m_position.m_y);
	}

	return true;
}

halo::IComponent::ID halo::TransformComponent::GetID() const
{
	return m_sComponentID;
}

void halo::TransformComponent::Move(float x, float y)
{
	m_position.m_x += x;
	m_position.m_y += y;
}

void halo::TransformComponent::UpdateFacing(float x, float y)
{
	// Update rotation
	Vector2D dir = MathHelper::Normalize(m_position, Vector2D(x, y));
	m_rotation = MathHelper::SpriteRotation(dir);

	// Update facing
	m_facing.m_x = x;
	m_facing.m_y = y;
}

int Lua::TransformComponentMove(lua_State* pState)
{
	auto pTransform = reinterpret_cast<TransformComponent*>(
		lua_touserdata(pState, 1));
	float x = static_cast<float>(luaL_checknumber(pState, 2));
	float y = static_cast<float>(luaL_checknumber(pState, 3));
	pTransform->Move(x, y);
	lua_pop(pState, 3);
	return 0;
}