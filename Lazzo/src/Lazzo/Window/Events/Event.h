#pragma once

#include <SDL3/SDL_events.h>

enum class EventType {
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyDown, KeyUp, KeyPress,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

class Event {
public:
	Event() = default;
	virtual ~Event() = default;
	virtual EventType GetEventType() const = 0;
};
