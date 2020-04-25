#pragma once
// \file AnimationProcess.h 
// TODO: File Purpose 
// Created by Dali Yi

#include "..\IProcess.h"

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class GameUnit;
	class AnimatorComponent;

	// \class AnimationProcess 
	// TODO: Class Purpose 
	class AnimationProcess
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
		AnimationProcess() = default;
		AnimationProcess(std::weak_ptr<halo::GameUnit> pUnit, float frameRate, float nextFrameTime);
		AnimationProcess(std::weak_ptr<halo::GameUnit> pUnit);

		// Default Destructor 
		~AnimationProcess();

		// Inherited via IProcess
		bool Init(tinyxml2::XMLElement* pData) final override;
		bool PostInit() final override;

		void Update(float deltaSeconds) final override;

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		AnimatorComponent* m_pAnimator;

		// Time when the animation should advance to the next frame
		float m_nextFrameTime;
		// Frame rate per second
		float m_frameRate;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		// change frame rate
		void SetFrameRate(float rate) { m_frameRate = rate; }
		void ResetFrameTime();
	};
}