#pragma once
#include <glm/glm.hpp>
#include "Lazzo/Core.h"
#include "Lazzo/Object/Camera/Camera.h"

namespace Lazzo::Object {

    struct LAZZO_API Ray {
        glm::vec3 Origin{ 0.0f };
        glm::vec3 Direction{ 0.0f, 0.0f, -1.0f };
    };

    struct LAZZO_API AABB {
        glm::vec3 Min{ 0.0f };
        glm::vec3 Max{ 0.0f };
    };

    // Same transform order as the built-in Draw() paths: translate -> rotate XYZ (degrees) -> scale.
    LAZZO_API glm::mat4 BuildModelMatrix(const glm::vec3& position, const glm::vec3& rotationDegrees, const glm::vec3& scale);
    LAZZO_API AABB UnitCubeAABB();
    LAZZO_API AABB TransformAABB(const AABB& local, const glm::mat4& model);

    // Slab test. Returns true on hit, outT = nearest non-negative distance along the ray.
    LAZZO_API bool RayIntersectsAABB(const Ray& ray, const AABB& box, float& outT);

    // Screenspace pixels (top-left origin) -> worldspace ray. Works for both
    // perspective and orthographic projections.
    LAZZO_API Ray ScreenPointToRay(float mouseX, float mouseY, float viewWidth, float viewHeight,
        const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    LAZZO_API Ray ScreenPointToRay(float mouseX, float mouseY, float viewWidth, float viewHeight,
        const Camera::Camera& camera);

    // Worldspace -> screenspace pixels (top-left origin). behindCamera is true
    // when the point is on/behind the camera plane (clip w <= 0).
    LAZZO_API glm::vec2 WorldToScreen(const glm::vec3& worldPos, float viewWidth, float viewHeight,
        const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, bool& behindCamera);
    LAZZO_API glm::vec2 WorldToScreen(const glm::vec3& worldPos, float viewWidth, float viewHeight,
        const Camera::Camera& camera, bool& behindCamera);
}
