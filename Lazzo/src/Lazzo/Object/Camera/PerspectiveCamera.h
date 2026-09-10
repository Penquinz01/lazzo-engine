#pragma once
#include "Lazzo/Core.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Lazzo::Object::Camera {

    class LAZZO_API PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane,
                          const glm::vec3& position = glm::vec3(0.0f, 0.0f, 3.0f),
                          const glm::vec3& rotation = glm::vec3(0.0f, 0.0f, 0.0f));
        virtual ~PerspectiveCamera() = default;

        void SetPosition(float x, float y, float z) override;
        void SetPosition(const glm::vec3& pos) override;
        glm::vec3 GetPosition() const override;
        void SetRotation(float pitch, float yaw, float roll) override;
        void SetRotation(const glm::vec3& rot) override;
        glm::vec3 GetRotation() const override;
        void SetFOV(float fov) override;
        float GetFOV() const override;
        void SetAspectRatio(float aspectRatio) override;
        float GetAspectRatio() const override;
        void SetNearPlane(float nearPlane) override;
        float GetNearPlane() const override;
        void SetFarPlane(float farPlane) override;
        float GetFarPlane() const override;

        glm::mat4 GetViewMatrix() const override;
        glm::mat4 GetProjectionMatrix() const override;

        glm::vec3 GetFront() const;

        void DrawUI();

    private:
        glm::vec3 m_Position;
        glm::vec3 m_Rotation;
        float m_FOV;
        float m_AspectRatio;
        float m_NearPlane;
        float m_FarPlane;
    };
}