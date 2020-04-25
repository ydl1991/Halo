#include "GameLogic.h"

// View
#include <Game/PlayerView/PlayerView.h>
#include <Game/EnemyView/EnemyView.h>
// App
#include <ApplicationLayer/ApplicationLayer.h>

// Event
#include <GameLayer/Event/Events/CreateActorEvent.h>
// Transform Component
#include <GameLayer/Components/TransformComponent/TransformComponent.h>
// Resource
#include <GameLayer/Resource/ResourceCache.h>
// Unit Factory
#include <GameLayer/GameUnit/UnitFactory.h>
// Log
#include <Utils/Log.h>
// Script
#include <GameLayer/Script/LuaScripter.h>
#include "Game/GameLogic.gen"

GameLogic::GameLogic()
{

}

GameLogic::~GameLogic()
{
	
}

bool GameLogic::Init()
{	
	if (bool result = IGameLayer::Init(); !result)
	{
		return result;
	}
	
	// Register with Lua
	RegisterWithScript();

	// Run script
	m_scripter->RunScript("Assets/Lua/Script.lua");

	// ------------------------------ //
	//	Create Game Units from Events
	// ------------------------------ //
	//// Register event handler
	//halo::EventDispatcher::Get().AddEventListener(halo::CreateActorEvent::m_kEventID, [this](halo::IEvent* pEvent) {
	//	CreateGameUnit(pEvent);
	//});
	////create actor event
	//halo::EventDispatcher::Get().QueueEvent(std::make_unique<halo::CreateActorEvent>("Assets/XML/TestPlayerUnit.xml", halo::CreateActorEvent::OwningViewType::kPlayer));

	//halo::EventDispatcher::Get().QueueEvent(std::make_unique<halo::CreateActorEvent>("Assets/XML/TestEnemyUnit.xml", halo::CreateActorEvent::OwningViewType::kEnemy));

	////--------------------------//
	////		Create player
	////--------------------------//
	//auto pPlayer = SpawnGameUnit("Assets/XML/TestPlayerUnit.xml");
	////		Init Player View
	//auto pPlayerView = new PlayerView(pPlayer);
	//AddView(std::unique_ptr<halo::IView>(pPlayerView));
	//
	////--------------------------//
	////		Create enemy
	////--------------------------//
	//auto pEnemy = SpawnGameUnit("Assets/XML/TestEnemyUnit.xml");
	////		Init Enemy View
	//auto pEnemyView = new EnemyView(pEnemy);
	//pEnemyView->SetTarget(pPlayer);
	//AddView(std::unique_ptr<halo::IView>(pEnemyView));

	return true;
}

const char* GameLogic::GetGameName() const
{
	return "Halo Test Game";
}

// Event Handler
void GameLogic::CreateGameUnit(halo::IEvent* pEvent)
{
	auto pCreateActor = static_cast<halo::CreateActorEvent*>(pEvent);
	auto pUnit = SpawnGameUnit(pCreateActor->GetFilename());
	
	halo::IView* pView = nullptr;

	switch (pCreateActor->GetViewType())
	{
	case halo::CreateActorEvent::OwningViewType::kPlayer:
		pView = new PlayerView(pUnit);
		break;
	case halo::CreateActorEvent::OwningViewType::kEnemy:
		pView = new EnemyView(pUnit);
		break;
	}

	if (!pView || !pView->Init())
	{
		LOG_ERROR("Failed to initialize view during event: %s", pCreateActor->GetEventName());
		return;
	}

	AddView(std::unique_ptr<halo::IView>(pView));
}

//---------------------------------------------------//
//          Lua Function Create Game Unit
//---------------------------------------------------//
int Lua::GameLogicCreateGameUnit(lua_State* pState)
{
	const char* pXML = luaL_checkstring(pState, 1);

	auto pGameLayer = halo::ApplicationLayer::Get()->GetGameLayer();
	auto unitFactory = pGameLayer->GetUnitFactory();
	auto pUnit = unitFactory.CreateUnit(pXML);
	pGameLayer->AddGameUnit(pUnit->GetID(), pUnit);

	lua_pop(pState, 1);

	// add the game unit to game unit table
	lua_getglobal(pState, "g_logic");
	lua_getfield(pState, -1, "GameUnits");
	lua_newtable(pState);
	lua_rawseti(pState, -2, pUnit->GetID());
	lua_pop(pState, 2);

	pUnit->RegisterWithScript();

	lua_pushinteger(pState, pUnit->GetID());
	return 1;
}

//---------------------------------------------------//
//         Lua Function Create Player View
//---------------------------------------------------//
int Lua::GameLogicCreatePlayerView(lua_State* pState)
{
	auto unitId = static_cast<halo::GameUnit::ID>(luaL_checkinteger(pState, 1));
	lua_pop(pState, 1);

	auto pGameLayer = halo::ApplicationLayer::Get()->GetGameLayer();
	std::shared_ptr<halo::GameUnit> pUnit = pGameLayer->GetGameUnit(unitId);

	auto pView = std::make_unique<PlayerView>(pUnit);
	pView->Init();

	pGameLayer->AddPendingViews(std::move(pView));
	return 0;
}

//---------------------------------------------------//
//             Lua Function Create Enemy View
//---------------------------------------------------//
int Lua::GameLogicCreateEnemyView(lua_State* pState)
{
	auto unitId = static_cast<halo::GameUnit::ID>(luaL_checkinteger(pState, 1));
	lua_pop(pState, 1);

	auto pGameLayer = halo::ApplicationLayer::Get()->GetGameLayer();
	std::shared_ptr<halo::GameUnit> pUnit = pGameLayer->GetGameUnit(unitId);

	auto pView = std::make_unique<EnemyView>(pUnit);
	pView->Init();

	pGameLayer->AddPendingViews(std::move(pView));
	return 0;
}

//---------------------------------------------------//
//             Lua Function Play Music
//---------------------------------------------------//
int Lua::GameLogicPlayMusic(lua_State* pState)
{
	const char* pFileName = luaL_checkstring(pState, 1);

	// play music
	halo::ApplicationLayer::Get()->GetAudio()->PlayMusic(pFileName);

	lua_pop(pState, 1);

	return 0;
}

//---------------------------------------------------//
//             Lua Function Play Sound
//---------------------------------------------------//
int Lua::GameLogicPlaySoundChunk(lua_State* pState)
{
	const char* pFileName = luaL_checkstring(pState, 1);

	// play music
	halo::ApplicationLayer::Get()->GetAudio()->PlaySound(pFileName);

	lua_pop(pState, 1);

	return 0;
}

//---------------------------------------------------//
//             Lua Function Log
//---------------------------------------------------//
int Lua::GameLogicLog(lua_State* pState)
{
	// Get the message from the stack
	// In lua, stack can be accessed backwards by using negative numbers:
	//        [-1] top of the stack
	const char* message = lua_tostring(pState, -1);

	// Grab debug info from the stack (where this was called from)
	lua_Debug ar;
	lua_getstack(pState, 1, &ar);
	lua_getinfo(pState, "Slnt", &ar);

	// Shorten file name for easy reading
	static std::string file;
	file = ar.short_src;
	file = file.substr(file.rfind('/') + 1);

	// Log it!
	LOG_LUA_A(ar.currentline, file.c_str(), message);

	return 0;
}

//---------------------------------------------------//
//             Lua Function Log Error
//---------------------------------------------------//
int Lua::GameLogicLogError(lua_State* pState)
{
	// Get the message from the stack
	// In lua, stack can be accessed backwards by using negative numbers:
	//        [-1] top of the stack
	const char* message = lua_tostring(pState, -1);

	// Grab debug info from the stack (where this was called from)
	lua_Debug ar;
	lua_getstack(pState, 1, &ar);
	lua_getinfo(pState, "Slnt", &ar);

	// Shorten file name for easy reading
	static std::string file;
	file = ar.short_src;
	file = file.substr(file.rfind('/') + 1);

	// Log it!
	LOG_LUAERROR_A(ar.currentline, file.c_str(), message);

	return 0;
}