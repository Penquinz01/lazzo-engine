#include "lzpch.h"
#include "MouseScrolledEvent.h"

namespace Lazzo
{
	MouseScrolledEvent::MouseScrolledEvent(SDL_Event event) {
		m_OffsetX = event.wheel.x;
		m_OffsetY = event.wheel.y;
	}
	float MouseScrolledEvent::GetOffsetX() const {
		return m_OffsetX;
	}
	float MouseScrolledEvent::GetOffsetY() const {
		return m_OffsetY;
	}
	EventType MouseScrolledEvent::GetEventType() const {
		return EventType::MouseScrolled;
	}
}
