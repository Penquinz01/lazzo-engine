#pragma once
#include "Event.h"

namespace Lazzo {
	class LAZZO_API KeyDownEvent : public Event {
	public:
		KeyDownEvent(SDL_Event event);
		int ReturnScanCode() const;
		EventType GetEventType() const override;
	private:
		int ScanCode;
	};
}