#pragma once
#include "Event.h"

namespace Lazzo {
	class KeyUpEvent : public Event {
	public:
		KeyUpEvent(SDL_Event event);
		int GetScanCode() const;
		EventType GetEventType() const override;
	private:
		int m_ScanCode;
	};
}
