#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Lazzo/Window/GraphicsAPI/Material.h"

namespace Lazzo {
    class Primitives {
    public:
        Primitives() = default;
        ~Primitives() = default;
        glm::vec3& GetPosition() { return position; }
        const glm::vec3& GetPosition() const { return position; }
        glm::vec3 GetRotation() const { return rotation; }
        glm::vec3 GetScale() const { return scale; }
        glm::vec3 SetPosition(const glm::vec3& pos) { position = pos; return position; }
        glm::vec3 SetRotation(const glm::vec3& rot) { rotation = rot; return rotation; }
        glm::vec3 SetScale(const glm::vec3& sc) { scale = sc; return scale; }
        glm::vec3 GetColor() const { return m_Color; }
        glm::vec3 SetColor(const glm::vec3& col) { m_Color = col; return m_Color; }
    private:
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 m_Color = glm::vec3(0.20f, 0.55f, 0.95f);
    protected:
        unsigned int VAO, VBO, EBO;
        std::unique_ptr<Graphics::Material> m_Material;
    };
}
