#include "IGameLayer.h"

// View
#include <ApplicationLayer/View/IView.h>
// Component
#include <GameLayer/Components/TransformComponent/TransformComponent.h>
#include <GameLayer/Components/BoxComponent/BoxComponent.h>
#include <GameLayer/Components/RenderableComponent/RenderableComponent.h>
#include <GameLayer/Components/AnimatorComponent/AnimatorComponent.h>
#include <GameLayer/Components/Physics/Box2DPhysicsComponent.h>
// Physics
#include <GameLayer/Physics/IPhysicsSimulation.h>
// Process
#include <GameLayer/Process/Animation/AnimationProcess.h>
#include <GameLayer/Process/Move/MoveProcess.h>
#include <GameLayer/Process/Timer/DelayProcess.h>
// Log
#include <Utils/Log.h>

// Testing box 2d integration
#include <Box2d/b2_world.h>


using halo::IGameLayer;

IGameLayer::IGameLayer()
	: m_wantsToQuit{ false }
{
    LOG_WARNING("Component creation linkage should probably be moved");

	RegisterComponentCreationFunctions();
	RegisterProcessCreationFunctions();

	// Test
	m_testKill = 1;
}

IGameLayer::~IGameLayer()
{
	Cleaning();
}

// ------------------------------- //
//	Initialize Game Layer
//-------------------------------- //
bool halo::IGameLayer::Init()
{
	// Create and Init Scripter
	m_scripter = IScripter::Create();
	if (!m_scripter->Init())
	{
		LOG_ERROR("Failed to Init Scripter!");
		return false;
	}

	// Using Unique Pointers ----- 
	m_pPhysics = IPhysicsSimulation::Create(Vector2D(0, 9.8f));

	// call Register Script
	IGameLayer::RegisterWithScript();

	// add pending views
	AddPendingViewsToViews();

    return true;
}

bool halo::IGameLayer::PostInit()
{
	// Init views
	for (auto& pView : m_views)
	{
		if (!pView || !pView->Init())
		{
			return false;
		}
	}

	return true;
}

// ------------------------------- //
//	Add View Into Game Layer Views
//-------------------------------- //
void halo::IGameLayer::AddView(std::unique_ptr<IView> pView)
{
	for (size_t index = 0; index < m_views.size(); ++index)
	{
		if (m_views[index] == nullptr)
		{
			pView->SetListIndex(index);
			m_views[index] = std::move(pView);
			return;
		}
	}

	// if no room for it, emplace to the back
	pView->SetListIndex(m_views.size());
	m_views.emplace_back(std::move(pView));
	return;
}

// ------------------------------- //
// Add View Into Pending Views List
//-------------------------------- //
void halo::IGameLayer::AddPendingViews(std::unique_ptr<IView> pView)
{
	m_pendingViews.emplace_back(std::move(pView));
}

// ------------------------------- //
//	Add the view need to delete
//-------------------------------- //
void halo::IGameLayer::AddDeleteView(size_t index)
{
	m_viewDeleteList.emplace_back(index);
}

// ------------------------------- //
//	Actually delete the views
//-------------------------------- //
void halo::IGameLayer::DeleteViews()
{
	for (size_t index : m_viewDeleteList)
	{
		m_views[index] = nullptr;
	}
	// clear out delete view list
	m_viewDeleteList.clear();
}

// ------------------------------- //
//	Add Renderable Component to Map
//-------------------------------- //
void halo::IGameLayer::RegisterRenderable(GameUnit::ID id, RenderableComponent* pRenderable)
{
	m_renderableMap[id] = pRenderable;
}

// ------------------------------------ //
//	Remove Renderable Component from Map
//------------------------------------- //
void halo::IGameLayer::RemoveRenderable(GameUnit::ID id)
{
	// If Id not exit, log error and exit
	if (m_renderableMap.find(id) == m_renderableMap.end())
	{
		LOG_ERROR("Invalid Game Unit ID, Failed to Delete Renderable.");
		return;
	}
	// Erase id from map
	m_renderableMap[id] = nullptr;
	m_renderableMap.erase(id);
}

// ------------------------------------ //
//	Remove Game Unit From Lua Table
//------------------------------------- //
bool halo::IGameLayer::LuaRemoveUnit(GameUnit::ID id)
{
	if (auto pLuaScripter = GetScripter<LuaScripter>(); pLuaScripter)
	{
		pLuaScripter->GetGlobal("g_logic");
		pLuaScripter->RetrieveElementFromTable("GameUnits");
		pLuaScripter->PushNil();
		pLuaScripter->AddToTable(id);
		pLuaScripter->Pop(2);
		
		LOG_DISPLAY("Lua Game Unit - %d Successfully Removed!", id);
		return true;
	}

	LOG_ERROR("Failed to Get Lua Scripter!");
	return false;
}

// ------------------------------- //
//		Add Pending Views
//-------------------------------- //
void halo::IGameLayer::AddPendingViewsToViews()
{
	if (m_pendingViews.size() > 0)
	{
		for (auto& pView : m_pendingViews)
		{
			AddView(std::move(pView));
		}
		m_pendingViews.clear();
	}
}

// ------------------------------- //
//		  Register Script
//-------------------------------- //
void halo::IGameLayer::RegisterWithScript()
{
	// Create a lua table to store and register all the functions
	if (auto pLuaScripter = GetScripter<halo::LuaScripter>(); pLuaScripter)
	{
		pLuaScripter->CreateTable();

		// Create a lua table to store all the game object
		pLuaScripter->CreateTable();
		pLuaScripter->AddToTable("GameUnits");

		// Create a globle variable and pack everything above into this variable called logic
		pLuaScripter->SetGlobal("g_logic");
	}
}

// ------------------------------- //
//			Clean up data
//-------------------------------- //
void halo::IGameLayer::Cleaning()
{
	for (auto& pair : m_unitMap)
	{
		RemoveRenderable(pair.first);
		pair.second = nullptr;
	}
	m_renderableMap.clear();
	m_unitMap.clear();
}

// -------------------------------------- //
//	Register Component Creation Function
//--------------------------------------- //
void halo::IGameLayer::RegisterComponentCreationFunctions()
{
	// Register Transform Component Creation Function
	m_unitFactory.RegisterComponentCreator("TransformComponent", [](std::shared_ptr<GameUnit> pUnit, const char* pName)
	{
		return std::make_unique<TransformComponent>(pUnit, pName);
	});
	// Register Box Component Creation Function
	m_unitFactory.RegisterComponentCreator("BoxComponent", [](std::shared_ptr<GameUnit> pUnit, const char* pName)
	{
		return std::make_unique<BoxComponent>(pUnit, pName);
	});
	// Register Renderable Component Creation Function
	m_unitFactory.RegisterComponentCreator("RenderableComponent", [](std::shared_ptr<GameUnit> pUnit, const char* pName)
	{
		return std::make_unique<RenderableComponent>(pUnit, pName);
	});
	// Register Animator Component Creation Function
	m_unitFactory.RegisterComponentCreator("AnimatorComponent", [](std::shared_ptr<GameUnit> pUnit, const char* pName)
	{
		return std::make_unique<AnimatorComponent>(pUnit, pName);
	});
	// Register Physics Component Creation Function
	m_unitFactory.RegisterComponentCreator("Box2DPhysicsComponent", [this](std::shared_ptr<GameUnit> pUnit, const char* pName)
	{
		return std::make_unique<Box2DPhysicsComponent>(pUnit, m_pPhysics.get());
	});
}

// -------------------------------------- //
//	Register Process Creation Function
//--------------------------------------- //
void halo::IGameLayer::RegisterProcessCreationFunctions()
{
	// Register Animation Process Creation Function
	m_unitFactory.RegisterProcessCreator("AnimationProcess", [](std::shared_ptr<GameUnit> pUnit)
	{
		return std::make_shared<AnimationProcess>(pUnit);
	});

	// Register Move Process Creation Function
	m_unitFactory.RegisterProcessCreator("MoveProcess", [](std::shared_ptr<GameUnit> pUnit)
	{
		return std::make_shared<MoveProcess>(pUnit);
	});

	// Register Delay Process Creation Function
	m_unitFactory.RegisterProcessCreator("DelayProcess", [](std::shared_ptr<GameUnit> pUnit)
	{
		return std::make_shared<DelayProcess>(pUnit);
	});
}

// ------------------------------- //
//		Update Game Layer
//-------------------------------- //
void halo::IGameLayer::Update(float deltaSeconds)
{
	AddPendingViewsToViews();

	// Taking inputs
    for (auto& pView : m_views)
    {
		if(pView)
			pView->UpdateInput(deltaSeconds);
    }

	// Process Events
	EventDispatcher::Get().ProcessEvents();

	// Update Processes
	m_processController.UpdateProcesses(deltaSeconds);

	// Update Physics
	m_pPhysics->Update(deltaSeconds);

	for (auto& pUnit : m_unitMap)
	{
		pUnit.second->Update(deltaSeconds);
	}

	// Update each renderable component
	for (auto& renderablePair : m_renderableMap)
	{
		renderablePair.second->Update(deltaSeconds);
	}

	// Delete non-related views
	DeleteViews();

	// Render Scene
    for (auto& pView : m_views)
    {
		if (pView)
			pView->ViewScene();
    }
}

// ------------------------------- //
//		Spawn Game Unit
//-------------------------------- //
std::shared_ptr<halo::GameUnit> halo::IGameLayer::SpawnGameUnit(const char* filename)
{
	auto pUnit = m_unitFactory.CreateUnit(filename);

	if (!pUnit)
	{
		LOG_ERROR("Fail to Spawn Game Unit!");
		return nullptr;
	}

	AddGameUnit(pUnit->GetID(), pUnit);
	
	return pUnit;
}

// ------------------------------- //
//	Add Game Unit into Game Unit Map
//-------------------------------- //
void halo::IGameLayer::AddGameUnit(GameUnit::ID id, std::shared_ptr<GameUnit> pUnit)
{
	m_unitMap[id] = pUnit;
}

// ------------------------------- //
//		Destroy Game Unit
//-------------------------------- //
void halo::IGameLayer::DestroyGameUnit(GameUnit::ID id)
{
	// If Id not exit, log error and exit
	if (m_unitMap.find(id) == m_unitMap.end())
	{
		LOG_ERROR("Invalid Game Unit ID, Failed to Delete Unit.");
		return;
	}

	// Erase id from map
	m_unitMap[id] = nullptr;
	m_unitMap.erase(id);
	LOG_DISPLAY("Game Unit - %d Removed!", id);

	RemoveRenderable(id);
	LOG_DISPLAY("Renderable Component of Game Unit - %d Removed!", id);

	// Erase unit from lua table 
	if (!LuaRemoveUnit(id))
	{
		LOG_ERROR("Failed to Remove Game Unit - %d From Lua Table!", id);
	}
}
