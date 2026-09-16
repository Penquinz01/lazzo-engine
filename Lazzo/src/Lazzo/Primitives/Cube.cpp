#include "lzpch.h"
#include "Cube.h"
#include "Lazzo/Object/Lights/DirectionalLight.h"
#include "Lazzo/Object/Lights/PointLight.h"
#include "Lazzo/Object/Lights/SpotLight.h"
#include <glad/glad.h>
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

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
    Cube::Cube(std::string id) : m_Id(id) {
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

    void Cube::Draw(const Lazzo::Object::Camera::Camera& camera, const std::vector<Lazzo::Object::Lights::Light*>& lights) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), GetPosition());
        model = glm::rotate(model, glm::radians(GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, GetScale());

        m_Material->Bind();
        m_Material->SetMat4("u_Model", model);
        m_Material->SetMat4("u_View", camera.GetViewMatrix());
        m_Material->SetMat4("u_Projection", camera.GetProjectionMatrix());
        m_Material->SetFloat3("u_Color", GetColor());
        m_Material->SetFloat3("u_ViewPos", camera.GetPosition());

        int pointCount = 0;
        int spotCount = 0;

        for (auto* light : lights) {
            if (light->GetType() == Lazzo::Object::Lights::LightType::Directional) {
                auto* dl = static_cast<Lazzo::Object::Lights::DirectionalLight*>(light);
                m_Material->SetFloat3("u_DirLight.direction", dl->GetDirection());
                m_Material->SetFloat3("u_DirLight.color", dl->GetColor());
                m_Material->SetFloat("u_DirLight.intensity", dl->GetIntensity());
            }
            else if (light->GetType() == Lazzo::Object::Lights::LightType::Point && pointCount < 4) {
                auto* pl = static_cast<Lazzo::Object::Lights::PointLight*>(light);
                std::string prefix = "u_PointLights[" + std::to_string(pointCount) + "]";
                m_Material->SetFloat3(prefix + ".position", pl->GetPosition());
                m_Material->SetFloat3(prefix + ".color", pl->GetColor());
                m_Material->SetFloat(prefix + ".intensity", pl->GetIntensity());
                m_Material->SetFloat(prefix + ".constant", pl->GetConstant());
                m_Material->SetFloat(prefix + ".linear", pl->GetLinear());
                m_Material->SetFloat(prefix + ".quadratic", pl->GetQuadratic());
                pointCount++;
            }
            else if (light->GetType() == Lazzo::Object::Lights::LightType::Spot && spotCount < 4) {
                auto* sl = static_cast<Lazzo::Object::Lights::SpotLight*>(light);
                std::string prefix = "u_SpotLights[" + std::to_string(spotCount) + "]";
                m_Material->SetFloat3(prefix + ".position", sl->GetPosition());
                m_Material->SetFloat3(prefix + ".direction", sl->GetDirection());
                m_Material->SetFloat3(prefix + ".color", sl->GetColor());
                m_Material->SetFloat(prefix + ".intensity", sl->GetIntensity());
                m_Material->SetFloat(prefix + ".innerCutoff", glm::cos(glm::radians(sl->GetInnerCutoff())));
                m_Material->SetFloat(prefix + ".outerCutoff", glm::cos(glm::radians(sl->GetOuterCutoff())));
                m_Material->SetFloat(prefix + ".constant", sl->GetConstant());
                m_Material->SetFloat(prefix + ".linear", sl->GetLinear());
                m_Material->SetFloat(prefix + ".quadratic", sl->GetQuadratic());
                spotCount++;
            }
        }

        m_Material->SetInt("u_NumPointLights", pointCount);
        m_Material->SetInt("u_NumSpotLights", spotCount);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }

    void Cube::DrawUI() {
        ImGui::PushID(m_Id.c_str());
        ImGui::SeparatorText("Cube");
        if (ImGui::DragFloat3("Position", glm::value_ptr(GetPosition()), 0.01f)) {}
        glm::vec3 rotation = GetRotation();
        if (ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 0.1f))
            SetRotation(rotation);
        glm::vec3 scale = GetScale();
        if (ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.01f))
            SetScale(scale);
        glm::vec3 color = GetColor();
        if (ImGui::ColorEdit3("Color", glm::value_ptr(color)))
            SetColor(color);
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::PopID();
    }

    void Cube::Update(float) {

    }
}
