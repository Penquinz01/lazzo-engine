#include "lzpch.h"
#include "MouseButtonPressedEvent.h"

namespace Lazzo
{
	MouseButtonPressedEvent::MouseButtonPressedEvent(SDL_Event event) {
		m_Button = event.button.button;
		m_X = event.button.x;
		m_Y = event.button.y;
	}
	int MouseButtonPressedEvent::GetButton() const {
		return m_Button;
	}
	float MouseButtonPressedEvent::GetX() const {
		return m_X;
	}
	float MouseButtonPressedEvent::GetY() const {
		return m_Y;
	}
	EventType MouseButtonPressedEvent::GetEventType() const {
		return EventType::MouseButtonPressed;
	}
}
