#include "lzpch.h"
#include "MouseButtonReleasedEvent.h"

namespace Lazzo
{
	MouseButtonReleasedEvent::MouseButtonReleasedEvent(SDL_Event event) {
		m_Button = event.button.button;
		m_X = event.button.x;
		m_Y = event.button.y;
	}
	int MouseButtonReleasedEvent::GetButton() const {
		return m_Button;
	}
	float MouseButtonReleasedEvent::GetX() const {
		return m_X;
	}
	float MouseButtonReleasedEvent::GetY() const {
		return m_Y;
	}
	EventType MouseButtonReleasedEvent::GetEventType() const {
		return EventType::MouseButtonReleased;
	}
}
