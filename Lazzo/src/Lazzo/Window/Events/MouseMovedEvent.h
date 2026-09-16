#pragma once
#include "Event.h"

namespace Lazzo {
	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(SDL_Event event);
		float GetX() const;
		float GetY() const;
        float GetRelX() const;
        float GetRelY() const;
		EventType GetEventType() const override;
	private:
		float m_X;
		float m_Y;
        float m_RelX;
        float m_RelY;
	};
}
