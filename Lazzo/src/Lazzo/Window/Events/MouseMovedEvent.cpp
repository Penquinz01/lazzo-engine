#include "lzpch.h"
#include "MouseMovedEvent.h"

namespace Lazzo
{
	MouseMovedEvent::MouseMovedEvent(SDL_Event event) {
		m_X = event.motion.x;
		m_Y = event.motion.y;
        m_RelX = event.motion.xrel;
        m_RelY = event.motion.yrel;
	}
	float MouseMovedEvent::GetX() const {
		return m_X;
	}
	float MouseMovedEvent::GetY() const {
		return m_Y;
	}
    float MouseMovedEvent::GetRelX() const {
        return m_RelX;
    }
    float MouseMovedEvent::GetRelY() const {
        return m_RelY;
    }
	EventType MouseMovedEvent::GetEventType() const {
		return EventType::MouseMoved;
	}
}
