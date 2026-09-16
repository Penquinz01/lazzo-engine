#pragma once
#include <Lazzo/Layers/Layer.h>
#include <Lazzo/Object/Camera/Camera.h>
#include <SDL3/SDL.h>

// Editor-style fly camera input: WASD translates the camera along its local
// axes, and holding the right mouse button rotates it (yaw/pitch) by the
// relative mouse motion. The cursor is trapped while the button is held.
class EditorInputLayer : public Lazzo::Layer
{
public:
    EditorInputLayer(Lazzo::Object::Camera::Camera& camera, SDL_Window* window);
    ~EditorInputLayer() override = default;

    void OnAttach() override {}
    void OnDetach() override {}
    void OnUpdate() override;

private:
    Lazzo::Object::Camera::Camera& m_Camera;
    SDL_Window* m_Window{ nullptr };
    float m_MoveSpeed{ 6.0f };
    float m_MouseSensitivity{ 0.15f };
    Uint64 m_LastFrameTime{ 0 };
    bool m_RelativeMouseMode{ false };
};