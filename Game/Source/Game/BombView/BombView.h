#pragma once
// \file BombView.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <memory>
#include <unordered_map>
#include <optional>

#include <ApplicationLayer/View/IView.h>
//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class IAudio;
}

// \class BombView 
// TODO: Class Purpose 
class BombView final
	: public halo::IView
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	// Default Constructor 
	BombView(std::shared_ptr<halo::GameUnit> pGameUnit);

	// Default Destructor 
	~BombView();

	// Inherited via IView
	bool Init() override;

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //
	// Systems
	halo::IAudio* m_pAudio;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //


public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //
};