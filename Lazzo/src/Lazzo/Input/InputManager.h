#pragma once

#include "Lazzo/Core.h"
#include "Lazzo/Window/Events/Event.h"
#include <SDL3/SDL_events.h>
#include <functional>
#include <vector>
#include <unordered_map>
#include <utility>

namespace Lazzo {
    using CallbackID = uint64_t;
    using EventCallback = std::function<void(const Event&)>;

    class LAZZO_API InputManager {
    private:
        InputManager() = default;
        ~InputManager() = default;

    public:
        static InputManager& GetInstance() {
            static InputManager instance;
            return instance;
        }

        InputManager(const InputManager&) = delete;
        InputManager& operator=(const InputManager&) = delete;

        CallbackID RegisterCallback(EventType type, EventCallback callback);
        void UnregisterCallback(CallbackID id);

        void ProcessEvent(const SDL_Event& sdlEvent);

        bool IsKeyPressed(int scancode) const;
        bool IsKeyReleased(int scancode) const;
        bool IsMouseButtonPressed(int button) const;
        bool IsMouseButtonReleased(int button) const;
        std::pair<float, float> GetMousePosition() const;

    private:
        std::unordered_map<EventType, std::vector<std::pair<CallbackID, EventCallback>>> m_Callbacks;
        std::vector<CallbackID> m_PendingRemoval;
        CallbackID m_NextID = 1;

        std::unordered_map<int, bool> m_KeyStates;
        std::unordered_map<int, bool> m_MouseButtonStates;
        float m_MouseX = 0.0f;
        float m_MouseY = 0.0f;
    };
}
