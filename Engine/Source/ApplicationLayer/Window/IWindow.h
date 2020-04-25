#pragma once
// \file IWindow.h 
// TODO: File Purpose 
// Created by Dali Yi

#include <stdint.h>

#include <ApplicationLayer/Input/IKeyboard.h>
#include <ApplicationLayer/Input/IMouse.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	// \class IWindow 
	// TODO: Class Purpose 
	class IWindow
	{
	public:
		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		IWindow();

		// Default Destructor 
		virtual ~IWindow();

		// pure virtual
		virtual bool Init(const char* name, uint32_t width, uint32_t height) = 0;
		// if returns false, the window has been closed
		virtual bool ProcessEvents() const = 0;
		virtual void* GetNativeWindow() const = 0;
		// input related
		virtual void NextFrame() = 0;
		virtual void AttachKeyboard(std::unique_ptr<IKeyboard> pInput) = 0;
		virtual IKeyboard* GetKeyboard() const = 0;
		virtual void AttachMouse(std::unique_ptr<IMouse> pInput) = 0;
		virtual IMouse* GetMouse() const = 0;

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