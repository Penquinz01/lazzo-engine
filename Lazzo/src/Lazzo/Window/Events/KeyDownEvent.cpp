#include "lzpch.h"
#include "KeyDownEvent.h"

namespace Lazzo
{
	KeyDownEvent::KeyDownEvent(SDL_Event event) {
		ScanCode = event.key.scancode;
	}
	int KeyDownEvent::ReturnScanCode() const {
		return ScanCode;
	}
	EventType KeyDownEvent::GetEventType() const {
		return EventType::KeyDown;
	}
}