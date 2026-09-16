#include "lzpch.h"
#include "SpotLight.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Lazzo::Object::Lights {

    SpotLight::SpotLight()
    {
        m_Type = LightType::Spot;
    }

    SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction,
                         const glm::vec3& color, float intensity,
                         float innerCutoff, float outerCutoff)
        : m_Position(position), m_Direction(direction),
          m_InnerCutoff(innerCutoff), m_OuterCutoff(outerCutoff)
    {
        m_Type = LightType::Spot;
        m_Color = color;
        m_Intensity = intensity;
    }

    void SpotLight::DrawUI()
    {
        ImGui::PushID("SpotLight");
        ImGui::SeparatorText("Spot Light");
        ImGui::DragFloat3("Position", glm::value_ptr(m_Position), 0.01f);
        ImGui::DragFloat3("Direction", glm::value_ptr(m_Direction), 0.01f);
        ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
        ImGui::SliderFloat("Intensity", &m_Intensity, 0.0f, 5.0f);
        ImGui::SliderFloat("Inner Cutoff", &m_InnerCutoff, 0.0f, 90.0f);
        ImGui::SliderFloat("Outer Cutoff", &m_OuterCutoff, 0.0f, 90.0f);
        ImGui::DragFloat("Range", &m_Range, 0.1f, 0.1f, 100.0f);
        ImGui::DragFloat("Constant", &m_Constant, 0.01f, 0.0f, 5.0f);
        ImGui::DragFloat("Linear", &m_Linear, 0.001f, 0.0f, 1.0f);
        ImGui::DragFloat("Quadratic", &m_Quadratic, 0.001f, 0.0f, 1.0f);
        ImGui::PopID();
    }
}
