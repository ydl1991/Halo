#include "Box2DPhysicsComponent.h"
#include <GameLayer/Components/TransformComponent/TransformComponent.h>
// Game Unit
#include <GameLayer/GameUnit/GameUnit.h>
// Physics
#include <GameLayer/Physics/Box2DPhysics.h>
// App
#include <ApplicationLayer/OS/IOpSys.h>
// Logger
#include <Utils/Log.h>

halo::IComponent::ID const halo::Box2DPhysicsComponent::m_sComponentID = halo::IOpSys::GUIDGenerator();

using halo::Box2DPhysicsComponent;

Box2DPhysicsComponent::Box2DPhysicsComponent(std::weak_ptr<halo::GameUnit> pOwner, halo::IPhysicsSimulation* pPhysics)
	:IPhysicsComponent{ pOwner , "Box2DPhysicsComponent" }
{
	m_pPhysics = dynamic_cast<Box2DPhysics*>(pPhysics);
	
	// Check if m_pPhysics exist
	if (m_pPhysics)
		m_pWorld = m_pPhysics->GetWorld();
}

Box2DPhysicsComponent::~Box2DPhysicsComponent()
{
	// Destroy Fixture
	if (m_pFixture != nullptr)
	{
		m_pBody->DestroyFixture(m_pFixture);
	}
	// Destroy Body
	if (m_pBody != nullptr)
	{
		m_pWorld->DestroyBody(m_pBody);
	}
}

bool halo::Box2DPhysicsComponent::Init(tinyxml2::XMLElement* pData)
{
	auto pElement = pData->FirstChildElement("Dimensions");
	if (pElement != nullptr)
	{
		m_height = pElement->FloatAttribute("width");
		m_width = pElement->FloatAttribute("height");
	}

	return true;
}

bool halo::Box2DPhysicsComponent::PostInit()
{
	// Grab the transform component of the owner
	m_pTransform = GetOwner()->GetComponent<TransformComponent>();

	if (!m_pTransform)
	{
		LOG_ERROR("Unable to Find Transform Component!");
		return false;
	}

	// Pretend this is being read in from XML :)
	m_bodyType = b2BodyType::b2_staticBody;

	// boyd has pointer to owner unit
	m_bodyDef.userData = GetOwner().get();
	m_bodyDef.fixedRotation = false;

	// Set body position
	m_bodyDef.position.Set(m_pTransform->GetX(), m_pTransform->GetY());

	// Set Box Shape
	m_polyShape.SetAsBox(0.5f, 0.5f);
	m_fixtureDef.shape = &m_polyShape;

	// create body / fixture
	m_pBody = m_pWorld->CreateBody(&m_bodyDef);
	// fixture can only be created inside the body itself
	m_pFixture = m_pBody->CreateFixture(&m_fixtureDef);

	return true;
}

void halo::Box2DPhysicsComponent::Update(float delta)
{
	if(m_pTransform && m_pBody)
		m_pBody->SetTransform(b2Vec2(m_pTransform->GetX() + m_width / 2.0f, m_pTransform->GetY() + m_height / 2.0f), 0);
}

halo::IComponent::ID halo::Box2DPhysicsComponent::GetID() const
{
	return ID();
}

void halo::Box2DPhysicsComponent::SetLinearVeclocity(Vector2D velocity)
{
}
