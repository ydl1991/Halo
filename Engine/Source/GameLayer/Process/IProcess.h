#pragma once
// \file IProcess.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <functional>
#include <memory>
#include <Utils/TinyXml/tinyxml2.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class GameUnit;

	// \class IProcess 
	// TODO: Class Purpose 
	class IProcess
	{
	public:
		enum State
		{
			kSucceeded,
			kFailed,
			kAborted,

			kNumStatesWithCallback,

			kUninitialized,
			kRunning,
			kPaused,
		};

		// Alias
		using Callback = std::function<void()>;
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		IProcess() = default;
		IProcess(std::weak_ptr<halo::GameUnit> pOwner);

		// Default Destructor 
		virtual ~IProcess();

		// virtuals 
		virtual bool PostInit() { return true;  }
		virtual bool Init(tinyxml2::XMLElement* pData) { return true; }
		virtual void Update(float deltaSeconds);

		// functions
		void OnFailure() { if (m_stateCallbacks[kFailed]) m_stateCallbacks[kFailed](); }
		void OnSucceed() { if (m_stateCallbacks[kSucceeded]) m_stateCallbacks[kSucceeded](); }
		void OnAbort() { if (m_stateCallbacks[kAborted]) m_stateCallbacks[kAborted](); }

		std::shared_ptr<IProcess> RemoveChild();

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		State m_state;
		Callback m_stateCallbacks[State::kNumStatesWithCallback];
		std::shared_ptr<IProcess> m_pChild;
		std::weak_ptr<halo::GameUnit> m_pOwner;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //


	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
		// Get Owner
		std::shared_ptr<halo::GameUnit> GetOwner() { return m_pOwner.lock(); }

		// State Getter
		State GetState() const { return m_state; }
		
		// State Setters
		void Succeed() { m_state = State::kSucceeded; }
		void Abort() { m_state = State::kAborted; }
		void Fail() { m_state = State::kFailed; }
		void Pause() { m_state = State::kPaused; }
		void Resume() { m_state = State::kRunning; }
		void Reset() { m_state = State::kUninitialized; }

		// State Checkers
		bool IsAlive() { return (m_state == State::kRunning || m_state == State::kPaused); }
		bool IsDead() { return (!IsAlive() && m_state != State::kUninitialized); }

		// Set Callback function for states
		void SetCallback(State state, Callback callback) { m_stateCallbacks[state] = callback; }

		// add child process
		void AttachChild(std::shared_ptr<IProcess> pChild) { m_pChild = pChild; }
	};
}