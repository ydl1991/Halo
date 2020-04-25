#include "EnemyView.h"
// C++ Library
#include <math.h>
// Engine Library
// System
#include <ApplicationLayer/ApplicationLayer.h>
#include <ApplicationLayer/Audio/IAudio.h>
// Processes
#include <GameLayer/Process/Timer/DelayProcess.h>
#include <GameLayer/Process/Move/MoveProcess.h>
#include <GameLayer/Process/Animation/AnimationProcess.h>
// Component
#include <GameLayer/Components/AnimatorComponent/AnimatorComponent.h>
// Events
#include <GameLayer/Event/Events/DestroyActorEvent.h>
#include <GameLayer/Event/IEvent.h>
// Log
#include <Utils/Log.h>

//----------------------//
// TESTING Move Process //
//----------------------//
static constexpr uint32_t kNumPositions = 4;
static constexpr uint32_t kNumDimensions = 2;
static constexpr float s_positions[kNumPositions][kNumDimensions] = { 
	{50.0f, 200.0f}, 
	{50.0f, 50.0f}, 
	{200.0f, 50.0f}, 
	{200.0f, 200.0f} };

EnemyView::EnemyView(std::shared_ptr<halo::GameUnit> pGameUnit)
	: IView{ pGameUnit }
	, m_pAudio{ nullptr }
	, m_pTarget{ nullptr }
	, m_currentPosition{ }
	, m_listenerID{ }
{
	
}

EnemyView::~EnemyView()
{
	
}

bool EnemyView::Init()
{
	auto pApp = halo::ApplicationLayer::Get();
	m_pGameLayer = pApp->GetGameLayer();

	// get system instances in the view
	m_pAudio = pApp->GetAudio();

	m_listenerID = halo::EventDispatcher::Get().AddEventListener(halo::DestroyActorEvent::m_kEventID, [this](halo::IEvent* pEvent) {
		DestroyGameUnit(pEvent);
	});

	CreateMoveProcess();
	m_pGameLayer->GetProcessController().AttachProcess(m_pMoveProcess);

	return true;
}

void EnemyView::CreateDelayProcess()
{
	// Create Delay Process
	m_pDelayProcess = std::make_shared<halo::DelayProcess>(m_pOwner, 2.0f);
	// Set Callback
	m_pDelayProcess->SetCallback(halo::IProcess::State::kSucceeded, [this](){
		CreateMoveProcess();
		m_pDelayProcess->AttachChild(m_pMoveProcess);
	});
	// Set animation sequence to play
	m_pOwner->GetComponent<halo::AnimatorComponent>()->PlayAnimation("Idle");
}

void EnemyView::CreateMoveProcess()
{
	// Create Move Process
	m_pMoveProcess = std::make_shared<halo::MoveProcess>(
		m_pOwner,
		s_positions[m_currentPosition][0],
		s_positions[m_currentPosition][1],
		2.0f);
	// Set Callback
	m_pMoveProcess->SetCallback(halo::IProcess::State::kSucceeded, [this](){
		CreateDelayProcess();
		m_pMoveProcess->AttachChild(m_pDelayProcess);
	});
	// Update position
	m_currentPosition = (m_currentPosition + 1) % kNumPositions;
	// Set animation sequence to play
	m_pOwner->GetComponent<halo::AnimatorComponent>()->PlayAnimation("Move");
}

void EnemyView::CreateAnimationProcess()
{
	m_pAnimationProcess = std::make_shared<halo::AnimationProcess>(m_pOwner);
}

void EnemyView::DestroyGameUnit(halo::IEvent* pEvent)
{
	auto pDestroyUnit = static_cast<halo::DestroyActorEvent*>(pEvent);
	if (pDestroyUnit->GetID() == m_pOwner->GetID())
	{
		halo::EventDispatcher::Get().RemoveEventListener(halo::DestroyActorEvent::m_kEventID, m_listenerID);

		if (auto pLuaScripter = m_pGameLayer->GetScripter<halo::LuaScripter>(); pLuaScripter)
		{
			pLuaScripter->StartFunction("PlaySound");
			pLuaScripter->PushString("Assets/Sounds/Chunk/scream.ogg");
			pLuaScripter->CallFunction(0);
		}

		m_pGameLayer->DestroyGameUnit(m_pOwner->GetID());
		m_pOwner = nullptr;

		m_pGameLayer->AddDeleteView(m_listIndex);

		// Test
		++m_pGameLayer->m_testKill;
	}
}
