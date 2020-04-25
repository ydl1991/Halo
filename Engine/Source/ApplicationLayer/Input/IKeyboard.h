#pragma once
// \file IKeyboard.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <algorithm>
#include <memory>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \enum Code
	enum KeyCode
	{
		// 26 characters
		kA = 0, kB, kC, kD, kE, kF, kG, kH, kI, kJ, kK, kL, kM, kN, kO, kP, kQ, kR, kS, kT, kU, kV, kW, kX, kY, kZ,

		// 9 numbers
		k0, k1, k2, k3, k4, k5, k6, k7, k8, k9,

		// keyboard keys
		kSpace, kEscape, kArrowLeft, kArrowRight, kArrowUp, kArrowDown,

		// Total
		kKeyMax,
	};

	// \class IKeyboard 
	// TODO: Class Purpose 
	class IKeyboard
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //

		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		IKeyboard();

		// Default Destructor 
		virtual ~IKeyboard();

		// Initialize function
		virtual bool Init();
		virtual void SetKeyState(halo::KeyCode key, bool down);
		virtual bool IsKeyDown(halo::KeyCode key) const { return m_keyState[key]; }
		virtual bool IsKeyPressed(halo::KeyCode key) const { return m_keyState[key] && m_prevKeyState[key]; }
		virtual bool IsKeyReleased(halo::KeyCode key) const { return !m_keyState[key] && m_prevKeyState[key]; }
		virtual void NextFrame() { std::copy(std::begin(m_keyState), std::end(m_keyState), std::begin(m_prevKeyState)); }

		// Create Keyboard Instance
		static std::unique_ptr<IKeyboard> Create();

	protected:
		// --------------------------------------------------------------------- //
		// Protected Member Variables
		// --------------------------------------------------------------------- //
		bool m_keyState[halo::KeyCode::kKeyMax];
		bool m_prevKeyState[halo::KeyCode::kKeyMax];

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
}