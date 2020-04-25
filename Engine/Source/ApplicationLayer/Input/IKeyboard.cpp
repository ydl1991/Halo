#include "IKeyboard.h"

using halo::IKeyboard;

IKeyboard::IKeyboard()
	: m_keyState{false}
	, m_prevKeyState{false}
{
	
}

IKeyboard::~IKeyboard()
{
	
}

bool halo::IKeyboard::Init()
{
	return true;
}

void halo::IKeyboard::SetKeyState(halo::KeyCode key, bool down)
{
	if (key != kKeyMax)
	{
		m_keyState[key] = down;
	}
}

std::unique_ptr<IKeyboard> halo::IKeyboard::Create()
{
	return std::make_unique<IKeyboard>();
}