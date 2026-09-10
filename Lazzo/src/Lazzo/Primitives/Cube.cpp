#include "lzpch.h"
#include "Cube.h"
#include <glad/glad.h>
#include <imgui.h>

namespace Lazzo {
    Cube::Cube(){
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

        constexpr GLsizei stride = 6 * sizeof(float);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindVertexArray(0);

        m_Material = std::make_unique<Graphics::Material>(
            "../Lazzo/Shaders/OpenGL/Basic.vert",
            "../Lazzo/Shaders/OpenGL/Basic.frag");
    }

    Cube::~Cube() {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }

    void Cube::Draw(const Lazzo::Object::Camera::Camera& camera) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), GetPosition());
        model = glm::rotate(model, glm::radians(GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, GetScale());

        m_Material->Bind();
        m_Material->SetMat4("u_Model", model);
        m_Material->SetMat4("u_View", camera.GetViewMatrix());
        m_Material->SetMat4("u_Projection", camera.GetProjectionMatrix());
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }

    void Cube::DrawUI() {
        ImGui::Begin("Cube");
        ImGui::DragFloat3("Position", glm::value_ptr(GetPosition()), 0.01f);
        ImGui::End();
    }

    void Cube::Update(float) {

    }
}
