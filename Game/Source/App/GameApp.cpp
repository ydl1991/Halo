#include "GameApp.h"

#include <Game/GameLogic.h>
GameApp::GameApp()
{
	
}

GameApp::~GameApp()
{
	
}

std::unique_ptr<halo::IGameLayer> GameApp::CreateGameLayer()
{
	return std::make_unique<GameLogic>();
}
