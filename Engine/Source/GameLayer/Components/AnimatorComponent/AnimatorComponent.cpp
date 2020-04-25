#include "AnimatorComponent.h"

#include <Utils/Log.h>
#include <ApplicationLayer/Texture/ITexture.h>
#include <GameLayer/Components/RenderableComponent/RenderableComponent.h>
#include <GameLayer/GameUnit/GameUnit.h>
#include <Utils/Math/Shapes/Shapes.h>

halo::IComponent::ID const halo::AnimatorComponent::m_sComponentID = halo::IOpSys::GUIDGenerator();

using halo::AnimatorComponent;

halo::AnimatorComponent::AnimatorComponent(std::weak_ptr<halo::GameUnit> pOwner, const char* pName)
	: IComponent{ pOwner, pName }
	, m_pRenderable{ nullptr }
	, m_currentFrameNumber{ -1 }
	, m_currentSequenceName{ "" }
	, m_spriteSheetColumns{ }
{
}

AnimatorComponent::~AnimatorComponent()
{
	
}

bool halo::AnimatorComponent::Init(tinyxml2::XMLElement* pData)
{
	// Testing Drawing with Rect
	auto pUnit = GetOwner();

	if (!pUnit)
	{
		LOG_ERROR("Failed to Load Game Object for Drawing!");
		return false;
	}

	// Get a pointer to renderable
	m_pRenderable = pUnit->GetComponent<RenderableComponent>();

	// Load Frame Data
	auto pElement = pData->FirstChildElement("Frame");
	if (pElement)
	{
		// get data
		int frameWidth = pElement->UnsignedAttribute("width");
		int frameHeight = pElement->UnsignedAttribute("height");
		int frameCount = pElement->UnsignedAttribute("count");

		// check data
		m_spriteSheetColumns = m_pRenderable->GetTexture()->GetTextureWidth() / frameWidth;
		int rows = m_pRenderable->GetTexture()->GetTextureHeight() / frameHeight;
		if (rows * m_spriteSheetColumns < frameCount)
		{
			LOG_ERROR("Animation Frame Data Does Not Match!")
			return false;
		}

		// set data
		m_pRenderable->GetRect().w = frameWidth;
		m_pRenderable->GetRect().h = frameHeight;
	}

	// Load Sequence Data
	pElement = pElement->NextSiblingElement("Sequence");
	if (pElement)
	{
		// Parse and add sequence
		for (auto pSequence = pElement->FirstChildElement();
			pSequence != nullptr;
			pSequence = pSequence->NextSiblingElement())
		{
			// Get Data
			const char* seqName = pSequence->Name();
			int firstFrame = pSequence->UnsignedAttribute("first");
			int lastFrame = pSequence->UnsignedAttribute("last");

			// Add Data
			LOG_DISPLAY("Found Sequence: %s.", seqName);
			m_allAnimations[seqName] = { seqName, firstFrame, lastFrame };
		}
	}

	return true;
}

halo::IComponent::ID halo::AnimatorComponent::GetID() const
{
	return m_sComponentID;
}

void halo::AnimatorComponent::UpdateFrameNumber()
{
	// get current sequence we want to play
	AnimationSequence& currentSequence = m_allAnimations[m_currentSequenceName];

	if (currentSequence.m_lastFrame == m_currentFrameNumber)
	{
		m_currentFrameNumber = currentSequence.m_firstFrame;
	}
	else
	{
		++m_currentFrameNumber;
	}
}

void halo::AnimatorComponent::PlayAnimation(const char* sequenceName)
{
	if (sequenceName == m_currentSequenceName || m_allAnimations.find(sequenceName) == m_allAnimations.end())
	{
		// print error message and dip!
		LOG_ERROR("Fail to update sequence, the sequence '%s' may not exist or is currently playing!", sequenceName);
		return;
	}

	// set sequence to play
	AnimationSequence& newSequence = m_allAnimations[sequenceName];
	m_currentFrameNumber = newSequence.m_firstFrame;
	m_currentSequenceName = sequenceName;
	UpdateSourceTransform();
}

void halo::AnimatorComponent::UpdateSourceTransform()
{
	// y is the colume, x is the row
	int frameX = m_currentFrameNumber % m_spriteSheetColumns;
	int frameY = m_currentFrameNumber / m_spriteSheetColumns;

	Rect& temp = m_pRenderable->GetRect();
	temp.x = frameX * temp.w;
	temp.y = frameY * temp.h;
}
