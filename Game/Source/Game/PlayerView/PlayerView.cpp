#include "PlayerView.h"

// System
#include <ApplicationLayer/ApplicationLayer.h>
#include <ApplicationLayer/Audio/IAudio.h>
#include <ApplicationLayer/Input/IKeyboard.h>
#include <ApplicationLayer/Input/IMouse.h>
#include <ApplicationLayer/Texture/ITexture.h>
#include <ApplicationLayer/Window/IWindow.h>
#include <ApplicationLayer/Graphics/IGraphics.h>
// Component
#include <GameLayer/Components/TransformComponent/TransformComponent.h>
#include <GameLayer/Components/RenderableComponent/RenderableComponent.h>
// Process
#include <GameLayer/Process/Timer/DelayProcess.h>
#include <GameLayer/Process/ProcessController.h>
// Event
#include <GameLayer/Event/Events/DestroyActorEvent.h>
// Log
#include <Utils/Log.h>

PlayerView::PlayerView(std::shared_ptr<halo::GameUnit> pGameUnit)
	: IView{ pGameUnit }
	, m_pGraphics{ nullptr }
	, m_pKeyboard{ nullptr }
	, m_pMouse{ nullptr }
	, m_pAudio{ nullptr }
	, m_color{ 100,100,100,255 }
	, m_attackOnCoolDown{ false }
	, m_pOwnerTransform{ nullptr }
{
	//
}

PlayerView::~PlayerView()
{
	
}

bool PlayerView::Init()
{
	auto pApp = halo::ApplicationLayer::Get();
	m_pGameLayer = pApp->GetGameLayer();

    // get system instances in the view
    m_pGraphics = pApp->GetGraphics();
    m_pKeyboard = pApp->GetKeyboardInput();
    m_pMouse = pApp->GetMouseInput();
    m_pAudio = pApp->GetAudio();

	// Find Component
	m_pOwnerTransform = m_pOwner->GetComponent<halo::TransformComponent>();

	if (!m_pOwnerTransform)
	{
		LOG_ERROR("Failed to Find Player's TranformComponent.");
		return false;
	}

	// Play BGM
	auto pLuaScripter = m_pGameLayer->GetScripter<halo::LuaScripter>();
	if (pLuaScripter)
	{
		pLuaScripter->StartFunction("PlayMusic");
		pLuaScripter->PushString("Assets/Sounds/Music/Defeat.mp3");
		pLuaScripter->CallFunction(0);
	}

    return true;
}

void PlayerView::UpdateInput(float delta)
{
	auto pLuaScripter = m_pGameLayer->GetScripter<halo::LuaScripter>();

	// Keyboard related input activities
	if (m_pKeyboard->IsKeyPressed(halo::KeyCode::kW))
	{
		//m_pOwnerTransform->Move(0, -1);

		if (pLuaScripter)
		{
			// Test scripted auto player move
			pLuaScripter->StartFunction("PlayerMoveUp");
			pLuaScripter->PushNumber(delta);
			pLuaScripter->CallFunction(0);
		}
	}
	
	if (m_pKeyboard->IsKeyPressed(halo::KeyCode::kS))
	{
		//m_pOwnerTransform->Move(0, 1);

		if (pLuaScripter)
		{
			// Test scripted auto player move
			pLuaScripter->StartFunction("PlayerMoveDown");
			pLuaScripter->PushNumber(delta);
			pLuaScripter->CallFunction(0);
		}
	}
	
	if (m_pKeyboard->IsKeyPressed(halo::KeyCode::kD))
	{
		//m_pOwnerTransform->Move(1, 0);

		if (pLuaScripter)
		{
			// Test scripted auto player move
			pLuaScripter->StartFunction("PlayerMoveRight");
			pLuaScripter->PushNumber(delta);
			pLuaScripter->CallFunction(0);
		}
	}
	
	if (m_pKeyboard->IsKeyPressed(halo::KeyCode::kA))
	{
		//m_pOwnerTransform->Move(-1, 0);

		if (pLuaScripter)
		{
			// Test scripted auto player move
			pLuaScripter->StartFunction("PlayerMoveLeft");
			pLuaScripter->PushNumber(delta);
			pLuaScripter->CallFunction(0);
		}
	}
	
	if (m_pKeyboard->IsKeyReleased(halo::KeyCode::kSpace))
	{
		if (pLuaScripter)
		{
			pLuaScripter->StartFunction("CreateEnemy");
			pLuaScripter->CallFunction(0);
		}
	}
	
	if (!m_attackOnCoolDown && m_pMouse->IsButtonPressed(halo::MouseButton::kButtonLeft))
	{
		m_attackOnCoolDown = true;

		if (pLuaScripter)
		{
			pLuaScripter->StartFunction("PlaySound");
			pLuaScripter->PushString("Assets/Sounds/Chunk/magicShoot.wav");
			pLuaScripter->CallFunction(0);
		}

		auto pCoolDown = std::make_shared<halo::DelayProcess>(m_pOwner, 2.0f);
		pCoolDown->SetCallback(halo::IProcess::State::kSucceeded, [this]() {
			m_attackOnCoolDown = false;
		});

		m_pGameLayer->GetProcessController().AttachProcess(pCoolDown);

		halo::EventDispatcher::Get().QueueEvent(std::make_unique<halo::DestroyActorEvent>(m_pGameLayer->m_testKill));
	}

	if (m_pMouse->IsButtonPressed(halo::MouseButton::kButtonRight))
	{
		m_pAudio->FadingSongTransition("Assets/Sounds/Music/GameBGM.mp3");
	}

	// Mouse Scrolling activities
	if (m_pMouse->IsScrollingUp() || m_pMouse->IsScrollingDown())
	{
		m_pAudio->SetMusicVolume(m_pMouse->GetWheelValue());
	}

}

//---------------------------------------------------//
//              Render Frame Scene
//---------------------------------------------------//
void PlayerView::ViewScene()
{
    // Prepare Render Settings
    m_pGraphics->RenderBegin(m_color);

	// render each game unit
	for (auto& renderablePair : m_pGameLayer->GetAllRenderables())
	{
		renderablePair.second->Render(m_pGraphics);
	}

    // Actual Rendering
    m_pGraphics->RenderShow();
}


