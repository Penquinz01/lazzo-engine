#pragma once
#include "Event.h"

namespace Lazzo {
	class MouseButtonPressedEvent : public Event {
	public:
		MouseButtonPressedEvent(SDL_Event event);
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
