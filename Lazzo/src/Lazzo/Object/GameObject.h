#pragma once
#include <glm/glm.hpp>

namespace Lazzo::Object {
    class GameObject {
    public:
        GameObject() = default;
        virtual ~GameObject() = default;
        virtual void Update(float deltaTime) = 0;
    public:
        glm::vec3 position{ 0.0f, 0.0f, 0.0f };
        glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
        glm::vec3 scale{ 1.0f, 1.0f, 1.0f };
    
    };
}
