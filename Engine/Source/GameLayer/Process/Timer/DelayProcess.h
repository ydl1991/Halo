#pragma once
// \file DelayProcess.h 
// TODO: File Purpose 
// Created by Dali Yi

#include "..\IProcess.h"

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class DelayProcess 
	// TODO: Class Purpose 
	class DelayProcess
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
		DelayProcess() = default;
		DelayProcess(std::weak_ptr<halo::GameUnit> pOwner, float time);
		DelayProcess(std::weak_ptr<halo::GameUnit> pOwner);

		// Default Destructor 
		~DelayProcess();

		void Update(float deltaSeconds) final override;

		bool Init(tinyxml2::XMLElement* pData) final override;
		bool PostInit() final override;

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		float m_duration;
		float m_timer;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //

	};
}