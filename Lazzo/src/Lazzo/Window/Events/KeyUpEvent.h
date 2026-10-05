#pragma once
#include "Event.h"

namespace Lazzo {
	class LAZZO_API KeyUpEvent : public Event {
	public:
		KeyUpEvent(SDL_Event event);
		int GetScanCode() const;
		EventType GetEventType() const override;
	private:
		int m_ScanCode;
	};
}
