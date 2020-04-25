#pragma once
// \file GameLogic.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <GameLayer/IGameLayer.h>
#include <GameLayer/Event/IEvent.h>

class IComponent;
class ApplicationLayer;

// \class GameLogic 
// Game Logic is a game side game layer 
class GameLogic : public halo::IGameLayer
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	// Default Constructor 
	GameLogic();

	// Default Destructor 
	virtual ~GameLogic();

	virtual bool Init() final override;

	// Inherited via IGameLayer
	virtual const char* GetGameName() const final override;

	// Event Handler
	void CreateGameUnit(halo::IEvent* pEvent);

	// Lua Custom functions binding
	LUA_CUSTOMGLUE(CreateGameUnit)
	LUA_CUSTOMGLUE(CreatePlayerView)
	LUA_CUSTOMGLUE(CreateEnemyView)
	LUA_CUSTOMGLUE(PlayMusic)
	LUA_CUSTOMGLUE(PlaySoundChunk)
	LUA_CUSTOMGLUE(Log)
	LUA_CUSTOMGLUE(LogError)

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //
	LUA_REGISTER();

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};

// ---------------------------- //
//		Functions For Lua
// ---------------------------- //
namespace Lua
{
	static int GameLogicCreateGameUnit(lua_State* pState);
	static int GameLogicCreatePlayerView(lua_State* pState);
	static int GameLogicCreateEnemyView(lua_State* pState);
	static int GameLogicPlayMusic(lua_State* pState);
	static int GameLogicPlaySoundChunk(lua_State* pState);
	static int GameLogicLog(lua_State* pState);
	static int GameLogicLogError(lua_State* pState);
}