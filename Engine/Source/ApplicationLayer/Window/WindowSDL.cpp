#include "WindowSDL.h"

#include <SDL/SDL.h>

#include <Utils/Log.h>

using halo::WindowSDL;

WindowSDL::WindowSDL()
	: m_pSDLWindow{ nullptr, nullptr }
	, m_isInitialized{ false }
{
	
}

WindowSDL::~WindowSDL()
{
	m_pSDLWindow = nullptr;
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	SDL_Quit();
}

bool halo::WindowSDL::Init(const char* name, uint32_t width, uint32_t height)
{
	if (SDL_InitSubSystem(SDL_INIT_VIDEO))
	{
		LOG_FATAL("Failed to Init SDL Video.");
		return false;
	}

	// Create the window
	m_pSDLWindow = UniqueWindow(SDL_CreateWindow(name, 
												 SDL_WINDOWPOS_CENTERED, 
												 SDL_WINDOWPOS_CENTERED, 
												 width, 
												 height, 
												 SDL_WINDOW_SHOWN), 
								&SDL_DestroyWindow);

	if (!m_pSDLWindow)
	{
		LOG_ERROR("Failed to Create SDL Window.");
		return false;
	}

	// Only set to true if all inits have passed
	m_isInitialized = true;
	return true;
}

bool halo::WindowSDL::ProcessEvents() const
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
		{
			return false;
		}
		else if (m_pKeyboard && (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP))
		{
			halo::KeyCode code = ConvertToCode(event.key.keysym.scancode);
			m_pKeyboard->SetKeyState(code, event.type == SDL_KEYDOWN);
		}
		else if (m_pMouse && (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP))
		{
			halo::MouseButton button = ConvertToButton(event.button.button);
			m_pMouse->SetButtonState(button, event.type == SDL_MOUSEBUTTONDOWN);
		}
		else if (m_pMouse && event.type == SDL_MOUSEWHEEL)
		{
			m_pMouse->SetWheelNum(event.wheel.y);
		}
	}
	return true;
}

void* halo::WindowSDL::GetNativeWindow() const
{
	return m_pSDLWindow.get();
}

//---------------------------------------------//
//	Set both Keyboard and Mouse to Next Frame
//---------------------------------------------//
void halo::WindowSDL::NextFrame()
{
	m_pKeyboard->NextFrame();
	m_pMouse->NextFrame();
}

//---------------------------------------------//
//	Convert SDL Key to Engine Key Code
//---------------------------------------------//
halo::KeyCode halo::WindowSDL::ConvertToCode(uint32_t key) const
{
	if (key >= SDL_SCANCODE_A && key <= SDL_SCANCODE_Z)
	{
		return static_cast<halo::KeyCode>(key -
			SDL_SCANCODE_A + halo::kA);
	}
	else if (key >= SDL_SCANCODE_0 && key <= SDL_SCANCODE_9)
	{
		return static_cast<halo::KeyCode>(key -
			SDL_SCANCODE_9 + halo::k0);
	}
	else if (key == SDL_SCANCODE_SPACE)
	{
		return halo::kSpace;
	}
	else if (key == SDL_SCANCODE_ESCAPE)
	{
		return halo::kEscape;
	}
	else if (key == SDL_SCANCODE_UP)
	{
		return halo::kArrowUp;
	}
	else if (key == SDL_SCANCODE_DOWN)
	{
		return halo::kArrowDown;
	}
	else if (key == SDL_SCANCODE_RIGHT)
	{
		return halo::kArrowRight;
	}
	else if (key == SDL_SCANCODE_LEFT)
	{
		return halo::kArrowLeft;
	}
	return halo::kKeyMax;
}

//---------------------------------------------//
//	Convert SDL Button to Engine Button Code
//---------------------------------------------//
halo::MouseButton halo::WindowSDL::ConvertToButton(uint32_t button) const
{
	static const uint32_t kSDLLeftButton = 1;
	static const uint32_t kSDLRightButton = 3;
	if (button == kSDLLeftButton)
	{
		return halo::kButtonLeft;
	}
	else if (button == kSDLRightButton)
	{
		return halo::kButtonRight;
	}
	return halo::kButtonMax;
}
