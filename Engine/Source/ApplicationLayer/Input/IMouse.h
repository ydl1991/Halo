#pragma once
// \file IMouse.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <algorithm>
#include <memory>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \enum Button
	enum MouseButton
	{
		// Key Buttons
		kButtonLeft = 0,
		kButtonRight,

		// Total
		kButtonMax,
	};

	// \class IMouse 
	// TODO: Class Purpose 
	class IMouse
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		IMouse();

		// Default Destructor 
		virtual ~IMouse();

		// Initialize function
		virtual bool Init();
		virtual void NextFrame();
		// Mouse Button
		virtual void SetButtonState(halo::MouseButton button, bool down);
		virtual bool IsButtonDown(halo::MouseButton button) const { return m_buttonState[button]; }
		virtual bool IsButtonPressed(halo::MouseButton button) const { return m_buttonState[button] && m_prevButtonState[button]; }
		virtual bool IsButtonReleased(halo::MouseButton button) const { return !m_buttonState[button] && m_prevButtonState[button]; }
		// Mouse Wheel
		virtual void SetWheelNum(int val) { m_wheelValue = val; }
		virtual bool IsScrollingUp() const { return m_wheelValue > 0; }
		virtual bool IsScrollingDown() const { return m_wheelValue < 0; }
		virtual int GetWheelValue() const { return m_wheelValue; }
	
		// Create Keyboard Instance
		static std::unique_ptr<IMouse> Create();

	protected:
		// --------------------------------------------------------------------- //
		// Protected Member Variables
		// --------------------------------------------------------------------- //
		// Mouse Button
		bool m_buttonState[halo::MouseButton::kButtonMax];
		bool m_prevButtonState[halo::MouseButton::kButtonMax];

		// Mouse Wheel
		int m_wheelValue;

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