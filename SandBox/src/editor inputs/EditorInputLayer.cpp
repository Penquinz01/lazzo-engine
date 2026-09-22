#include "lzpch.h"
#include "EditorInputLayer.h"
#include <Lazzo/Input/InputManager.h>
#include <glm/glm.hpp>

EditorInputLayer::EditorInputLayer(Lazzo::Object::Camera::Camera& camera, SDL_Window* window)
    : Layer("Editor Input"), m_Camera(camera), m_Window(window)
{
    m_LastFrameTime = SDL_GetPerformanceCounter();
}

void EditorInputLayer::OnMouseEvent(const Lazzo::Event& event)
{
    if (event.GetEventType() == Lazzo::EventType::MouseMoved)
    {
        const auto& mouseEvent = static_cast<const Lazzo::MouseMovedEvent&>(event);
        float dx = mouseEvent.GetRelX();
        float dy = mouseEvent.GetRelY();
        glm::vec3 rotation = m_Camera.GetRotation();
        rotation.y += dx * m_MouseSensitivity;
        rotation.x = glm::clamp(rotation.x - dy * m_MouseSensitivity, -89.0f, 89.0f);
        m_Camera.SetRotation(rotation);
    }
}

void EditorInputLayer::OnUpdate()
{
    Uint64 now = SDL_GetPerformanceCounter();
    float dt = static_cast<float>(now - m_LastFrameTime) / static_cast<float>(SDL_GetPerformanceFrequency());
    m_LastFrameTime = now;

    const bool* keys = SDL_GetKeyboardState(nullptr);

    float mouseX = 0.0f, mouseY = 0.0f;
    const bool rightDown = (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON_RMASK) != 0;

    if (rightDown)
    {
        if (m_Window != nullptr && !m_RelativeMouseMode)
        {
            SDL_SetWindowRelativeMouseMode(m_Window, true);
            m_RelativeMouseMode = true;
            float discardX = 0.0f, discardY = 0.0f;
            SDL_GetRelativeMouseState(&discardX, &discardY);
        }
        else
        {
            float dx = 0.0f, dy = 0.0f;
            SDL_GetRelativeMouseState(&dx, &dy);

        glm::vec3 rotation = m_Camera.GetRotation();
            rotation.y += dx * m_MouseSensitivity;
            rotation.x = glm::clamp(rotation.x - dy * m_MouseSensitivity, -89.0f, 89.0f);
            m_Camera.SetRotation(rotation);
        }
    }
    else if (m_RelativeMouseMode)
    {
        SDL_SetWindowRelativeMouseMode(m_Window, false);
        m_RelativeMouseMode = false;
    }

    const glm::vec3 front = m_Camera.GetFront();
    const glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    const float step = m_MoveSpeed * dt;

    glm::vec3 position = m_Camera.GetPosition();
    if (keys[SDL_SCANCODE_W]) position += front * step;
    if (keys[SDL_SCANCODE_S]) position -= front * step;
    if (keys[SDL_SCANCODE_A]) position -= right * step;
    if (keys[SDL_SCANCODE_D]) position += right * step;
    m_Camera.SetPosition(position);
}