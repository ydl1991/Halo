#include "IMouse.h"

using halo::IMouse;

IMouse::IMouse()
	: m_buttonState{ false }
	, m_prevButtonState{ false }
	, m_wheelValue{ 0 }
{
	
}

IMouse::~IMouse()
{
	
}

bool halo::IMouse::Init()
{
	return true;
}

void halo::IMouse::SetButtonState(halo::MouseButton button, bool down)
{
	if (button != kButtonMax)
	{
		m_buttonState[button] = down;
	}
}

std::unique_ptr<IMouse> halo::IMouse::Create()
{
	return std::make_unique<IMouse>();
}

void halo::IMouse::NextFrame()
{
	std::copy(std::begin(m_buttonState), std::end(m_buttonState), std::begin(m_prevButtonState));
	m_wheelValue = 0;
}