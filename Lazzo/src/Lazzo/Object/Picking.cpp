#include "lzpch.h"
#include "Picking.h"
#include <cmath>
#include <limits>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Lazzo::Object {

    glm::mat4 BuildModelMatrix(const glm::vec3& position, const glm::vec3& rotationDegrees, const glm::vec3& scale) {
        glm::mat4 matrix = glm::translate(glm::mat4(1.0f), position);
        matrix = glm::rotate(matrix, glm::radians(rotationDegrees.x), glm::vec3(1.0f, 0.0f, 0.0f));
        matrix = glm::rotate(matrix, glm::radians(rotationDegrees.y), glm::vec3(0.0f, 1.0f, 0.0f));
        matrix = glm::rotate(matrix, glm::radians(rotationDegrees.z), glm::vec3(0.0f, 0.0f, 1.0f));
        return glm::scale(matrix, scale);
    }

    AABB UnitCubeAABB() {
        AABB box;
        box.Min = glm::vec3(-0.5f);
        box.Max = glm::vec3(0.5f);
        return box;
    }

    AABB TransformAABB(const AABB& local, const glm::mat4& model) {
        AABB box;
        box.Min = glm::vec3(std::numeric_limits<float>::max());
        box.Max = glm::vec3(std::numeric_limits<float>::lowest());
        for (int i = 0; i < 8; i++) {
            glm::vec3 corner(
                (i & 1) ? local.Max.x : local.Min.x,
                (i & 2) ? local.Max.y : local.Min.y,
                (i & 4) ? local.Max.z : local.Min.z);
            glm::vec3 world = glm::vec3(model * glm::vec4(corner, 1.0f));
            box.Min = glm::min(box.Min, world);
            box.Max = glm::max(box.Max, world);
        }
        return box;
    }

    bool RayIntersectsAABB(const Ray& ray, const AABB& box, float& outT) {
        float tMin = 0.0f;
        float tMax = std::numeric_limits<float>::max();

        for (int i = 0; i < 3; i++) {
            float origin = (i == 0) ? ray.Origin.x : (i == 1 ? ray.Origin.y : ray.Origin.z);
            float direction = (i == 0) ? ray.Direction.x : (i == 1 ? ray.Direction.y : ray.Direction.z);
            float boxMin = (i == 0) ? box.Min.x : (i == 1 ? box.Min.y : box.Min.z);
            float boxMax = (i == 0) ? box.Max.x : (i == 1 ? box.Max.y : box.Max.z);

            if (std::abs(direction) < 1e-8f) {
                if (origin < boxMin || origin > boxMax)
                    return false;
            }
            else {
                float t1 = (boxMin - origin) / direction;
                float t2 = (boxMax - origin) / direction;
                if (t1 > t2) std::swap(t1, t2);
                tMin = std::max(tMin, t1);
                tMax = std::min(tMax, t2);
                if (tMin > tMax)
                    return false;
            }
        }
        outT = tMin;
        return true;
    }

    Ray ScreenPointToRay(float mouseX, float mouseY, float viewWidth, float viewHeight,
        const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
        float ndcX = (2.0f * mouseX) / viewWidth - 1.0f;
        float ndcY = 1.0f - (2.0f * mouseY) / viewHeight;
        glm::mat4 invVP = glm::inverse(projectionMatrix * viewMatrix);
        glm::vec4 pNear = invVP * glm::vec4(ndcX, ndcY, -1.0f, 1.0f);
        glm::vec4 pFar = invVP * glm::vec4(ndcX, ndcY, 1.0f, 1.0f);
        pNear /= pNear.w;
        pFar /= pFar.w;
        Ray ray;
        ray.Origin = glm::vec3(pNear);
        ray.Direction = glm::normalize(glm::vec3(pFar - pNear));
        return ray;
    }

    Ray ScreenPointToRay(float mouseX, float mouseY, float viewWidth, float viewHeight,
        const Camera::Camera& camera) {
        return ScreenPointToRay(mouseX, mouseY, viewWidth, viewHeight,
            camera.GetViewMatrix(), camera.GetProjectionMatrix());
    }

    glm::vec2 WorldToScreen(const glm::vec3& worldPos, float viewWidth, float viewHeight,
        const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, bool& behindCamera) {
        glm::vec4 clip = projectionMatrix * viewMatrix * glm::vec4(worldPos, 1.0f);
        behindCamera = clip.w <= 0.0f;
        if (std::abs(clip.w) < 1e-8f)
            return glm::vec2(-1.0f);
        glm::vec3 ndc = glm::vec3(clip) / clip.w;
        return glm::vec2(
            (ndc.x + 1.0f) * 0.5f * viewWidth,
            (1.0f - ndc.y) * 0.5f * viewHeight);
    }

    glm::vec2 WorldToScreen(const glm::vec3& worldPos, float viewWidth, float viewHeight,
        const Camera::Camera& camera, bool& behindCamera) {
        return WorldToScreen(worldPos, viewWidth, viewHeight,
            camera.GetViewMatrix(), camera.GetProjectionMatrix(), behindCamera);
    }
}
