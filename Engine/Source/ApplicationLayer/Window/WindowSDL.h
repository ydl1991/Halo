#pragma once
// \file WindowSDL.h 
// TODO: File Purpose 
// Created by Dali Yi

#include ".\IWindow.h"

#include <memory>
#include <SDL/SDL_video.h>

//! \namespace halo Contains all Halo Engine code
namespace halo
{
	class IKeyboard;
	class IMouse;
	// \class WindowSDL 
	// TODO: Class Purpose 
	class WindowSDL final 
		: public IWindow
	{
	public:
		// Alias 
		using UniqueWindow = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

		// --------------------------------------------------------------------- //
		// Public Member Variables
		// --------------------------------------------------------------------- //


		// --------------------------------------------------------------------- //
		// Public Member Functions
		// --------------------------------------------------------------------- //
		// Default Constructor 
		WindowSDL();

		// Default Destructor 
		~WindowSDL();

		// Inherited via IWindow
		virtual bool Init(const char* name, uint32_t width, uint32_t height) override final;
		virtual bool ProcessEvents() const final override;
		virtual void* GetNativeWindow() const final override;
		// input related
		virtual void NextFrame() final override;
		virtual void AttachKeyboard(std::unique_ptr<IKeyboard> pInput) final override { m_pKeyboard = std::move(pInput); }
		virtual IKeyboard* GetKeyboard() const final override { return m_pKeyboard.get(); }
		virtual void AttachMouse(std::unique_ptr<IMouse> pInput) final override { m_pMouse = std::move(pInput); }
		virtual IMouse* GetMouse() const final override { return m_pMouse.get(); }

		// Input Convert Functions
		halo::KeyCode ConvertToCode(uint32_t key) const;
		halo::MouseButton ConvertToButton(uint32_t button) const;

	private:
		// --------------------------------------------------------------------- //
		// Private Member Variables
		// --------------------------------------------------------------------- //
		bool m_isInitialized;
		UniqueWindow m_pSDLWindow;

		// input systems
		std::unique_ptr<IKeyboard> m_pKeyboard;
		std::unique_ptr<IMouse> m_pMouse;

		// --------------------------------------------------------------------- //
		// Private Member Functions
		// --------------------------------------------------------------------- //

	public:
		// --------------------------------------------------------------------- //
		// Accessors & Mutators
		// --------------------------------------------------------------------- //
	};
}