#pragma once
#include "Event.h"

namespace Lazzo {
	class LAZZO_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(SDL_Event event);
		float GetOffsetX() const;
		float GetOffsetY() const;
		EventType GetEventType() const override;
	private:
		float m_OffsetX;
		float m_OffsetY;
	};
}
