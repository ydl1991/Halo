#pragma once
// \file MoveProcess.h 
// TODO: File Purpose 
// Created by Dali Yi

#include "..\IProcess.h"

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class GameUnit;
	class TransformComponent;

	// \class MoveProcess 
	// TODO: Class Purpose 
	class MoveProcess
		: public IProcess
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		MoveProcess() = default;
		MoveProcess(std::weak_ptr<halo::GameUnit> pUnit, float destX, float destY, float time);
		MoveProcess(std::weak_ptr<halo::GameUnit> pUnit);

		// Default Destructor 
		virtual ~MoveProcess();

		// Inherited from IProcess
		bool Init(tinyxml2::XMLElement* pData) final override;
		bool PostInit() final override;

		void Update(float deltaSeconds) final override;

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		TransformComponent* m_pTransform;
		float m_xDest;
		float m_yDest;
		float m_xSpeed;
		float m_ySpeed;
		float m_time;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //

	};
}