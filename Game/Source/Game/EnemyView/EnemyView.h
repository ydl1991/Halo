#pragma once
// \file EnemyView.h 
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
	class IProcess;
	class IEvent;
}

// \class EnemyView 
// TODO: Class Purpose 
class EnemyView final
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
	EnemyView(std::shared_ptr<halo::GameUnit> pGameUnit);

	// Default Destructor 
	~EnemyView();

	// Inherited via IView
	bool Init() override;

private:
	// --------------------------------------------------------------------- //
	// Private Member Variables
	// --------------------------------------------------------------------- //
	// Systems
	halo::IAudio* m_pAudio;
	int32_t m_currentPosition;

	// Processes
	std::shared_ptr<halo::IProcess> m_pDelayProcess;
	std::shared_ptr<halo::IProcess> m_pMoveProcess;
	std::shared_ptr<halo::IProcess> m_pAnimationProcess;

	// Target Object
	std::shared_ptr<halo::GameUnit> m_pTarget;

	// Owner Object
	size_t m_listenerID;

	// --------------------------------------------------------------------- //
	// Private Member Functions
	// --------------------------------------------------------------------- //
	void CreateDelayProcess();
	void CreateMoveProcess();
	void CreateAnimationProcess();

	// Object Related
	void DestroyGameUnit(halo::IEvent* pEvent);

public:
	// --------------------------------------------------------------------- //
	// Accessors & Mutators
	// --------------------------------------------------------------------- //
	void SetTarget(std::shared_ptr<halo::GameUnit> pPlayer) { m_pTarget = pPlayer; }
};