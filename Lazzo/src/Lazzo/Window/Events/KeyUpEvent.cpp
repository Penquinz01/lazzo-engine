#include "lzpch.h"
#include "KeyUpEvent.h"

namespace Lazzo
{
	KeyUpEvent::KeyUpEvent(SDL_Event event) {
		m_ScanCode = event.key.scancode;
	}
	int KeyUpEvent::GetScanCode() const {
		return m_ScanCode;
	}
	EventType KeyUpEvent::GetEventType() const {
		return EventType::KeyUp;
	}
}
