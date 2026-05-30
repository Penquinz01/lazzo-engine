#pragma once
#include "Event.h"

namespace Lazzo {
	class KeyDownEvent : public Event {
	public:
		KeyDownEvent(SDL_Event event);
		int ReturnScanCode() const;
		EventType GetEventType() const override;
	private:
		int ScanCode;
	};
}