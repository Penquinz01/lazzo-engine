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
    bool handled = false;
};

class EventDispatcher {
public :
    EventDispatcher(Event& event) :m_Event(event) {}

    template <typename T, typename F>
    bool Dispatch(const F& func) {
        if (m_Event.GetEventType() == T::GetEventType()) {
            m_Event.handled = func(static_cast<T&>(m_Event));
            return true;
        }
        return false;
    }

private:
	Event& m_Event;
};
