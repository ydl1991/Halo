#pragma once
// \file GameApp.h 
// TODO: File Purpose 
// Created by Dali Yi


#include <ApplicationLayer/ApplicationLayer.h>

// \class GameApp 
// TODO: Class Purpose 
class GameApp
	: public halo::ApplicationLayer
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	// Default Constructor 
	GameApp();

	// Default Destructor 
	virtual ~GameApp();

	// Inherited via ApplicationLayer
	virtual std::unique_ptr<halo::IGameLayer> CreateGameLayer() final override;

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //


};