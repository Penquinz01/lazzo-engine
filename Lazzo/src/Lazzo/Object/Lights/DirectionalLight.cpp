#include "lzpch.h"
#include "DirectionalLight.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Lazzo::Object::Lights {

    DirectionalLight::DirectionalLight()
    {
        m_Type = LightType::Directional;
    }

    DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color, float intensity)
        : m_Direction(direction)
    {
        m_Type = LightType::Directional;
        m_Color = color;
        m_Intensity = intensity;
    }

    void DirectionalLight::DrawUI()
    {
        ImGui::PushID("DirectionalLight");
        ImGui::SeparatorText("Directional Light");
        ImGui::DragFloat3("Direction", glm::value_ptr(m_Direction), 0.01f);
        ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
        ImGui::SliderFloat("Intensity", &m_Intensity, 0.0f, 5.0f);
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        ImGui::PopID();
    }
}
