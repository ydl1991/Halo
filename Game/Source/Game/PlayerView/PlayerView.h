#pragma once
// \file PlayerView.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <memory>
#include <unordered_map>
#include <optional>

#include <ApplicationLayer/View/IView.h>
#include <Utils/Math/Shapes/Shapes.h>
#include <Utils/Color/Color.h>
#include <GameLayer/Script/LuaScripter.h>

namespace halo
{
	class IKeyboard;
	class IMouse;
	class IAudio;
	class ITexture;
	class IGraphics;
	class TransformComponent;
}

// \class PlayerView 
// TODO: Class Purpose 
class PlayerView final
	: public halo::IView
{
public:
	// --------------------------------------------------------------------- //
	// Public Member Variables
	// --------------------------------------------------------------------- //


	// --------------------------------------------------------------------- //
	// Public Member Functions
	// --------------------------------------------------------------------- //
	// Constructor 
	PlayerView(std::shared_ptr<halo::GameUnit> pGameUnit);

	// Default Destructor 
	~PlayerView();

	// Inherited via IView
	bool Init() final override;
	void UpdateInput(float delta) final override;
	void ViewScene() final override;

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //
	// Systems
	halo::IGraphics* m_pGraphics;
	halo::IKeyboard* m_pKeyboard;
	halo::IMouse* m_pMouse;
	halo::IAudio* m_pAudio;
	halo::Color m_color;

	// Gameplay
	bool m_attackOnCoolDown;
	halo::TransformComponent* m_pOwnerTransform;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //
};