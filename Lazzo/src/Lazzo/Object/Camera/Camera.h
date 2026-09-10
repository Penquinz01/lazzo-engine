#pragma once
#include <glm/glm.hpp>

namespace Lazzo::Object::Camera {
    class Camera
    {
    public:
        virtual ~Camera() = default;
        virtual void SetPosition(float x, float y, float z) = 0;
        virtual void SetPosition(const glm::vec3& pos) = 0;
        virtual glm::vec3 GetPosition() const = 0;
        virtual void SetRotation(float pitch, float yaw, float roll) = 0;
        virtual void SetRotation(const glm::vec3& rot) = 0;
        virtual glm::vec3 GetRotation() const = 0;
        virtual void SetFOV(float fov) = 0;
        virtual float GetFOV() const = 0;
        virtual void SetAspectRatio(float aspectRatio) = 0;
        virtual float GetAspectRatio() const = 0;
        virtual void SetNearPlane(float nearPlane) = 0;
        virtual float GetNearPlane() const = 0;
        virtual void SetFarPlane(float farPlane) = 0;
        virtual float GetFarPlane() const = 0;
        virtual glm::mat4 GetViewMatrix() const = 0;
        virtual glm::mat4 GetProjectionMatrix() const = 0;

    };
}
