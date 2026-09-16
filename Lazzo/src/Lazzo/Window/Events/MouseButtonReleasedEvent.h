#pragma once
#include "Event.h"

namespace Lazzo {
	class MouseButtonReleasedEvent : public Event {
	public:
		MouseButtonReleasedEvent(SDL_Event event);
		int GetButton() const;
		float GetX() const;
		float GetY() const;
		EventType GetEventType() const override;
	private:
		int m_Button;
		float m_X;
		float m_Y;
	};
}
