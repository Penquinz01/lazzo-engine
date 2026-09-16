#include "lzpch.h"
#include "PointLight.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Lazzo::Object::Lights {

    PointLight::PointLight()
    {
        m_Type = LightType::Point;
    }

    PointLight::PointLight(const glm::vec3& position, const glm::vec3& color, float intensity, float range)
        : m_Position(position), m_Range(range)
    {
        m_Type = LightType::Point;
        m_Color = color;
        m_Intensity = intensity;
    }

    void PointLight::DrawUI()
    {
        ImGui::PushID("PointLight");
        ImGui::SeparatorText("Point Light");
        ImGui::DragFloat3("Position", glm::value_ptr(m_Position), 0.01f);
        ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
        ImGui::SliderFloat("Intensity", &m_Intensity, 0.0f, 5.0f);
        ImGui::DragFloat("Range", &m_Range, 0.1f, 0.1f, 100.0f);
        ImGui::DragFloat("Constant", &m_Constant, 0.01f, 0.0f, 5.0f);
        ImGui::DragFloat("Linear", &m_Linear, 0.001f, 0.0f, 1.0f);
        ImGui::DragFloat("Quadratic", &m_Quadratic, 0.001f, 0.0f, 1.0f);
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::PopID();
    }
}
