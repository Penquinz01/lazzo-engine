#include "lzpch.h"
#include "InputManager.h"
#include "Lazzo/Window/Events/Events.h"
#include "Lazzo/Log.h"

namespace Lazzo {
    CallbackID InputManager::RegisterCallback(EventType type, EventCallback callback) {
        CallbackID id = m_NextID++;
        m_Callbacks[type].emplace_back(id, std::move(callback));
        return id;
    }

    void InputManager::UnregisterCallback(CallbackID id) {
        m_PendingRemoval.push_back(id);
    }

    void InputManager::ProcessEvent(const SDL_Event& sdlEvent) {
        EventType type = EventType::None;
        std::unique_ptr<Event> event;

        switch (sdlEvent.type) {
        case SDL_EVENT_KEY_DOWN: {
            type = EventType::KeyDown;
            event = std::make_unique<KeyDownEvent>(sdlEvent);
            m_KeyStates[sdlEvent.key.scancode] = true;
            break;
        }
        case SDL_EVENT_KEY_UP: {
            type = EventType::KeyUp;
            event = std::make_unique<KeyUpEvent>(sdlEvent);
            m_KeyStates[sdlEvent.key.scancode] = false;
            break;
        }
        case SDL_EVENT_MOUSE_MOTION: {
            type = EventType::MouseMoved;
            event = std::make_unique<MouseMovedEvent>(sdlEvent);
            m_MouseX = sdlEvent.motion.x;
            m_MouseY = sdlEvent.motion.y;
            break;
        }
        case SDL_EVENT_MOUSE_BUTTON_DOWN: {
            type = EventType::MouseButtonPressed;
            event = std::make_unique<MouseButtonPressedEvent>(sdlEvent);
            m_MouseButtonStates[sdlEvent.button.button] = true;
            break;
        }
        case SDL_EVENT_MOUSE_BUTTON_UP: {
            type = EventType::MouseButtonReleased;
            event = std::make_unique<MouseButtonReleasedEvent>(sdlEvent);
            m_MouseButtonStates[sdlEvent.button.button] = false;
            break;
        }
        case SDL_EVENT_MOUSE_WHEEL: {
            type = EventType::MouseScrolled;
            event = std::make_unique<MouseScrolledEvent>(sdlEvent);
            break;
        }
        default:
            return;
        }

        if (!m_PendingRemoval.empty()) {
            for (CallbackID id : m_PendingRemoval) {
                for (auto& [eventType, callbacks] : m_Callbacks) {
                    callbacks.erase(
                        std::remove_if(callbacks.begin(), callbacks.end(),
                            [id](const std::pair<CallbackID, EventCallback>& pair) {
                                return pair.first == id;
                            }),
                        callbacks.end());
                }
            }
            m_PendingRemoval.clear();
        }

        auto it = m_Callbacks.find(type);
        if (it != m_Callbacks.end()) {
            for (auto& [id, callback] : it->second) {
                callback(*event);
            }
        }
    }

    bool InputManager::IsKeyPressed(int scancode) const {
        auto it = m_KeyStates.find(scancode);
        return it != m_KeyStates.end() && it->second;
    }

    bool InputManager::IsKeyReleased(int scancode) const {
        auto it = m_KeyStates.find(scancode);
        return it == m_KeyStates.end() || !it->second;
    }

    bool InputManager::IsMouseButtonPressed(int button) const {
        auto it = m_MouseButtonStates.find(button);
        return it != m_MouseButtonStates.end() && it->second;
    }

    bool InputManager::IsMouseButtonReleased(int button) const {
        auto it = m_MouseButtonStates.find(button);
        return it == m_MouseButtonStates.end() || !it->second;
    }

    std::pair<float, float> InputManager::GetMousePosition() const {
        return { m_MouseX, m_MouseY };
    }
}
